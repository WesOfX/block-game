#include <algorithm>
#include "world.hpp"

world::~world(){
	if(chunk_thread.joinable()) chunk_thread.join();
}

void world::update(){
	// std::vector<std::thread> chunk_loading_threads;
	for(auto& player: players){
		player.update();
		for(
			int row = -chunk_loading_distance; 
			row < chunk_loading_distance; 
			++row
		){
			for(
				int column = -chunk_loading_distance;
				column < chunk_loading_distance;
				++column
			){
				if(std::hypot(row, column) < chunk_loading_distance){
					chunk::position_type chunk_position{
						(chunk::position_type::coordinate_type)(
					  		player.position.x / chunk::columns + column
					  	),
					  	(chunk::position_type::coordinate_type)(
					  		player.position.y / chunk::rows + row
					  	)
					};
					if( 
						m.chunks.find(chunk_position) == m.chunks.end()
					 && std::find(
							chunk_loading_queue.begin(),
							chunk_loading_queue.end(),
							chunk_position
						) == chunk_loading_queue.end()
					){
						chunk_loading_queue.push_back(chunk_position);
					}
				}
			} 
		}
		if(!chunk_thread.joinable()){
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
		chunk_loading_queue.clear();
	}
}

/*static float chunk_distance(
	const entity::position_type& entity_position, 
	const chunk::position_type& chunk_position
){
	return std::hypot(
		entity_position.x / chunk::columns - chunk_position.x,
		entity_position.y / chunk::rows - chunk_position.y
	);
}*/
