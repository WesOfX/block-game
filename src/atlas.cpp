#include "atlas.hpp"

vec2<float> atlas::get_uv(size_t row, size_t column) const{
	return {
		column * (float)texture.getSize().x / columns,
		row * (float)texture.getSize().y / row
	};
}
