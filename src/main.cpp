#include <iostream>
#include "map.hpp"
#include "entity.hpp"

map m;
entity e{
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f}
};
chunk::position_type p{3, 1};

int main(){	
	m.load_chunk(p);	
	m.save_chunk(p);
}
