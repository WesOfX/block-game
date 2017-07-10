#include <iostream>
#include "map.hpp"
#include "entity.hpp"

map m;
entity e{
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f}
};

int main(){
	m.chunks.emplace(
		std::make_pair(
			chunk::position_type{3, 1}, 
			chunk()
		)
	);
	
	m.chunks.at({3, 1}).blocks[0][0][0].id = block::glass;
	
	m.save_chunk({3, 1});
}
