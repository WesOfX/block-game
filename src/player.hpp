#pragma once

#include <cstdint>
#include "mob.hpp"

struct player: public mob{
	bool forward = false,
	     backward = false,
	     left = false,
	     right = false,
	     jump = false,
	     prone = false;	     
	
	void update_input();
};
