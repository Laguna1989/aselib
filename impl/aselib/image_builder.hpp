#ifndef ASEPRITELIB_IMAGE_BUILDER_HPP
#define ASEPRITELIB_IMAGE_BUILDER_HPP

#include <aselib/aseprite_data.hpp>
#include <aselib/image.hpp>

namespace aselib {

Image makeImageFromAse(AsepriteData const& ase);

Image makeImageFromLayer(AsepriteData const& ase, std::string const& layerName);

} // namespace aselib

#endif // ASEPRITELIB_IMAGE_BUILDER_HPP
