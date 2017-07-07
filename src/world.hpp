#pragma once

#include <map>
#include "vector.hpp"
#include "chunk.hpp"

typedef vector2_t<int16_t> chunk_position_t;

struct world_t{	
	std::map<chunk_position_t, chunk_t> chunk_map;
	void update_chunks();
};
