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
    z_stream zs; // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = static_cast<uInt>(str.size());

    int ret;
    char outbuffer[256];
    std::string outstring;

    // get the decompressed bytes blockwise using repeated calls to inflate
    do {
        zs.next_out = reinterpret_cast<Bytef*>(outbuffer);
        zs.avail_out = sizeof(outbuffer);

        ret = inflate(&zs, 0);

        if (outstring.size() < zs.total_out) {
            outstring.append(outbuffer, zs.total_out - outstring.size());
        }

    } while (ret == Z_OK);

    inflateEnd(&zs);

    if (ret != Z_STREAM_END) { // an error occurred that was not EOF
        std::ostringstream oss;
        oss << "Exception during zlib decompression: (" << ret << ") " << zs.msg;
        throw(std::runtime_error(oss.str()));
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
        ColorProfileChunk cpc {};
        cpc.m_header = hdr;

        cpc.m_color_profile_type = parseWord(is);
        cpc.m_color_profile_flags = parseWord(is);

        is.ignore(4);
        cpc.gamma = 1;

        is.ignore(8);

        data.m_color_profile_chunks.emplace_back(cpc);
    } else if (hdr.m_chunk_type == 0x2019) {
        // palette chunk
        PaletteChunk pc {};
        pc.m_header = hdr;
        Dword_t palette_size = parseDword(is);
        pc.m_first_color_index_to_change = parseDword(is);
        pc.m_last_color_index_to_change = parseDword(is);
        is.ignore(8);
        for (auto i = 0u; i != palette_size; ++i) {
            PaletteEntry entry {};
            entry.m_entry_flags = parseWord(is);
            entry.m_color.r = parseByte(is);
            entry.m_color.g = parseByte(is);
            entry.m_color.b = parseByte(is);
            entry.m_color.a = parseByte(is);
            pc.m_palette_entries.emplace_back(entry);
        }
        data.m_palette_chunks.emplace_back(pc);
    } else if (hdr.m_chunk_type == 0x0004) {
        // old palette chunk, ignore
        is.ignore(hdr.m_chunk_size - 6);
    } else if (hdr.m_chunk_type == 0x2004) {
        // layers chunk
        LayerChunk lc {};
        lc.m_header = hdr;
        lc.m_layer_flags = parseWord(is);
        lc.m_layer_type = parseWord(is);
        lc.m_layer_child_level = parseWord(is);
        is.ignore(2); // Default layer width in pixels (ignored)
        is.ignore(2); // Default layer height in pixels (ignored)
        lc.m_blend_mode = parseWord(is);
        lc.m_opacity = parseByte(is);
        is.ignore(3); // ignore
        lc.m_layer_name = parseString(is);
        data.m_layers_chunks.emplace_back(lc);
    } else if (hdr.m_chunk_type == 0x2005) {
        // cel chunk
        CelChunk cc {};
        cc.m_header = hdr;
        cc.m_layer_index = parseWord(is);
        cc.m_pos_x = parseShort(is);
        cc.m_pos_y = parseShort(is);
        cc.m_opacity = parseByte(is);
        cc.m_cell_type = parseWord(is);
        cc.m_z_index = parseShort(is);
        is.ignore(5);
        if (cc.m_cell_type != 2) {
            throw std::invalid_argument { "unsupported cell type "
                + std::to_string(cc.m_cell_type) };
        }
        cc.m_cell_width = parseWord(is);
        cc.m_cell_height = parseWord(is);

        auto const chunk_header_size = 6;
        auto const chunk_data_offset = 20 + chunk_header_size;
        auto const data_size = cc.m_header.m_chunk_size - chunk_data_offset;
        std::string compressed_data {};
        compressed_data.resize(data_size);
        is.read(compressed_data.data(), compressed_data.size());
        std::string const uncompressed_data = decompress(compressed_data);

        auto const length = uncompressed_data.length();
        auto const bytes_per_pixel = ase_header.m_color_depth / 8;
        auto const expected_length = cc.m_cell_height * cc.m_cell_width * bytes_per_pixel;
        if (length != static_cast<std::size_t>(expected_length)) {
            throw std::invalid_argument {
                "decompressed cel data length does not match cel width and height and bit depth"
            };
        }
        for (auto j = 0u; j != cc.m_cell_height; ++j) {
            for (auto i = 0u; i != cc.m_cell_width; ++i) {
                auto const idx_ofs = (i + j * cc.m_cell_width) * bytes_per_pixel;
                if (bytes_per_pixel == 4) {
                    cc.m_pixels_rgba.emplace_back(PixelDataRGBA {
                        // clang-format off
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 0]),
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 1]),
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 2]),
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 3])
                        // clang-format on
                    });
                } else if (bytes_per_pixel == 2) {
                    cc.m_pixels_grayscale.emplace_back(PixelDataGrayscale {
                        // clang-format off
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 0]),
                        static_cast<Byte_t>(uncompressed_data[idx_ofs + 1])
                        // clang-format on
                    });
                } else if (bytes_per_pixel == 1) {
                    cc.m_pixels_indexed.emplace_back(
                        PixelDataIndexed { static_cast<Byte_t>(uncompressed_data[idx_ofs]) });
                } else {
                    throw std::invalid_argument { "unsupported color depth: "
                        + std::to_string(static_cast<int>(ase_header.m_color_depth)) };
                }
            }
        }

        data.m_cel_chunks.emplace_back(cc);
    } else if (hdr.m_chunk_type == 0x2018) {
        // tags
        TagChunk tc {};
        tc.m_header = hdr;
        auto const number_of_tags = parseWord(is);
        is.ignore(8); // for future use
        for (auto i = 0u; i != number_of_tags; ++i) {
            TagEntry te {};
            te.m_from_frame = parseWord(is);
            te.m_to_frame = parseWord(is);
            te.m_loop_direction = parseByte(is);
            te.m_repeat_animation = parseWord(is);
            is.ignore(6); // for future use
            is.ignore(3); // deprecated tag color
            is.ignore(1); // extra byte
            te.m_tag_name = parseString(is);
            tc.m_tags.push_back(te);
        }
        data.m_tag_chunks.emplace_back(tc);
    } else if (hdr.m_chunk_type == 0x2020) {
        // user data
        UserDataChunk udc {};
        udc.m_header = hdr;
        udc.m_user_data_flags = parseDword(is);
        if (udc.m_user_data_flags & 1) {
            udc.m_text = parseString(is);
        }
        if (udc.m_user_data_flags & 2) {
            udc.m_color_r = parseByte(is);
            udc.m_color_g = parseByte(is);
            udc.m_color_b = parseByte(is);
            udc.m_color_a = parseByte(is);
        }
        if (udc.m_user_data_flags & 4) {
            // TODO implement properties

            //            Dword_t const numberOfPropertyMaps = parseDword(is);
            throw std::invalid_argument { "cannot read properties until now" };
        }
        data.m_user_data_chunks.emplace_back(udc);
    } else {
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
