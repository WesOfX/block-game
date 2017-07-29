#include "vbo.hpp"

vbo::vbo(const model& m, usage u){
	load_from_model(m, u);
}

void vbo::load_from_model(const model& m, usage u){
	vertex_count = m.vertices.size();
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(
		GL_ARRAY_BUFFER, 
		m.vertices.size() * sizeof(vertex),
		&m.vertices.front(),
		u
	);
	va.load();
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
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,
		1,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex),
		(void*)(
			sizeof(decltype(vertex::position)) 
		  + sizeof(decltype(vertex::normal))
		  + sizeof(decltype(vertex::uv))
		)
	);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
		4,
		1,
		GL_FLOAT,
		GL_FALSE,
		sizeof(vertex),
		(void*)(
			sizeof(decltype(vertex::position)) 
		  + sizeof(decltype(vertex::normal))
		  + sizeof(decltype(vertex::uv))
		  + sizeof(decltype(vertex::sky_light))
		)
	);
	glEnableVertexAttribArray(0);
}

void vbo::bind() const{
	glBindBuffer(GL_ARRAY_BUFFER, id);
	va.bind();
}
