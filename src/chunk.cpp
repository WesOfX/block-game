#include "chunk.hpp"

const block& chunk::get(const block_position_type& position) const{
	return blocks.at(position.x).at(position.y).at(position.z);
}

void chunk::set(const block_position_type& position, const block& b){
	blocks.at(position.x).at(position.y).at(position.z) = b;
}

block& chunk::at(const block_position_type& position){
	return blocks.at(position.x).at(position.y).at(position.z);
}

bool chunk::has_updates() const{
	return !block_updates.empty();
}

void chunk::push_update(const block_position_type& block_position){
	block_updates.push(block_position);
}

const chunk::block_position_type& chunk::next_update(){
	return block_updates.front();
}

void chunk::pop_update(){
	block_updates.pop();
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
