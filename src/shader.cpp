#include "shader.hpp"

#include <iostream>
#include <fstream>

shader::shader(
	const std::string& vertex_shader_filename,
	const std::string& fragment_shader_filename
){	
	compile_vertex_shader(vertex_shader_filename);
	compile_fragment_shader(fragment_shader_filename);
	link_shaders();
	glDeleteShader(vertex_shader_id); // no-longer needed
	glDeleteShader(fragment_shader_id); // no-lenger needed
}

void shader::compile_vertex_shader(const std::string& filename){
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	std::ifstream fin(filename);
	std::string shader_source(
		(std::istreambuf_iterator<char>(fin)),
		std::istreambuf_iterator<char>()
	);
	auto c_str{shader_source.c_str()};
	const GLint length{(GLint)shader_source.length()};
	glShaderSource(
		vertex_shader_id, 
		1, 
		&c_str, 
		&length
	);
	glCompileShader(vertex_shader_id);
	int success;
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &success);
	if(!success){
		auto constexpr log_length = 512;
		char info[log_length];
		glGetShaderInfoLog(vertex_shader_id, log_length, nullptr, info);
		std::cout << "vertex shader error: " << info << std::endl;
	}
}

void shader::compile_fragment_shader(const std::string& filename){
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	std::ifstream fin(filename);
	std::string shader_source(
		(std::istreambuf_iterator<char>(fin)),
		std::istreambuf_iterator<char>()
	);
	auto c_str{shader_source.c_str()};
	const GLint length{(GLint)shader_source.length()};
	glShaderSource(
		fragment_shader_id, 
		1, 
		&c_str, 
		&length
	);
	glCompileShader(fragment_shader_id);
	int success;
	glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &success);
	if(!success){
		auto constexpr log_length = 512;
		char info[log_length];
		glGetShaderInfoLog(fragment_shader_id, log_length, nullptr, info);
		std::cout << "fragment shader error: " << info << std::endl;
	}
}

void shader::link_shaders(){
	id = glCreateProgram();
	glAttachShader(id, vertex_shader_id);
	glAttachShader(id, fragment_shader_id);
	glLinkProgram(id);
	int success;
	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if(!success){
		auto constexpr log_length = 512;
		char info[log_length];
		glGetProgramInfoLog(id, log_length, nullptr, info);
		std::cout << "shader linker error: " << info << std::endl;
	}
}

void shader::bind(){
	glUseProgram(id);
}

GLuint shader::get_id() const{
	return id;
}
