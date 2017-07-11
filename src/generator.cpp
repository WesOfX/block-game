#include "generator.hpp"

chunk generator::operator()(const chunk::position_type& position){
	// TODO
	chunk c;
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::rows; ++column){
			auto value = perlin::noise(
				(float)row / 4,
				(float)column / 4
			);
			if(value > 0.0f) c.blocks[row][column][0].id = block::grass;
			else c.blocks[row][column][0].id = block::stone;
		}
	}
	return c;
}
