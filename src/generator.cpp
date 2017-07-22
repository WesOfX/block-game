#include "generator.hpp"

void generator::generate_terrain(
	chunk& c,
	const chunk::position_type& position
) const{
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::rows; ++column){
			for(size_t layer = chunk::layers - 1; layer != 0; --layer){
				auto value = perlin::noise(
					(float)row / 12,
					(float)column / 12,
					(float)layer / 4
				);
				if(value > 0.2f){
					if(
						layer == chunk::layers - 1 
					 || c.get({row, column, layer + 1}).id == block::air
					)
						// c.set({row, column, layer}, {block::leaves, 0, 0});
						c.set({row, column, layer}, {block::stone, 0, 0});
					else
						// c.set({row, column, layer}, {block::leaves, 0, 0});
						c.set({row, column, layer}, {block::stone, 0, 0});
				}
				// if(layer == 254) c.at({row, column, layer}) = {block::stone};
			}
		}
	}
}
