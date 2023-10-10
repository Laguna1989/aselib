#include "image_builder.hpp"

namespace {
aselib::PixelDataRGBA addPixelColor(
    aselib::PixelDataRGBA const& pixel_src, aselib::PixelDataRGBA const& pixel_orig)
{

    if (pixel_src.a == 255) {
        // just paint over
        return pixel_src;
    } else if (pixel_src.a == 0) {
        return pixel_orig;
    } else {
        // TODO test

        float const a0 = static_cast<float>(pixel_src.a) / 255.0f;
        float const r0 = static_cast<float>(pixel_src.r) / 255.0f;
        float const g0 = static_cast<float>(pixel_src.g) / 255.0f;
        float const b0 = static_cast<float>(pixel_src.b) / 255.0f;

        float const a1 = static_cast<float>(pixel_orig.a) / 255.0f;
        float const r1 = static_cast<float>(pixel_orig.r) / 255.0f;
        float const g1 = static_cast<float>(pixel_orig.g) / 255.0f;
        float const b1 = static_cast<float>(pixel_orig.b) / 255.0f;

        float const a01 = (1.0f - a0) * a1 + a0;
        float const r01 = ((1.0f - a0) * a1 * r1 + a0 * r0) / a01;
        float const g01 = ((1.0f - a0) * a1 * g1 + a0 * g0) / a01;
        float const b01 = ((1.0f - a0) * a1 * b1 + a0 * b0) / a01;

        return aselib::PixelDataRGBA {
            // clang-format off
            static_cast<std::uint8_t>(r01 * 255.0f),
            static_cast<std::uint8_t>(g01 * 255.0f),
            static_cast<std::uint8_t>(b01 * 255.0f),
            static_cast<std::uint8_t>(a01 * 255.0f)
            // clang-format on
        };
    }
}
} // namespace

aselib::Image aselib::makeImageFromAse(aselib::AsepriteData const& ase)
{
    Image img {};

    auto const numberOfFrames = ase.m_header.m_number_of_frames;
    img.m_width = ase.m_header.m_width_in_pixel * numberOfFrames;
    img.m_height = ase.m_header.m_height_in_pixel;

    auto const numberOfPixels = img.m_width * img.m_height;

    img.m_pixels.resize(numberOfPixels, PixelDataRGBA { 0, 0, 0, 0 });

    for (auto i = 0u; i != numberOfFrames; ++i) {

        std::uint32_t frame_offset_x = i * ase.m_header.m_width_in_pixel;
        auto const& f = ase.m_frames[i];

        if (f.m_chunks.m_cel_chunks.empty()) {
            continue;
        }

        for (auto const& cel : f.m_chunks.m_cel_chunks) {
            for (auto x_in_cel = 0; x_in_cel != cel.m_cell_width; ++x_in_cel) {
                for (auto y_in_cel = 0; y_in_cel != cel.m_cell_height; ++y_in_cel) {
                    auto const x_in_frame = x_in_cel + cel.m_pos_x;
                    auto const y_in_frame = y_in_cel + cel.m_pos_y;

                    auto const& pixel_src
                        = cel.m_pixels_rgba[x_in_cel + y_in_cel * cel.m_cell_width];
                    auto const& pixel_orig
                        = img.getPixelAt(x_in_frame + frame_offset_x, y_in_frame);
                    img.getPixelAt(x_in_frame + frame_offset_x, y_in_frame)
                        = addPixelColor(pixel_src, pixel_orig);
                }
            }
        }
    }

    return img;
}

aselib::Image aselib::makeImageFromLayer(
    aselib::AsepriteData const& ase, std::string const& layerName)
{
    Image img {};

    if (ase.m_frames[0].m_chunks.m_layers_chunks.empty()) {
        throw std::invalid_argument { "no layer information in first frame" };
    }

    bool found = false;
    std::uint16_t layerID = 0;
    for (auto i = 0u; i != ase.m_frames[0].m_chunks.m_layers_chunks.size(); ++i) {
        if (ase.m_frames[0].m_chunks.m_layers_chunks.at(i).m_layer_name == layerName) {
            found = true;
            layerID = i;
            break;
        }
    }
    if (!found) {
        throw std::invalid_argument { "no layer found with name '" + layerName + "'" };
    }

    auto const numberOfFrames = ase.m_header.m_number_of_frames;
    img.m_width = ase.m_header.m_width_in_pixel * numberOfFrames;
    img.m_height = ase.m_header.m_height_in_pixel;

    auto const numberOfPixels = img.m_width * img.m_height;

    img.m_pixels.resize(numberOfPixels, PixelDataRGBA { 0, 0, 0, 0 });

    for (auto i = 0u; i != numberOfFrames; ++i) {

        std::uint32_t frame_offset_x = i * ase.m_header.m_width_in_pixel;
        auto const& f = ase.m_frames[i];

        if (f.m_chunks.m_cel_chunks.empty()) {
            continue;
        }

        for (auto const& cel : f.m_chunks.m_cel_chunks) {
            if (cel.m_layer_index != layerID) {
                continue;
            }
            for (auto x_in_cel = 0; x_in_cel != cel.m_cell_width; ++x_in_cel) {
                for (auto y_in_cel = 0; y_in_cel != cel.m_cell_height; ++y_in_cel) {
                    auto const x_in_frame = x_in_cel + cel.m_pos_x;
                    auto const y_in_frame = y_in_cel + cel.m_pos_y;

                    auto const& pixel_src
                        = cel.m_pixels_rgba[x_in_cel + y_in_cel * cel.m_cell_width];
                    img.m_pixels[img.posToIndex(x_in_frame + frame_offset_x, y_in_frame)]
                        = pixel_src;
                }
            }
        }
    }

    return img;
}
