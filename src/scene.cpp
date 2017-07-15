#include "scene.hpp"

void scene::update_chunk_model(
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
}

void scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{

}
