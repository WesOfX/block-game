#pragma once

#include <functional>
#include <optional>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp> // TODO Remove
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "chunk.hpp"
#include "entity.hpp"

// std::hash for chunk positions used for std::unordered_map
template<>
struct std::hash<chunk::position_type>{
	typedef chunk::position_type position_type;
	auto operator()(const position_type& position) const{
		typedef position_type::coord_type coord_type;
		const auto x_hash{std::hash<coord_type>{}(position.x)},
		           y_hash{std::hash<coord_type>{}(position.y)};
		return x_hash ^ (y_hash << 1);
	}
};

typedef std::optional<std::reference_wrapper<const chunk>> const_chunk_ref_opt;
typedef std::array<std::array<const_chunk_ref_opt, 3>, 3> const_chunk3x3;
typedef std::optional<std::reference_wrapper<chunk>> chunk_ref_opt;
typedef std::array<std::array<chunk_ref_opt, 3>, 3> chunk3x3;

template<class element_t, class required_element_t>
void push_unloaded_chunks_in_range(
	std::unordered_map<chunk::position_type, element_t> map, 
	std::deque<chunk::position_type>& queue,
	const entity::position_type& position,
	float range,
	const std::optional<
		std::unordered_map<
			chunk::position_type, 
			required_element_t
		>
	> required = {}
){
	 // For any chunk in range (manhattan distance)
	for(int row = -range; row < range; ++row){
		for(int column = -range; column < range; ++column){
			// If the chunk is in range
			if(std::hypot(row, column) < range){
				chunk::position_type chunk_position{
					(chunk::position_type::coord_type)(
				  		position.x / chunk::rows + row
				  	),
					(chunk::position_type::coord_type)(
				  		position.z / chunk::columns + column
				  	)
				};
				if(map.find(chunk_position) == map.end()
				&& (
						!required
					 || required.value().find(chunk_position) 
					 != required.value().end()
				   )
				) queue.push_back(chunk_position);
			}
		}
	}
}
