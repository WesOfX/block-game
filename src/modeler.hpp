#pragma once

#include <vector>
#include <optional>
#include "vertex.hpp"
#include "chunk.hpp"
#include "atlas.hpp"

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
		const chunk& c,
		const std::optional<chunk>& north_chunk = {},
		const std::optional<chunk>& east_chunk = {},
		const std::optional<chunk>& south_chunk = {},
		const std::optional<chunk>& west_chunk = {}
	) const;
	quad generate_block_face(
		block::id_type id,
		const chunk::block_position_type& position, 
		block_face face
	) const;
	static vec2<size_t> atlas_position(
		block::id_type id, 
		block_face face
	);
};
