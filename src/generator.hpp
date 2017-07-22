#pragma once

#include "chunk.hpp"
#include "noise.hpp"

struct generator{
	void generate_terrain(
		chunk& c,
		const chunk::position_type& position
	) const;
};
