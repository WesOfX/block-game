#include <algorithm>
#include "world.hpp"
#include "util.hpp"

world::~world(){
	join_all_threads();
}

void world::update(){
	// if(clock::now() - last_master_tick > master_tick(1.0f)){
	std::this_thread::sleep_for(
		master_tick(1.0f) - (clock::now() - last_master_tick)
	);
	if(clock::now() - last_chunk_io_tick > chunk_io_tick(1.0f)){
		chunk_io_thread = std::thread(&world::update_chunk_io, this);
		last_chunk_io_tick = clock::now();
	}
	if(clock::now() - last_map_tick > map_tick(1.0f)){
		map_thread = std::thread(&world::update_map, this);
		last_map_tick = clock::now();
	}
	if(clock::now() - last_mob_tick > mob_tick(1.0f)){
		mob_thread = std::thread(&world::update_mobs, this);
		last_mob_tick = clock::now();
	}
	if(clock::now() - last_player_tick > player_tick(1.0f)){
		player_thread = std::thread(&world::update_players, this);
		last_player_tick = clock::now();
	}
	last_master_tick = clock::now();
	// }	
	join_all_threads();
}

void world::update_chunk_io(){
	// std::cout << "update chunk io" << std::endl; // TODO REMOVE
	for(auto& player: players){
		// if(!chunk_io_thread.joinable()){ // If the thread is not busy
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
}

void world::update_map(){
	// std::cout << "update map" << std::endl; // TODO REMOVE
	++time_of_day;
	upd.update_map(m);
}

void world::update_mobs(){
	// std::cout << "update mobs" << std::endl; // TODO REMOVE
	for(auto& i: mobs){
		i.update();
	}
}

void world::update_players(){
	// std::cout << "update players" << std::endl; // TODO REMOVE
	for(auto& i: players){
		i.update();
	}
}

void world::join_all_threads(){
	if(chunk_io_thread.joinable()) chunk_io_thread.join();
	if(map_thread.joinable()) map_thread.join();
	if(mob_thread.joinable()) mob_thread.join();
	if(player_thread.joinable()) player_thread.join();
}
