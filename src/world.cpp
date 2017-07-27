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
			for( // For any chunk in range (manhattan distance)
				int row = -chunk_loading_distance; 
				row < chunk_loading_distance; 
				++row
			){
				for(
					int column = -chunk_loading_distance;
					column < chunk_loading_distance;
					++column
				){
					// If the chunk is in range
					if(std::hypot(row, column) < chunk_loading_distance){
						chunk::position_type player_chunk_position{
							(chunk::position_type::coord_type)(
						  		player.position.x / chunk::columns + column
						  	),
						  	(chunk::position_type::coord_type)(
						  		player.position.y / chunk::rows + row
						  	)
						};
						if( // If the chunk is not loaded and not queued to load
							m.chunks.find(player_chunk_position) == m.chunks.end()
						 && std::find(
								chunk_loading_queue.begin(),
								chunk_loading_queue.end(),
								player_chunk_position
							) == chunk_loading_queue.end()
						){
							chunk_loading_queue.push_back(player_chunk_position);
						}
					}
				}
			}
		}
		if(!chunk_loading_queue.empty()){
			// TODO if(chunks.size() == max_loaded_chunks) unload most distant chunk
			auto &player = players.at(
				std::uniform_int_distribution<size_t>(0, players.size() - 1)(rng)
			);
			auto closest_unloaded_chunk = std::min_element(
				chunk_loading_queue.begin(),
				chunk_loading_queue.end(),
				[&player](
					const chunk::position_type& a,
					const chunk::position_type& b
				){
					return std::hypot(
						player.position.x / chunk::columns - a.x,
						player.position.y / chunk::rows - a.y
					) < std::hypot(
						player.position.x / chunk::columns - b.x,
						player.position.y / chunk::rows - b.y
					);
				}
			);
			m.load_chunk(*closest_unloaded_chunk);
			chunk_loading_queue.erase(closest_unloaded_chunk);
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
		for(auto& i: players){
			i.update();
		}
	}
}

void world::join_all_threads(){
	if(chunk_io_thread.joinable()) chunk_io_thread.join();
	if(map_thread.joinable()) map_thread.join();
	if(mob_thread.joinable()) mob_thread.join();
	if(player_thread.joinable()) player_thread.join();
}
