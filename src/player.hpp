#pragma once

#include <cstdint>
#include "mob.hpp"

struct player: public mob{
	enum input_type: uint8_t{
		forward,
		backward,
		left,
		right,
		jump,
		prone
	};
};
