#pragma once

#include "chunk.hpp"

struct updater{
	void update_sky_light(chunk& c) const;
	void update_torch_light(chunk& c) const;
};
