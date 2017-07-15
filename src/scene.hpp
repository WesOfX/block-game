#pragma once

#include <unordered_map>
#include <SFML/Graphics/Drawable.hpp>
#include "modeler.hpp"
#include "util.hpp"

struct scene: public sf::Drawable{
	modeler chunk_modeler;
	std::unordered_map<chunk::position_type, model> chunk_models;
	void update_chunk_model(
		const chunk::position_type& position, 
		const chunk& c
		// const chunk::block_position_type& updated_block
	);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
