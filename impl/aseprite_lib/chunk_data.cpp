#include "chunk_data.hpp"
#include "pixel_data.hpp"
#include <aseprite_lib/parse_functions.hpp>
#include <cstring>
#include <sstream>
#include <zlib.h>

namespace {
// Decompress an STL string using zlib and return the original data.
std::string decompress(const std::string& str)
{
    z_stream zs; // z_stream is zlib's control structure
    memset(&zs, 0, sizeof(zs));

    if (inflateInit(&zs) != Z_OK)
        throw(std::runtime_error("inflateInit failed while decompressing."));

    zs.next_in = (Bytef*)str.data();
    zs.avail_in = static_cast<uInt>(str.size());

    int ret;
    char outbuffer[10240];
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

aseprite_lib::ChunkHeader aseprite_lib::parseChunkHeader(std::istream& is)
{
    ChunkHeader hdr {};

    hdr.m_chunk_size = parseDword(is);
    hdr.m_chunk_type = parseWord(is);

    return hdr;
}

void aseprite_lib::parseNextChunk(std::istream& is, ChunksData& data)
{
    ChunkHeader hdr = parseChunkHeader(is);

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
            entry.m_red = parseByte(is);
            entry.m_green = parseByte(is);
            entry.m_blue = parseByte(is);
            entry.m_alpha = parseByte(is);
            pc.m_palette_entries.emplace_back(entry);
        }
        data.m_palette_chunks.emplace_back(pc);
    } else if (hdr.m_chunk_type == 0x0004) {
        // old palette chunk, ignore
        is.ignore(hdr.m_chunk_size - 6);
    } else if (hdr.m_chunk_type == 0x2004) {
        // layers chunk
        LayersChunk lc {};
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
        cc.m_pos_x = parseWord(is); // TODO signed/unsigned conversion
        cc.m_pos_y = parseWord(is); // TODO signed/unsigned conversion
        cc.m_opacity = parseByte(is);
        cc.m_cell_type = parseWord(is);
        cc.m_z_index = parseWord(is); // TODO signed/unsigned conversion
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
        std::string compressed_data;
        compressed_data.resize(data_size);
        is.read(compressed_data.data(), compressed_data.size());
        std::string uncompressed_data = decompress(compressed_data);

        auto const length = uncompressed_data.length();
        if (length != cc.m_cell_height * cc.m_cell_width * 4) {
            throw std::invalid_argument {
                "decompressed cel data length does not match cel width and height."
            };
        }
        for (auto j = 0u; j != cc.m_cell_height; ++j) {
            for (auto i = 0u; i != cc.m_cell_width; ++i) {
                auto const idx_ofs = (i + j * cc.m_cell_width) * 4;
                PixelDataRGBA col {};
                col.r = static_cast<Byte_t>(uncompressed_data[idx_ofs + 0]);
                col.g = static_cast<Byte_t>(uncompressed_data[idx_ofs + 1]);
                col.b = static_cast<Byte_t>(uncompressed_data[idx_ofs + 2]);
                col.a = static_cast<Byte_t>(uncompressed_data[idx_ofs + 3]);
                cc.m_pixels_rgba.emplace_back(col);
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
            Dword_t const numberOfPropertyMaps = parseDword(is);
            // TODO implement properties
            throw std::invalid_argument { "cannot read properties until now" };
        }
        data.m_user_data_chunks.emplace_back(udc);
    } else {
        throw std::invalid_argument { "unsupported chunk type: "
            + std::to_string(hdr.m_chunk_type) };
    }
}
aseprite_lib::ChunksData aseprite_lib::parseAllChunks(
    std::istream& is, std::uint16_t number_of_chunks)
{
    ChunksData chunks {};
    for (int i = 0; i != number_of_chunks; ++i) {
        parseNextChunk(is, chunks);
    }

    return chunks;
}
