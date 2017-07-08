#include <iostream>
#include "map.hpp"

map m;

int main(){
	m.chunks.emplace(
		std::make_pair(
			chunk::position_type{3, 1}, 
			chunk()
		)
	);
}
