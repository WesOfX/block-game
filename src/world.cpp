#include <algorithm>
#include "world.hpp"
#include "util.hpp"

world::world(){
	run();
}

world::~world(){
	running = false;
	join_all_threads();
}

void world::run(){
	running = true;
	chunk_io_thread = std::thread(&world::start_chunk_io, this);
	map_thread = std::thread(&world::start_map_updates, this);
	mob_thread = std::thread(&world::start_mob_updates, this);
	player_thread = std::thread(&world::start_player_updates, this);
}

void world::start_chunk_io(){
	while(running){
		std::this_thread::sleep_for(
			chunk_io_tick(1.0f) - (clock::now() - last_chunk_io_tick)
		);
		for(auto& player: players){
			push_unloaded_chunks_in_range<chunk, chunk>(
				m.chunks, 
				chunk_loading_queue,
				player.position, 
				chunk_loading_distance,
				{}
			);
		}
		if(!chunk_loading_queue.empty()){
			// TODO if(chunks.size() == max_loaded_chunks) unload most distant chunk
			const auto& player = players.at(
				std::uniform_int_distribution<size_t>(0, players.size() - 1)(rng)
			);
			auto& closest_unloaded_chunk = *std::min_element(
				chunk_loading_queue.begin(),
				chunk_loading_queue.end(),
				[&player](
					const chunk::position_type& a,
					const chunk::position_type& b
				){
					return std::hypot(
						player.position.x / chunk::columns - a.x,
						player.position.z / chunk::rows - a.y
					) < std::hypot(
						player.position.x / chunk::columns - b.x,
						player.position.z / chunk::rows - b.y
					);
				}
			);
			m.load_chunk(closest_unloaded_chunk);
		}
		chunk_loading_queue.clear(); // Remakes the queue every tick!
		last_chunk_io_tick = clock::now();
	}
}

void world::start_map_updates(){
	while(running){
		std::this_thread::sleep_for(
			map_tick(1.0f) - (clock::now() - last_map_tick)
		);
		++time_of_day;
		upd.update_map(m);
		last_map_tick = clock::now();
	}
}

void world::start_mob_updates(){
	while(running){
		std::this_thread::sleep_for(
			mob_tick(1.0f) - (clock::now() - last_mob_tick)
		);
		for(auto& i: mobs){
			i.update();
		}
		last_mob_tick = clock::now();
	}
}

void world::start_player_updates(){
	while(running){
		std::this_thread::sleep_for(
			player_tick(1.0f) - (clock::now() - last_player_tick)
		);
		for(auto& i: players){
			i.update();
		}
		last_player_tick = clock::now();
	}
}

void world::join_all_threads(){
	if(chunk_io_thread.joinable()) chunk_io_thread.join();
	if(map_thread.joinable()) map_thread.join();
	if(mob_thread.joinable()) mob_thread.join();
	if(player_thread.joinable()) player_thread.join();
}
