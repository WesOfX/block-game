#pragma once

#include <vector>
#include <deque>
#include <thread>
#include "updater.hpp"

struct world{
	// typedef std::chrono::duration<float, std::ratio<1, 1000>> main_tick;
	typedef std::chrono::duration<float, std::ratio<1, 100>> chunk_map_tick;
	typedef std::chrono::duration<float, std::ratio<1, 10>> block_tick;
	typedef std::chrono::duration<float, std::ratio<1, 25>> mob_tick;
	typedef std::chrono::duration<float, std::ratio<1, 50>> player_tick;
	typedef std::chrono::steady_clock clock;
	typedef std::chrono::time_point<clock> time_point;

	float chunk_loading_distance = 8;
	size_t chunk_limit = pow(chunk_loading_distance * M_PI, 2) * 7; // (pi * r) ^ 2
	unsigned day_length = 5000, time_of_day = day_length / 2;
	map m;
	std::vector<entity> players, mobs;
	
	time_point // last_main_tick,
	           last_chunk_map_tick, 
	           last_block_tick, 
	           last_mob_tick, 
	           last_player_tick;	
	           
	updater upd;
	
	std::deque<chunk::position_type> chunk_loading_queue;
	std::thread chunk_io_thread, 
	            chunk_map_thread,
	            block_thread,
	            mob_thread,
	            player_thread;
	
	~world();
	
	void update();
	void update_chunk_map();
	void update_blocks();
	void update_mobs();
	void update_players();
};
