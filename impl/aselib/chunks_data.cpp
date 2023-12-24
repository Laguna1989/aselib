#include "chunks_data.hpp"
#include <aselib/aseprite_header.hpp>
#include <aselib/parse_functions.hpp>
#include <aselib/pixel_data.hpp>
#include <cstring>
#include <sstream>
#include <zlib.h>

namespace {

// Decompress an STL string using zlib and return the original data.
std::string decompress(std::string const& str)
{
    z_stream zs = {}; // z_stream is zlib's control structure

    if (inflateInit(&zs) != Z_OK) [[unlikely]] {
        throw(std::runtime_error("inflateInit failed while decompressing."));
    }

    zs.next_in = (Byte*)str.data();
    zs.avail_in = static_cast<uInt>(str.size());

    int ret;
    std::string outstring;

    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        char outbuffer[256];
        zs.next_out = reinterpret_cast<Byte*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs, 0);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer, zs.total_out - outstring.size());
        }

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) [[unlikely]] {
        // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") " << zs.msg;
        throw std::runtime_error { oss.str() };
    }
    return outstring;
}

} // namespace

aselib::ChunkHeader aselib::parseChunkHeader(std::istream& is)
{
    ChunkHeader hdr {};

    hdr.m_chunk_size = parseDword(is);
    hdr.m_chunk_type = parseWord(is);

    return hdr;
}

void aselib::parseNextChunk(
    std::istream& is, ChunksData& data, aselib::AsepriteHeader const& ase_header)
{
    ChunkHeader const hdr = parseChunkHeader(is);

    if (hdr.m_chunk_type == 0x2007) {
        // color profile chunk
        ColorProfileChunk color_profile_chunk {};
        color_profile_chunk.m_header = hdr;

        color_profile_chunk.m_color_profile_type = parseWord(is);
        color_profile_chunk.m_color_profile_flags = parseWord(is);

        is.ignore(4);
        color_profile_chunk.gamma = 1;

        is.ignore(8);

        data.m_color_profile_chunks.emplace_back(color_profile_chunk);

    } else if (hdr.m_chunk_type == 0x2019) {
        // palette chunk
        PaletteChunk palette_chunk {};
        palette_chunk.m_header = hdr;
        Dword_t palette_size = parseDword(is);
        palette_chunk.m_first_color_index_to_change = parseDword(is);
        palette_chunk.m_last_color_index_to_change = parseDword(is);
        is.ignore(8);
        for (auto i = 0u; i != palette_size; ++i) {
            PaletteEntry entry {};
            entry.m_entry_flags = parseWord(is);
            entry.m_color.r = parseByte(is);
            entry.m_color.g = parseByte(is);
            entry.m_color.b = parseByte(is);
            entry.m_color.a = parseByte(is);
            palette_chunk.m_palette_entries.emplace_back(entry);
        }

        data.m_palette_chunks.emplace_back(palette_chunk);
    } else if (hdr.m_chunk_type == 0x0004) {
        // old palette chunk, ignore
        is.ignore(hdr.m_chunk_size - 6);
    } else if (hdr.m_chunk_type == 0x2004) {
        // layers chunk
        LayerChunk layer_chunk {};
        layer_chunk.m_header = hdr;
        layer_chunk.m_layer_flags = parseWord(is);
        layer_chunk.m_layer_type = parseWord(is);
        layer_chunk.m_layer_child_level = parseWord(is);
        is.ignore(2); // Default layer width in pixels (ignored)
        is.ignore(2); // Default layer height in pixels (ignored)
        layer_chunk.m_blend_mode = parseWord(is);
        layer_chunk.m_opacity = parseByte(is);
        is.ignore(3); // ignore
        layer_chunk.m_layer_name = parseString(is);

        data.m_layers_chunks.emplace_back(layer_chunk);
    } else if (hdr.m_chunk_type == 0x2005) {
        // cel chunk
        CelChunk cel_chunk {};
        cel_chunk.m_header = hdr;
        cel_chunk.m_layer_index = parseWord(is);
        cel_chunk.m_pos_x = parseShort(is);
        cel_chunk.m_pos_y = parseShort(is);
        cel_chunk.m_opacity = parseByte(is);
        cel_chunk.m_cell_type = parseWord(is);
        cel_chunk.m_z_index = parseShort(is);
        is.ignore(5);
        if (cel_chunk.m_cell_type != 2) [[unlikely]] {
            throw std::invalid_argument { "unsupported cell type "
                + std::to_string(cel_chunk.m_cell_type) };
        }
        cel_chunk.m_cell_width = parseWord(is);
        cel_chunk.m_cell_height = parseWord(is);

        constexpr auto chunk_header_size = 6;
        constexpr auto chunk_data_offset = 20 + chunk_header_size;
        auto const data_size = cel_chunk.m_header.m_chunk_size - chunk_data_offset;
        std::string compressed_data {};
        compressed_data.resize(data_size);
        is.read(compressed_data.data(), compressed_data.size());
        std::string const uncompressed_data = decompress(compressed_data);

        auto const length = uncompressed_data.length();
        auto const bytes_per_pixel = ase_header.m_color_depth / 8;
        auto const expected_length
            = cel_chunk.m_cell_height * cel_chunk.m_cell_width * bytes_per_pixel;
        if (length != static_cast<std::size_t>(expected_length)) [[unlikely]] {
            throw std::invalid_argument {
                "decompressed cel data length does not match cel width and height and bit depth"
            };
        }
        for (auto j = 0u; j != cel_chunk.m_cell_height; ++j) {
            for (auto i = 0u; i != cel_chunk.m_cell_width; ++i) {
                auto const idx_ofs = (i + j * cel_chunk.m_cell_width) * bytes_per_pixel;
                if (bytes_per_pixel == 4) {
                    cel_chunk.m_pixels_rgba.emplace_back(PixelDataRGBA {
                        // clang-format off
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 0]),
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 1]),
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 2]),
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 3])
                        // clang-format on
                    });
                } else if (bytes_per_pixel == 2) {
                    cel_chunk.m_pixels_grayscale.emplace_back(PixelDataGrayscale {
                        // clang-format off
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 0]),
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 1])
                        // clang-format on
                    });
                } else if (bytes_per_pixel == 1) {
                    cel_chunk.m_pixels_indexed.emplace_back(
                        PixelDataIndexed { static_cast<Byte_t>(uncompressed_data[idx_ofs]) });
                } else [[unlikely]] {
                    throw std::invalid_argument { "unsupported color depth: "
                        + std::to_string(ase_header.m_color_depth) };
                }
            }
        }

        data.m_cel_chunks.emplace_back(cel_chunk);
    } else if (hdr.m_chunk_type == 0x2018) {
        // tags
        TagChunk tag_chunk {};
        tag_chunk.m_header = hdr;

        auto const number_of_tags = parseWord(is);
        is.ignore(8); // for future use
        for (auto i = 0u; i != number_of_tags; ++i) {
            TagEntry tag_entry {};
            tag_entry.m_from_frame = parseWord(is);
            tag_entry.m_to_frame = parseWord(is);
            tag_entry.m_loop_direction = parseByte(is);
            tag_entry.m_repeat_animation = parseWord(is);
            is.ignore(6); // for future use
            is.ignore(3); // deprecated tag color
            is.ignore(1); // extra byte
            tag_entry.m_tag_name = parseString(is);
            tag_chunk.m_tags.push_back(tag_entry);
        }
        data.m_tag_chunks.emplace_back(tag_chunk);
    } else if (hdr.m_chunk_type == 0x2020) {
        // user data
        UserDataChunk user_data_chunk {};
        user_data_chunk.m_header = hdr;
        user_data_chunk.m_user_data_flags = parseDword(is);
        if (user_data_chunk.m_user_data_flags & 1) {
            user_data_chunk.m_text = parseString(is);
        }
        if (user_data_chunk.m_user_data_flags & 2) {
            user_data_chunk.m_color_r = parseByte(is);
            user_data_chunk.m_color_g = parseByte(is);
            user_data_chunk.m_color_b = parseByte(is);
            user_data_chunk.m_color_a = parseByte(is);
        }
        if (user_data_chunk.m_user_data_flags & 4) [[unlikely]] {
            // TODO implement properties

            //            Dword_t const numberOfPropertyMaps = parseDword(is);
            throw std::invalid_argument { "aselib cannot read properties" };
        }
        data.m_user_data_chunks.emplace_back(user_data_chunk);
    } else [[unlikely]] {
        throw std::invalid_argument { "unsupported chunk type: "
            + std::to_string(hdr.m_chunk_type) };
    }
}

aselib::ChunksData aselib::parseAllChunks(
    std::istream& is, uint16_t number_of_chunks, aselib::AsepriteHeader const& ase_header)
{
    ChunksData chunks {};
    for (std::uint16_t i = 0u; i != number_of_chunks; ++i) {
        parseNextChunk(is, chunks, ase_header);
    }

    return chunks;
}
