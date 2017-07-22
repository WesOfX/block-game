#pragma once

#include "chunk.hpp"

struct updater{
	void update_sky_light(chunk& c) const;
	void update_torch_light(chunk& c) const;

private:
	enum light_type: bool{sky, torch};
	void flood_all_light(chunk& c, light_type lt) const;
	void spread_light(block& b, int16_t level, light_type lt) const;
};
