#pragma once

#include <array>
#include <queue>
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "block.hpp"

struct chunk{
	typedef vec2<ptrdiff_t> position_type;
	typedef position_type::coord_type coord_type;
	typedef vec3<size_t> block_position_type;
	typedef block_position_type::coord_type block_coord_type;
	
	static constexpr block_coord_type rows = 16, columns = 16, layers = 128;
	// TODO last block update
	// TODO last light update
	// TODO last save
	// TODO in scene: last_remodel
	
	const block& get(const block_position_type& position) const;
	void set(const block_position_type& position, const block& b);
	block& at(const block_position_type& position);
	
	bool has_updates() const;
	void push_update(const block_position_type& block_position);
	const block_position_type& next_update();
	void pop_update();
	
	friend std::ostream& operator<<(std::ostream& os, const chunk& c);
	friend std::istream& operator>>(std::istream& is, chunk& c);
	
private:
	std::array<std::array<std::array<block, layers>, columns>, rows> blocks;
	std::queue<block_position_type> block_updates;
};
