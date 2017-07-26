#pragma once

#include <random>
#include "map.hpp"
#include "entity.hpp"
#include "util.hpp"
	
struct updater{
	typedef std::default_random_engine rng_type;

	rng_type rng = rng_type{rng_type::default_seed};

	void update_sky_light(const chunk3x3& c3x3) const;
	void update_torch_light(const chunk3x3& c3x3) const;
	void update_block(
		const chunk3x3& c3x3, 
		const chunk::block_position_type& block_position
	) const;
	void update_random(const chunk3x3& c3x3);
	void update_mob(decltype(map::chunks) chunks, entity& m) const;
	void update_player(decltype(map::chunks) chunks, entity& p) const;

private:
	enum light_type: bool{sky, torch};
	void flood_all_light(const chunk3x3& c3x3, light_type lt) const;
	void spread_light(block& b, int16_t level, light_type lt) const;
};
