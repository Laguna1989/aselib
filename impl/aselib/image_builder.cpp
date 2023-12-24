#include "image_builder.hpp"
#include <aselib/constants.hpp>
#include <aselib/pixel_operations.hpp>

aselib::Image aselib::makeImageFromAse(
    aselib::AsepriteData const& ase, bool include_invisible_layers)
{
    if (ase.m_frames.empty()) [[unlikely]] {
        throw std::invalid_argument { "aseprite does not contain any frames" };
    }

    Image img {};

    auto const numberOfFrames = ase.m_header.m_number_of_frames;
    img.m_width = ase.m_header.m_width_in_pixel * numberOfFrames;
    img.m_height = ase.m_header.m_height_in_pixel;

    auto const numberOfPixels = img.m_width * img.m_height;

    img.m_pixels.resize(numberOfPixels, PixelDataRGBA { 0, 0, 0, 0 });

    auto const& layers = ase.m_frames.at(0).m_chunks.m_layers_chunks;

    for (auto i = 0u; i != numberOfFrames; ++i) {

        std::uint32_t frame_offset_x = i * ase.m_header.m_width_in_pixel;
        auto const& f = ase.m_frames[i];

        for (auto const& cel : f.m_chunks.m_cel_chunks) {
            auto const layer_index = cel.m_layer_index;
            if (!include_invisible_layers) {
                if (!(layers.at(layer_index).m_layer_flags & aselib::layer_flags::visible)) {
                    continue;
                }
            }

            auto const layer_opacity = layers.at(layer_index).m_opacity;

            for (auto x_in_cel = 0; x_in_cel != cel.m_cell_width; ++x_in_cel) {
                for (auto y_in_cel = 0; y_in_cel != cel.m_cell_height; ++y_in_cel) {
                    auto const x_in_frame = x_in_cel + cel.m_pos_x;
                    auto const y_in_frame = y_in_cel + cel.m_pos_y;
                    auto const& pixel_orig
                        = img.getPixelAt(x_in_frame + frame_offset_x, y_in_frame);
                    if (ase.m_header.m_color_depth == 32) {
                        auto const& pixel_src
                            = cel.m_pixels_rgba[x_in_cel + y_in_cel * cel.m_cell_width];
                        img.getPixelAt(x_in_frame + frame_offset_x, y_in_frame)
                            = add_pixel_color(pixel_src, pixel_orig, layer_opacity);
                    } else if (ase.m_header.m_color_depth == 16) {
                        auto const& pixel_src
                            = cel.m_pixels_grayscale[x_in_cel + y_in_cel * cel.m_cell_width];
                        img.getPixelAt(x_in_frame + frame_offset_x, y_in_frame)
                            = add_pixel_color(pixel_src, pixel_orig, layer_opacity);
                    } else if (ase.m_header.m_color_depth == 8) {
                        auto const& palette
                            = ase.m_frames.front().m_chunks.m_palette_chunks.front();
                        auto const& pixel_src
                            = cel.m_pixels_indexed[x_in_cel + y_in_cel * cel.m_cell_width];
                        img.getPixelAt(x_in_frame + frame_offset_x, y_in_frame)
                            = add_pixel_color(pixel_src, pixel_orig, palette, layer_opacity);
                    } else [[unlikely]] {
                        throw std::invalid_argument { "unsupported color depth" };
                    }
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

    bool found = false;
    std::uint16_t layerID = 0;
    for (auto i = 0u; i != ase.m_frames[0].m_chunks.m_layers_chunks.size(); ++i) {
        if (ase.m_frames[0].m_chunks.m_layers_chunks.at(i).m_layer_name == layerName) {
            found = true;
            layerID = i;
            break;
        }
    }
    if (!found) [[unlikely]] {
        throw std::invalid_argument { "no layer found with name '" + layerName + "'" };
    }

    auto const numberOfFrames = ase.m_header.m_number_of_frames;
    img.m_width = ase.m_header.m_width_in_pixel * numberOfFrames;
    img.m_height = ase.m_header.m_height_in_pixel;

    auto const numberOfPixels = img.m_width * img.m_height;

    img.m_pixels.resize(numberOfPixels, PixelDataRGBA { 0, 0, 0, 0 });

    for (auto i = 0u; i != numberOfFrames; ++i) {

        std::uint32_t const frame_offset_x = i * ase.m_header.m_width_in_pixel;
        auto const& [frame_header, m_chunks] = ase.m_frames[i];

        for (auto const& cel : m_chunks.m_cel_chunks) {
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
