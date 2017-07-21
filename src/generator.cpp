#include "generator.hpp"

void generator::generate_terrain(
	chunk& c,
	const chunk::position_type& position
) const{
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::rows; ++column){
			for(size_t layer = chunk::layers - 1; layer != 0; --layer){
				auto value = perlin::noise(
					(float)row / 8,
					(float)column / 8,
					(float)layer / 4
				);
				if(value > 0.3f){
					if(
						layer == chunk::layers - 1 
					 || c.get({row, column, layer + 1}).id == block::air
					)
						c.set({row, column, layer}, {block::grass, 0, 0});
					else
						c.set({row, column, layer}, {block::dirt, 0, 0});
				}
			}
		}
	}
}

void generator::update_sky_light(chunk& c) const{
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::columns; ++column){
			for(size_t layer = chunk::layers - 1; layer != 0; --layer){
				if(!c.get({row, column, layer}).transparent()) break;
				else c.at({row, column, layer}).sky_light = 15; // max
			}	
		}
	}
	for(uint8_t level = 15; level != 1; --level){
		for(size_t row = 0; row < chunk::rows; ++row){
			for(size_t column = 0; column < chunk::columns; ++column){
				for(size_t layer = 0; layer < chunk::layers; ++layer){
					if(c.get({row, column, layer}).sky_light == level){				      
						if(row > 0){
							auto& back = c.at({row - 1, column, layer});
							if(back.transparent() && back.sky_light < level - 1)
								back.sky_light = level - 1;
						}
						if(row < chunk::rows - 1){
							auto& front = c.at({row + 1, column, layer});
							if(front.transparent() && front.sky_light < level - 1)
								front.sky_light = level - 1;
						}
						if(column > 0){
							auto& left = c.at({row, column - 1, layer});
							if(left.transparent() && left.sky_light < level - 1)
								left.sky_light = level - 1;
						}
						if(column < chunk::columns - 1){
							auto& right = c.at({row, column + 1, layer});
							if(right.transparent() && right.sky_light < level - 1)
								right.sky_light = level - 1;
						}
						if(layer > 0){
							auto& bottom = c.at({row, column, layer - 1});
							if(bottom.transparent() && bottom.sky_light < level - 1)
								bottom.sky_light = level - 1;
						}
						if(layer < chunk::layers - 1){
							auto& top = c.at({row, column, layer + 1});
							if(top.transparent() && top.sky_light < level - 1)
								top.sky_light = level - 1;
						}
					}
				}	
			}
		}
	}
}
