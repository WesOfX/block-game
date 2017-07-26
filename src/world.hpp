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
	typedef std::chrono::duration<float, std::ratio<1, 100>> chunk_io_tick;
	typedef std::chrono::duration<float, std::ratio<1, 10>> map_tick;
	typedef std::chrono::duration<float, std::ratio<1, 25>> mob_tick;
	typedef std::chrono::duration<float, std::ratio<1, 50>> player_tick;
	typedef std::chrono::steady_clock clock;
	typedef std::chrono::time_point<clock> time_point;
	typedef std::default_random_engine rng_type;

	float chunk_loading_distance = 8;
	size_t chunk_limit = pow(chunk_loading_distance * M_PI, 2) * 7; // (pi * r) ^ 2
	unsigned day_length = 5000, time_of_day = day_length / 2;
	rng_type rng = rng_type{rng_type::default_seed};
	map m;
	std::vector<player> players;
	std::vector<mob> mobs;
	
	time_point // last_main_tick,
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
	
	~world();
	
	void update();
	void update_chunk_io();
	void update_map();
	void update_mobs();
	void update_players();
};
