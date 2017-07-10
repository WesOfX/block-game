#include "chunk.hpp"

std::ostream& operator<<(
	std::ostream& os, 
	const chunk& c
){
	for(auto& row: c.blocks)
		for(auto& column: row)
			for(auto& block: column)
				os << block;
	return os;
}

std::istream& operator>>(
	std::istream& is,
	chunk& c
){
	for(auto& row: c.blocks)
		for(auto& column: row)
			for(auto& block: column)
				is >> block;
	return is;
}
