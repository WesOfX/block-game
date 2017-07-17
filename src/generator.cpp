#include "generator.hpp"

chunk generator::operator()(const chunk::position_type& position){
	// TODO
	chunk c;
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::rows; ++column){
			for(size_t layer = 0; layer < chunk::layers; ++layer){
				auto value = perlin::noise(
					(float)row / 6,
					(float)column / 6,
					(float)layer / 6
				);
				// c.blocks[row][column][layer].id = block::stone;
				if(value > 0.2f) c.blocks[row][column][layer].id = block::stone;
				// else c.blocks[row][column][0].id = block::stone;
			}
		}
	}
	return c;
}
