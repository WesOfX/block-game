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

void chunk::set_sky_light(const block_position_type& position, uint8_t value){
	blocks.at(position.x).at(position.y).at(position.z).sky_light = value;
}

void chunk::update_light(){
	// update skylight
	for(auto& row: blocks){
		for(auto& column: row){
			for(size_t layer = layers - 1; layer != 0; --layer){
				if(!column[layer].transparent()) break;
				else column[layer].sky_light = 15; // max
			}	
		}
	}
	for(uint8_t level = 15; level != 1; --level){
		for(size_t row = 0; row < rows; ++row){
			for(size_t column = 0; column < columns; ++column){
				for(size_t layer = 0; layer < layers; ++layer){
					if(get({row, column, layer}).sky_light == level){
						/*auto& top = at({row, column, layer + 1}),
						      bottom = at({row, column, layer - 1}),
						      front = at({row + 1, column, layer}),
						      back = at({row - 1, column, layer}),
						      left = at({row, column - 1, layer}),
						      right = at({row, column + 1, layer});*/					      
						if(row > 0){
							auto& back = at({row - 1, column, layer});
							if(back.transparent() && back.sky_light < level - 1)
								back.sky_light = level - 1;
						}
						if(row < rows - 1){
							auto& front = at({row + 1, column, layer});
							if(front.transparent() && front.sky_light < level - 1)
								front.sky_light = level - 1;
						}
						if(column > 0){
							auto& left = at({row, column - 1, layer});
							if(left.transparent() && left.sky_light < level - 1)
								left.sky_light = level - 1;
						}
						if(column < columns - 1){
							auto& right = at({row, column + 1, layer});
							if(right.transparent() && right.sky_light < level - 1)
								right.sky_light = level - 1;
						}
						if(layer > 0){
							auto& bottom = at({row, column, layer - 1});
							if(bottom.transparent() && bottom.sky_light < level - 1)
								bottom.sky_light = level - 1;
						}
						if(layer < layers - 1){
							auto& top = at({row, column, layer + 1});
							if(top.transparent() && top.sky_light < level - 1)
								top.sky_light = level - 1;
						}
					}
				}	
			}
		}
	}
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
