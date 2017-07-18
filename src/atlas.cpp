#include "atlas.hpp"

uv_quad atlas::get_uv(const vec2<size_t>& position) const{
	// note that the texture is upside down with uv 0, 0 at bottom left
	auto offset_x = pixel_offset / texture.getSize().x,
	     offset_y = pixel_offset / texture.getSize().y;
	return {
		{
			{
				(1.0f / columns) * (position.x) + offset_x,
				(1.0f / rows) * (position.y + 1) - offset_y
			},
			{
				(1.0f / columns) * (position.x + 1) - offset_x,
				(1.0f / rows) * (position.y + 1) - offset_y
			},
			{
				(1.0f / columns) * (position.x + 1) - offset_x,
				(1.0f / rows) * (position.y) + offset_y
			},
			{
				(1.0f / columns) * (position.x) + offset_x,
				(1.0f / rows) * (position.y) + offset_y
			}
		}
	};
}
