#pragma once

#include <vector>
#include <optional>
#include "vertex.hpp"
#include "chunk.hpp"
#include "atlas.hpp"
#include "util.hpp"

struct model{
	std::vector<vertex> vertices;
};

typedef std::array<vertex, 4> quad;

struct modeler{
	enum block_face: uint8_t{
		top,
		bottom,
		front,
		back,
		left,
		right
	};
	atlas block_atlas;
	// bool smooth_lighting;
	modeler();
	model generate_chunk_model(
		const chunk3x3& chunks,
		const chunk::position_type& position = {0, 0}
	) const;
	quad generate_block_face(
		const block& b,
		const chunk& c,
		const chunk::block_position_type& position, 
		block_face face,
		const chunk::position_type& chunk_position
	) const;
	/*void position_quad(
		quad& q,
		block_face, face
	) const;*/
	static vec2<size_t> atlas_position(
		block::id_type id, 
		block_face face
	);
};
