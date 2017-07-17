#include "vao.hpp"

void vao::load(){
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}

void vao::bind(){
	glBindVertexArray(id);
}
