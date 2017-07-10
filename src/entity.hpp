#pragma once

#include "vec3.hpp"

struct entity{
	typedef vec3<float> position_type;
	position_type position, velocity;
	
	void move(const position_type& offset);
	void accelerate(const position_type& amount);
	void update();
};
