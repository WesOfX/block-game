#pragma once

#include <chrono>
#include <random>
#include <vector>
#include <deque>
#include <thread>
#include "map.hpp"
#include "mob.hpp"
#include "player.hpp"
#include "updater.hpp"

struct world{
	typedef std::chrono::duration<float, std::ratio<1, 120>> master_tick;
	typedef std::chrono::duration<float, std::ratio<1, 60>> chunk_io_tick;
	typedef std::chrono::duration<float, std::ratio<1, 15>> map_tick;
	typedef std::chrono::duration<float, std::ratio<1, 15>> mob_tick;
	typedef std::chrono::duration<float, std::ratio<1, 60>> player_tick;
	typedef std::chrono::steady_clock clock;
	typedef std::chrono::time_point<clock> time_point;
	typedef std::default_random_engine rng_type;

	float chunk_loading_distance = 8.0f;
	size_t chunk_limit = pow(chunk_loading_distance * M_PI, 2) * 2; // (pi * r) ^ 2
	unsigned day_length = 5000, time_of_day = day_length / 2;
	rng_type rng = rng_type{rng_type::default_seed};
	map m;
	std::vector<player> players;
	std::vector<mob> mobs;
	
	time_point last_master_tick,
	           last_chunk_io_tick, 
	           last_map_tick, 
	           last_mob_tick, 
	           last_player_tick;	
	           
	updater upd;
	
	std::deque<chunk::position_type> chunk_loading_queue;
	std::thread chunk_io_thread, 
	            map_thread,
	            mob_thread,
	            player_thread;
	
	world();
	~world();
	
	void run();
	void start_chunk_io();
	void start_map_updates();
	void start_mob_updates();
	void start_player_updates();
	
private:
	bool running;
	void join_all_threads();
};
