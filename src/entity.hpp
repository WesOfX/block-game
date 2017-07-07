#pragma once

#include "vector.hpp"

struct entity_t{
	typedef vector3_t<float> position_t, velocity_t;
	position_t position;
	velocity_t velocity;
	void move(position_t offset);
	void accelerate(velocity_t ammount);
	void update(); //std::chrono?
};
