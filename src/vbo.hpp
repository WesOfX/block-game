#pragma once

#include <GL/glew.h>
#include "modeler.hpp"

struct vbo{
	enum usage: uint8_t{
		static_draw, // rarely changes
		dynamic_draw // changes frequently
	};
	GLuint id;
	void load_from_model(const model& m, usage u);
	void bind();
};
