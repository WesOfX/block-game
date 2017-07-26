#pragma once

#include "map.hpp"
#include "entity.hpp"
#include "util.hpp"
	
struct updater{
	void update_sky_light(const chunk3x3& chunks) const;
	void update_torch_light(const chunk3x3& chunks) const;
	void update_blocks(const chunk3x3& chunks) const;
	void update_mob(decltype(map::chunks) chunks, entity& m) const;
	void update_player(decltype(map::chunks) chunks, entity& p) const;

private:
	enum light_type: bool{sky, torch};
	void flood_all_light(const chunk3x3& chunks, light_type lt) const;
	void spread_light(block& b, int16_t level, light_type lt) const;
};
