#include <iostream>
#include "map.hpp"
#include "entity.hpp"
#include "generator.hpp"

map m;
chunk c;
entity e{
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f}
};
generator g;
chunk::position_type p{3, 1};

int main(){
	c = g(p);

	m.chunks.insert({p, c});
	
	m.save_chunk(p);
}
