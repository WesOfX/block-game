#include "chunk.hpp"

const block& chunk::get(const block_position_type& position) const{
	return blocks.at(position.x).at(position.y).at(position.z);
}

block& chunk::at(const block_position_type& position){
	return blocks.at(position.x).at(position.y).at(position.z);
}

void chunk::set(const block_position_type& position, const block& b){
	blocks.at(position.x).at(position.y).at(position.z) = b;
}

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
