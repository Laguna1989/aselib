#include "pixel_operations.hpp"
#include <aselib/chunks_data.hpp>

aselib::PixelDataRGBA aselib::add_pixel_color(aselib::PixelDataRGBA const& pixel_src,
    aselib::PixelDataRGBA const& pixel_orig, std::uint8_t layer_opacity)
{
    if (pixel_src.a == 255) {
        // just paint over
        return pixel_src;
    } else if (pixel_src.a == 0) {
        // ignore new pixel
        return pixel_orig;
    }

    float const a0 = static_cast<float>(pixel_src.a) / 255.0f;
    float const r0 = static_cast<float>(pixel_src.r) / 255.0f;
    float const g0 = static_cast<float>(pixel_src.g) / 255.0f;
    float const b0 = static_cast<float>(pixel_src.b) / 255.0f;

    float const a_layer = static_cast<float>(layer_opacity) / 255.0f;

    float const a1 = static_cast<float>(pixel_orig.a) / 255.0f * a_layer;
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

aselib::PixelDataRGBA aselib::add_pixel_color(aselib::PixelDataGrayscale const& pixel_src,
    aselib::PixelDataRGBA const& pixel_orig, std::uint8_t layer_opacity)
{
    aselib::PixelDataRGBA const pixel_src_rgba { pixel_src.v, pixel_src.v, pixel_src.v,
        pixel_src.a };

    return aselib::add_pixel_color(pixel_src_rgba, pixel_orig, layer_opacity);
}

aselib::PixelDataRGBA aselib::add_pixel_color(aselib::PixelDataIndexed const& pixel_src,
    aselib::PixelDataRGBA const& pixel_orig, aselib::PaletteChunk const& palette,
    std::uint8_t layer_opacity)
{
    auto const index = pixel_src.idx;
    if (palette.m_palette_entries.size() <= index) {
        throw std::invalid_argument { "indexed color index exceeds palette size" };
    }
    auto const& pixel_src_rgba = palette.m_palette_entries.at(index).m_color;

    return aselib::add_pixel_color(pixel_src_rgba, pixel_orig, layer_opacity);
}
