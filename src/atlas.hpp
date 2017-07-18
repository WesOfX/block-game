#pragma once

#include <array>
#include <GL/glew.h>
#include <SFML/Graphics/Texture.hpp>
#include "vec2.hpp"
#include "vec3.hpp"

typedef std::array<vec3<float>, 4> uv_quad;

struct atlas{
	atlas(const std::string& filename, size_t rows, size_t columns);
	const size_t rows, columns;
	// static constexpr float border = 0.0f, pixel_offset = 0.0f;
	uv_quad get_uv(const vec2<size_t>& position) const;
	void bind() const;
private:
	GLuint id;
};
