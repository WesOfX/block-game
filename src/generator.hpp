#pragma once

#include "chunk.hpp"
#include "noise.hpp"

struct generator{
	chunk operator()(const chunk::position_type& position);
};
