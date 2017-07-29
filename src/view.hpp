#pragma once

#include "world.hpp"

struct view{
	float fov = 70.0f;
	void update(const world& w);
	void bind();
};
