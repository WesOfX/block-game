#pragma once

#include <memory>
#include <unordered_map>
#include <SFML/Graphics/Drawable.hpp>
#include "world.hpp"
#include "modeler.hpp"
#include "vbo.hpp"
#include "shader.hpp"
#include "view.hpp"
#include "util.hpp"

struct scene: public sf::Drawable{
	const world& w;
	float render_distance = 32.0f;
	size_t chunk_model_limit = pow(render_distance * M_PI, 2) * 2; 
	modeler chunk_modeler;
	std::unordered_map<chunk::position_type, vbo> chunk_models;
	float fov = 100.0f;
	std::deque<chunk::position_type> model_loading_queue;
	std::thread model_thread;
	shader scene_shader;
	GLuint mvp_id, sampler_id;
		
	scene(const world& w);
	void update();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
