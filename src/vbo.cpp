#include "vbo.hpp"

void vbo::load_from_model(const model& m, vbo::usage u){
	vertex_count = m.vertices.size();
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(
		GL_ARRAY_BUFFER, 
		m.vertices.size() * sizeof(vertex),
		&m.vertices.front(),
		u
	);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex),
		(void*)0
	);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex),
		(void*)sizeof(decltype(vertex::position))
	);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex),
		(void*)(
			sizeof(decltype(vertex::position)) 
		  + sizeof(decltype(vertex::normal))
		)
	);
	glEnableVertexAttribArray(0);
}

void vbo::bind(){
	glBindBuffer(GL_ARRAY_BUFFER, id);
}
