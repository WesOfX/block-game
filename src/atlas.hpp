#pragma once

#include <array>
#include <SFML/Graphics/Texture.hpp>
#include "vec2.hpp"

typedef std::array<vec2<float>, 4> uv_quad;

struct atlas{
	size_t rows, columns;
	static constexpr float border = 0.0f, pixel_offset = 0.0f;
	sf::Texture texture;
	uv_quad get_uv(const vec2<size_t>& position) const;
};
