#pragma once

#include <array>
#include <random>
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "block.hpp"

struct chunk{
	typedef vec2<size_t> position_type;
	typedef vec2<size_t> coord_type;
	typedef vec3<size_t> block_position_type;
	typedef block_position_type::coord_type block_coord_type;
	typedef std::default_random_engine rng_type;
	
	static constexpr block_coord_type rows = 16, columns = 16, layers = 64;
	rng_type rng = rng_type{rng_type::default_seed};
	
	const block& get(const block_position_type& position) const;
	block& at(const block_position_type& position);
	void set(const block_position_type& position, const block& b);
	
	void block_update(const block_position_type& position);
	void random_update();
	
	friend std::ostream& operator<<(std::ostream& os, const chunk& c);
	friend std::istream& operator>>(std::istream& is, chunk& c);
	
private:
	std::array<std::array<std::array<block, layers>, columns>, rows> blocks;
};
