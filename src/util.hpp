#pragma once

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
