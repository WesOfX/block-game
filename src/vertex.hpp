#pragma once

#include "vec3.hpp"
#include "vec2.hpp"

struct vertex{
	vec3<float> position = {};
	vec3<float> normal = {};
	vec3<float> uv = {};
	float sky_light = 0.0f,
	      torch_light = 0.0f;
};
