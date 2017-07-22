#include "updater.hpp"

void updater::update_sky_light(chunk& c) const{
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::columns; ++column){
			uint8_t sky_light = 15;
			for(size_t layer = chunk::layers - 1; layer != 0; --layer){
				/*if(!c.get({row, column, layer}).transparent()) break;
				else c.at({row, column, layer}).sky_light = 15; // max*/
				sky_light -= std::min(
					sky_light, 
					c.get({row, column, layer}).opacity()
				);
				c.at({row, column, layer}).sky_light = sky_light;
				if(!sky_light) break;
			}	
		}
	}
	flood_all_light(c, sky);
}

void updater::update_torch_light(chunk& c) const{
	for(size_t row = 0; row < chunk::rows; ++row){
		for(size_t column = 0; column < chunk::columns; ++column){
			for(size_t layer = 0; layer < chunk::layers; ++layer){
				c.at({row, column, layer}).torch_light 
			  = c.get({row, column, layer}).emittance();
			}
		}
	}	
	flood_all_light(c, torch);
}

void updater::flood_all_light(chunk& c, updater::light_type lt) const{
	for(int16_t level = 15; level != 1; --level){
		for(size_t row = 0; row < chunk::rows; ++row){
			for(size_t column = 0; column < chunk::columns; ++column){
				for(size_t layer = 0; layer < chunk::layers; ++layer){
					if(
						(lt == sky && c.get({row, column, layer}).sky_light == level)
					 || (lt == torch && c.get({row, column, layer}).torch_light == level)
					){					      
						if(row > 0){
							auto& target = c.at({row - 1, column, layer});
							spread_light(target, level, lt);
						}
						if(row < chunk::rows - 1){
							auto& target = c.at({row + 1, column, layer});
							spread_light(target, level, lt);
						}
						if(column > 0){
							auto& target = c.at({row, column - 1, layer});
							spread_light(target, level, lt);
						}
						if(column < chunk::columns - 1){
							auto& target = c.at({row, column + 1, layer});
							spread_light(target, level, lt);
						}
						if(layer > 0){
							auto& target = c.at({row, column, layer - 1});
							spread_light(target, level, lt);
						}
						if(layer < chunk::layers - 1){
							auto& target = c.at({row, column, layer + 1});
							spread_light(target, level, lt);
						}
					}
				}	
			}
		}
	}
}

void updater::spread_light(block& b, int16_t level, light_type lt) const{
	(lt == sky ? b.sky_light : b.torch_light) = std::max<uint8_t>(
		lt == sky ? b.sky_light : b.torch_light,
		std::max(level - (int)b.opacity() - 1, 0)
	);
}
