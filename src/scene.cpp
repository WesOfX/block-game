#include "scene.hpp"

scene::scene(const world& w):
	w(w),
	scene_shader{
 		"shaders/vertex_shader",
 		"shaders/fragment_shader"
 	},
 	mvp_id{glGetUniformLocation(scene_shader.get_id(), "mvp")},
 	sampler_id{glGetUniformLocation(scene_shader.get_id(), "sampler")}
{}

void scene::update(){
	auto& player = w.players.back(); // TODO
	
	/*for( // For any chunk in range (manhattan distance)
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
				chunk::position_type chunk_position{
					(chunk::position_type::coord_type)(
				  		player.position.x / chunk::columns + column
				  	),
				  	(chunk::position_type::coord_type)(
				  		player.position.z / chunk::rows + row
				  	)
				};
				if( // If the chunk is loaded and the chunk model is not loaded and not queued to load
					w.m.chunks.find(chunk_position) != w.m.chunks.end()
				 && chunk_models.find(chunk_position) == chunk_models.end()
				) model_loading_queue.push_back(chunk_position);
			}
		}
	}*/
	push_unloaded_chunks_in_range<vbo, chunk>( // TODO replace with for_all_chunks_in_range_do
		chunk_models,
		model_loading_queue,
		player.position,
		render_distance,
		w.m.chunks
	);
	if(!model_loading_queue.empty()){
		// TODO if(chunk_models.size() == max_loaded_models) unload most distant chunk model
		auto closest_unloaded_model = *std::min_element(
			model_loading_queue.begin(),
			model_loading_queue.end(),
			[&player](
				const chunk::position_type& a,
				const chunk::position_type& b
			){
				return std::hypot(
					player.position.x / chunk::columns - a.x,
					player.position.z / chunk::rows - a.y
				) < std::hypot(
					player.position.x / chunk::columns - b.x,
					player.position.z / chunk::rows - b.y
				);
			}
		);
		const_chunk3x3 c3x3;
		for(auto r = 0; r < 3; ++r){
			for(auto c = 0; c < 3; ++c){
				chunk::position_type p{
					closest_unloaded_model.x + c - 1,
					closest_unloaded_model.y + r - 1
				};
				if(w.m.chunks.find(p) != w.m.chunks.end())
					c3x3[r][c] = w.m.chunks.at(p);
				else
					c3x3[r][c] = {};
			}
		}
		chunk_models.emplace(
			closest_unloaded_model, 
			chunk_modeler.generate_chunk_model(c3x3, closest_unloaded_model)
		);
	}
	model_loading_queue.clear(); // Remakes the queue every tick!
}

void scene::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	auto& player = w.players.back(); // TODO

	glm::mat4 projection = glm::perspective(
		glm::radians(fov), 
		(float)target.getSize().x / target.getSize().y, 
		0.1f, 
		render_distance * std::max(chunk::rows, chunk::columns)
	);
	
	glm::mat4 view = glm::lookAt(
		glm::vec3(player.position.x, player.position.y, player.position.z),
		glm::vec3(player.position.x, player.position.y, player.position.z + 1),
		glm::vec3(0, 1, 0)
	);
	
	glm::mat4 model{1.0f};
	
	glm::mat4 mvp = projection * view * model;
	
	scene_shader.bind();
	
	glUniformMatrix4fv(mvp_id, 1, GL_FALSE, &mvp[0][0]);
	glUniform1i(sampler_id, 0);
	
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
				chunk::position_type chunk_position{
					(chunk::position_type::coord_type)(
				  		player.position.x / chunk::columns + column
				  	),
				  	(chunk::position_type::coord_type)(
				  		player.position.y / chunk::rows + row
				  	)
				};
				if(chunk_models.find(chunk_position) != chunk_models.end()){
					const auto& cm = chunk_models.at(chunk_position);
					cm.bind();
					glDrawArrays(GL_QUADS, 0, cm.vertex_count);
				}
			}
		}
	}
}
