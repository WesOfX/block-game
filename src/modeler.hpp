#pragma once

#include <vector>
#include "vertex.hpp"
#include "chunk.hpp"

typedef std::vector<vertex> model;
typedef std::array<vertex, 4> rect;

struct modeler{
	enum block_face: uint8_t{
		top,
		bottom,
		front,
		back,
		left,
		right
	};
	model generate_chunk_model(const chunk& c) const;
	rect generate_block_face(
		block::id_type id,
		const chunk::block_position_type& position, 
		block_face face
	) const;
};

void bind(const model& m);
