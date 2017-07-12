#include "world.hpp"

world::~world(){
	chunk_loader.join();
}

void world::update(){
	// std::vector<std::thread> chunk_loading_threads;
	for(auto& i: players){
		chunk_loader = std::thread(
			&map::load_chunk,
			&m,
			chunk::position_type{
				(chunk::position_type::coordinate_type)(i.position.x / chunk::columns),
				(chunk::position_type::coordinate_type)(i.position.y / chunk::rows)
			}
		);
	}
}
