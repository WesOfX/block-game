#include "generator.hpp"

void generator::generate_terrain(
	chunk& c,
	const chunk::position_type& position
) const{
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::columns; ++column){
			for(size_t layer = chunk::layers - 1; layer != 0; --layer){
				auto value = perlin::noise(
					((float)position.y * chunk::rows + (float)row) / 5,
					((float)position.x * chunk::columns + (float)column) / 5,
					(float)layer / 5
				);
				if(value > 0.3f) c.set({row, column, layer}, {block::stone, 0, 0});
				else c.set({row, column, layer}, {block::air, 0, 0});
			}
		}
	}
}
