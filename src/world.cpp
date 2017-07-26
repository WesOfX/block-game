#include <algorithm>
#include "world.hpp"
#include "util.hpp"

world::~world(){
	if(chunk_io_thread.joinable()) chunk_io_thread.join();
}

void world::update(){
	if(
		!chunk_map_thread.joinable() 
	 && clock::now() - last_chunk_map_tick > chunk_map_tick(1.0f)
	)
		chunk_map_thread = std::thread(&world::update_chunk_map, this);
	else chunk_map_thread.join();
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
	for(auto& chunk: m.chunks){ // pair<chunk position, chunk>
		chunk3x3 c3x3{
			// TODO
		};
		while(chunk.second.has_updates()){
			upd.update_block(c3x3, chunk.second.next_update());
			chunk.second.pop_update();
		}
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
