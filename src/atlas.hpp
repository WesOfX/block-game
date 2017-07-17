#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "vec2.hpp"

struct atlas{
	static constexpr size_t rows = 16, columns = 16;
	sf::Texture texture;
	vec2<float> get_uv(size_t row, size_t column) const;
};
