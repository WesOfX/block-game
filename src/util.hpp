#pragma once

#include <functional>
#include <optional>
#include <glm/glm.hpp>
#include "chunk.hpp"

// std::hash for chunk positions used for std::unordered_map
template<>
struct std::hash<chunk::position_type>{
	typedef chunk::position_type position_type;
	auto operator()(const position_type& position) const{
		typedef position_type::coordinate_type coordinate_type;
		const auto x_hash{std::hash<coordinate_type>{}(position.x)},
		           y_hash{std::hash<coordinate_type>{}(position.y)};
		return x_hash ^ (y_hash << 1);
	}
};

typedef std::optional<std::reference_wrapper<chunk>> chunk_ref_opt;
typedef std::array<std::array<chunk_ref_opt, 3>, 3> chunk3x3;

// TODO
/*
sf::Glsl::Mat4 camera(const vec3& position, float yaw, float pitch){
	glm::mat4 projection = glm::perspective(
		glm::radians(30.0f),
		4.0f / 3.0f,
		0.1f,
		100.0f
	);
	return {};
}
*/
