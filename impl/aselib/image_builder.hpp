#ifndef ASELIB_IMAGE_BUILDER_HPP
#define ASELIB_IMAGE_BUILDER_HPP

#include <aselib/aseprite_data.hpp>
#include <aselib/image.hpp>

namespace aselib {

[[nodiscard]] Image makeImageFromAse(AsepriteData const& ase, bool include_invisible_layers = true);

[[nodiscard]] Image makeImageFromLayer(AsepriteData const& ase, std::string const& layerName);

} // namespace aselib

#endif // ASELIB_IMAGE_BUILDER_HPP
