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
	for(int16_t level = 15; level != 1; --level){
		for(size_t row = 0; row < chunk::rows; ++row){
			for(size_t column = 0; column < chunk::columns; ++column){
				for(size_t layer = 0; layer < chunk::layers; ++layer){
					if(c.get({row, column, layer}).sky_light == level){				      
						if(row > 0){
							auto& target = c.at({row - 1, column, layer});
							target.sky_light = std::max<uint8_t>(
								target.sky_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(row < chunk::rows - 1){
							auto& target = c.at({row + 1, column, layer});
							target.sky_light = std::max<uint8_t>(
								target.sky_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(column > 0){
							auto& target = c.at({row, column - 1, layer});
							target.sky_light = std::max<uint8_t>(
								target.sky_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(column < chunk::columns - 1){
							auto& target = c.at({row, column + 1, layer});
							target.sky_light = std::max<uint8_t>(
								target.sky_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(layer > 0){
							auto& target = c.at({row, column, layer - 1});
							target.sky_light = std::max<uint8_t>(
								target.sky_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(layer < chunk::layers - 1){
							auto& target = c.at({row, column, layer + 1});
							target.sky_light = std::max<uint8_t>(
								target.sky_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
					}
				}	
			}
		}
	}
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
	for(int16_t level = 15; level != 1; --level){
		for(size_t row = 0; row < chunk::rows; ++row){
			for(size_t column = 0; column < chunk::columns; ++column){
				for(size_t layer = 0; layer < chunk::layers; ++layer){
					if(c.get({row, column, layer}).torch_light == level){				      
						if(row > 0){
							auto& target = c.at({row - 1, column, layer});
							target.torch_light = std::max<uint8_t>(
								target.torch_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(row < chunk::rows - 1){
							auto& target = c.at({row + 1, column, layer});
							target.torch_light = std::max<uint8_t>(
								target.torch_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(column > 0){
							auto& target = c.at({row, column - 1, layer});
							target.torch_light = std::max<uint8_t>(
								target.torch_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(column < chunk::columns - 1){
							auto& target = c.at({row, column + 1, layer});
							target.torch_light = std::max<uint8_t>(
								target.torch_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(layer > 0){
							auto& target = c.at({row, column, layer - 1});
							target.torch_light = std::max<uint8_t>(
								target.torch_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
						if(layer < chunk::layers - 1){
							auto& target = c.at({row, column, layer + 1});
							target.torch_light = std::max<uint8_t>(
								target.torch_light,
								std::max(level - (int)target.opacity() - 1, 0)
							);
						}
					}
				}	
			}
		}
	}
}
