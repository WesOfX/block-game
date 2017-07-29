#pragma once

#include <GL/glew.h>

struct vao{
	GLuint id;
	void load();
	void bind() const;
};
