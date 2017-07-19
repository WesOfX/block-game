#include "generator.hpp"

chunk generator::operator()(const chunk::position_type& position){
	// TODO
	chunk c;
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::rows; ++column){
			for(size_t layer = chunk::layers - 1; layer != 0; --layer){
				auto value = perlin::noise(
					(float)row / 6,
					(float)column / 6,
					(float)layer / 6
				);
				// c.blocks[row][column][layer].id = block::stone;
				if((value + 1.0f - ((float)layer * 2 / chunk::layers)) > 0.0f){
					if(c.blocks[row][column][layer + 1].id == block::air)
						c.blocks[row][column][layer].id = block::grass;
					else
						c.blocks[row][column][layer].id = block::dirt;
				}
				// else c.blocks[row][column][0].id = block::stone;
			}
		}
	}
	return c;
}
