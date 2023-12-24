#include "aseprite_data.hpp"
#include <fstream>
#include <istream>

aselib::AsepriteData::AsepriteData(std::filesystem::path const& file_name)
{
    std::ifstream in { file_name, std::ios::binary };
    if (!in.good()) [[unlikely]] {
        throw std::invalid_argument { "Error opening the file: '" + file_name.string() + "'" };
    }
    in >> m_header;

    m_frames.resize(m_header.m_number_of_frames);
    for (int frame_index = 0u; frame_index != m_header.m_number_of_frames; ++frame_index) {
        in >> m_frames[frame_index].m_frame_header;
        m_frames[frame_index].m_chunks
            = parseAllChunks(in, m_frames[frame_index].m_frame_header.m_number_of_chunks, m_header);
    }
}
