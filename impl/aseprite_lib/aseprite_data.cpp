#include "aseprite_data.hpp"
#include <fstream>
#include <istream>

aseprite_lib::AsepriteData::AsepriteData(std::string const& file_name)
{
    std::ifstream in { file_name, std::ios::binary };
    if (!in.good()) {
        throw std::invalid_argument { "Error opening the file: '" + file_name + "'" };
    }
    in >> m_header;

    m_frames.resize(m_header.m_number_of_frames);
    for (int frame_index = 0u; frame_index != m_header.m_number_of_frames; ++frame_index) {
        in >> m_frames[frame_index].m_frame_header;
        m_frames[frame_index].m_chunks
            = parseAllChunks(in, m_frames[frame_index].m_frame_header.m_number_of_chunks);
    }
}
