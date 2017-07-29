#pragma once

#include <array>
#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>
#include "vec2.hpp"
#include "vec3.hpp"

typedef std::array<vec3<float>, 4> uv_quad;

struct atlas{
	atlas(
		const std::string& filename = "textures/blocks.png", 
		size_t rows = 16, 
		size_t columns = 1
	);
	const size_t rows, columns;
	uv_quad get_uv(const vec2<size_t>& position) const;
	void bind() const;
private:
	GLuint id;
};
