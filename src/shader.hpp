#pragma once

#include <string>
#include <GL/glew.h>

struct shader{
	shader(
		const std::string& vertex_shader_filename,
		const std::string& fragment_shader_filename
	);
	void bind() const;
	GLuint get_id() const;
private:
	GLuint id, vertex_shader_id, fragment_shader_id;
	void compile_vertex_shader(const std::string& filename);
	void compile_fragment_shader(const std::string& filename);
	void link_shaders();
};
