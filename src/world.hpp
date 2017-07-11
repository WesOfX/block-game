#pragma once

#include <vector>
#include "entity.hpp"
#include "map.hpp"

struct world{
	std::vector<entity> players;
	map m;
	size_t chunk_limit;
	void update();
};
