#pragma once

#include <vector>
#include <deque>
#include <thread>
#include "entity.hpp"
#include "map.hpp"

struct world{
	~world();
	std::vector<entity> players;
	map m;
	size_t chunk_limit;
	float chunk_loading_distance;
	std::deque<chunk::position_type> chunk_loading_queue;
	std::thread chunk_thread;
	void update();
	/*static float chunk_distance(
		const entity::position_type& entity_position, 
		const chunk::position_type& chunk_position
	);*/
};
