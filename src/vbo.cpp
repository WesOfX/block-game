#include "vbo.hpp"

void vbo::load_from_model(const model& m, vbo::usage u){
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(
		GL_ARRAY_BUFFER, 
		m.vertices.size() * sizeof(vertex),
		&m.vertices.front(),
		u
	);
}

void vbo::bind(){
	glBindBuffer(GL_ARRAY_BUFFER, id);
}
