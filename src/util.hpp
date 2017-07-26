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
		typedef position_type::coord_type coord_type;
		const auto x_hash{std::hash<coord_type>{}(position.x)},
		           y_hash{std::hash<coord_type>{}(position.y)};
		return x_hash ^ (y_hash << 1);
	}
};

typedef std::optional<std::reference_wrapper<chunk>> chunk_ref_opt;
typedef std::array<std::array<chunk_ref_opt, 3>, 3> chunk3x3;
