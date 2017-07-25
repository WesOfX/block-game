#pragma once

#include <GL/glew.h>
#include "modeler.hpp"
#include "vao.hpp"

struct vbo{
	enum usage{
		static_draw = GL_STATIC_DRAW, // rarely changes
		dynamic_draw = GL_DYNAMIC_DRAW // changes frequently
	};
	GLuint id;
	vao va;
	size_t vertex_count;
	void load_from_model(const model& m, usage u);
	void bind();
};
