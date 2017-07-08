#include "chunk.hpp"

std::ostream& operator<<(
	std::ostream& os, 
	const chunk& c
){
	for(auto& layer: c.blocks)
		for(auto& column: layer)
			for(auto& block: column)
				os << block;
	return os;
}

std::istream& operator>>(
	std::istream& is,
	chunk& c
){
	for(auto& layer: c.blocks)
		for(auto& column: layer)
			for(auto& block: column)
				is >> block;
	return is;
}
