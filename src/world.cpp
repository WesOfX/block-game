#include <algorithm>
#include "world.hpp"

world::~world(){
	if(chunk_io_thread.joinable()) chunk_io_thread.join();
}

void world::update_chunk_map(){
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
						(chunk::position_type::coordinate_type)(
					  		player.position.x / chunk::columns + column
					  	),
					  	(chunk::position_type::coordinate_type)(
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
		if(!chunk_io_thread.joinable()){ // If the thread is not busy
			if(!chunk_loading_queue.empty()){
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
				chunk_io_thread = std::thread(
					&map::load_chunk,
					&m,
					*closest_unloaded_chunk
				);
				chunk_loading_queue.erase(closest_unloaded_chunk);
			}
		} 
		else chunk_io_thread.join();
		chunk_loading_queue.clear(); // Remakes the queue every tick!
	}
	
}

void world::update_blocks(){
	++time_of_day;
	for(auto& i: m.chunks){
		i.second.random_update();
		// create c3x3
	}
}

void world::update_mobs(){
	for(auto& i: mobs){
		i.update();
	}
}

void world::update_players(){
	for(auto& i: players){
		i.update();
	}
}

/*
void world::update(){
	// std::vector<std::thread> chunk_loading_threads;
	for(auto& player: players){
		player.update();
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
						(chunk::position_type::coordinate_type)(
					  		player.position.x / chunk::columns + column
					  	),
					  	(chunk::position_type::coordinate_type)(
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
		if(!chunk_thread.joinable()){ // If the thread is not busy
			if(!chunk_loading_queue.empty()){
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
				chunk_thread = std::thread(
					&map::load_chunk,
					&m,
					*closest_unloaded_chunk
				);
				chunk_loading_queue.erase(closest_unloaded_chunk);
			}
		} 
		else chunk_thread.join();
		chunk_loading_queue.clear(); // Remakes the queue every tick!
	}
}
*/
