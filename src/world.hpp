#pragma once

#include <vector>
#include <thread>
#include "entity.hpp"
#include "map.hpp"

struct world{
	~world();
	std::vector<entity> players;
	map m;
	size_t chunk_limit;
	std::thread chunk_loader;
	void update();
};
