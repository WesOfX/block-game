#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/Graphics/Drawable.hpp>
#include "world.hpp"
#include "modeler.hpp"
#include "util.hpp"

struct scene: public sf::Drawable{
	float render_distance = 8.0f;
	size_t chunk_model_limit = pow(render_distance * M_PI, 2) * 2; 
	modeler chunk_modeler;
	std::unordered_map<chunk::position_type, model> chunk_models;
	std::deque<chunk::position_type> model_loading_queue;
	std::thread model_thread;
	/*void update_chunk_models(
		const chunk::position_type& position, 
		const chunk& c
		// const chunk::block_position_type& updated_block
	);*/
		
	void update(const world& w);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void set_map(std::shared_ptr<map> m_ptr);
	
private:	
	std::weak_ptr<map> map_ptr;
};
