#include "scene.hpp"

/*void scene::update_chunk_model(
	const chunk::position_type& position, 
	const chunk& c
	// const chunk::block_position_type& updated_block
){
	if(chunk_models.find(position) == chunk_models.end()){
		chunk_models.emplace(
			position,
			chunk_modeler.generate_chunk_model(c)
		);
		// generate model from scratch
	}
	else{
		// update current model
	}
}*/

void scene::update(const world& w){
	// TODO
	// if maximum models are loaded unload most distance model
	// model closest unmodeled loaded chunk
	
	// if(w.m.chunks.find(/*position*/) == w.m.chunks.end())
	
	// TODO get player reference
	auto& player = w.players.back();
	
	for( // For any chunk in range (manhattan distance)
		int row = -render_distance; 
		row < render_distance; 
		++row
	){
		for(
			int column = -render_distance;
			column < render_distance;
			++column
		){
			// If the chunk is in range
			if(std::hypot(row, column) < render_distance){
				chunk::position_type player_chunk_position{
					(chunk::position_type::coord_type)(
				  		player.position.x / chunk::columns + column
				  	),
				  	(chunk::position_type::coord_type)(
				  		player.position.y / chunk::rows + row
				  	)
				};
				if( // If the chunk model is not loaded and not queued to load
					chunk_models.find(player_chunk_position) == chunk_models.end()
				 && std::find(
						model_loading_queue.begin(),
						model_loading_queue.end(),
						player_chunk_position
					) == model_loading_queue.end()
				){
					model_loading_queue.push_back(player_chunk_position);
				}
			}
		}
	}
	if(!model_loading_queue.empty()){
		// TODO if(chunk_models.size() == max_loaded_models) unload most distant chunk model
		auto closest_unloaded_model = std::min_element(
			model_loading_queue.begin(),
			model_loading_queue.end(),
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
		// TODO create chunk3x3
		// chunk_modeler.generate_chunk_model(*closest_unloaded_model);
		// model_loading_queue.erase(closest_unloaded_model);
	}
	model_loading_queue.clear(); // Remakes the queue every tick!
}

void scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	// TODO
	// create view matrix
	// cull invisible chunks
	// draw all chunks in range with fog
}

void scene::set_map(std::shared_ptr<map> m_ptr){
	map_ptr = m_ptr;
}
