#pragma once

#include <vector>
#include <deque>
#include <random>
#include <thread>
#include "entity.hpp"
#include "map.hpp"

struct world{
	typedef std::chrono::duration<float, std::ratio<1, 10>> block_tick;
	typedef std::chrono::duration<float, std::ratio<1, 24>> mob_tick;
	typedef std::chrono::duration<float, std::ratio<1, 50>> player_tick;
	typedef std::chrono::steady_clock clock;
	typedef std::chrono::time_point<clock> time_point;
	typedef std::default_random_engine rng_type;

	float chunk_loading_distance = 8;
	size_t chunk_limit = pow(chunk_loading_distance * M_PI, 2) * 7; // (pi * r) ^ 2
	unsigned day_length = 5000, time_of_day = day_length / 2;
	rng_type rng = rng_type{rng_type::default_seed};
	map m;
	std::vector<entity> players, mobs;
	
	time_point last_time_of_day_tick, 
	           last_block_tick, 
	           last_mob_tick, 
	           last_player_tick;	
	
	std::deque<chunk::position_type> chunk_loading_queue;
	std::thread chunk_io_thread, chunk_map_thread;
	~world();
	
	void update_chunk_map();
	void update_blocks();
	void update_mobs();
	void update_players();
	void update_random_block();
};
