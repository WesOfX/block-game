#pragma once

#include <array>
#include <iostream>
#include "vec2.hpp"
#include "vec3.hpp"
#include "block.hpp"

struct chunk{
	typedef vec2<size_t> position_type;
	typedef vec3<size_t> block_position_type;
	static constexpr size_t rows = 16, columns = 16, layers = 256;
	const block& get(const block_position_type& position) const;
	block& at(const block_position_type& position);
	void set(const block_position_type& position, const block& b);
	
	friend std::ostream& operator<<(std::ostream& os, const chunk& c);
	friend std::istream& operator>>(std::istream& is, chunk& c);
	
private:
	std::array<std::array<std::array<block, layers>, columns>, rows> blocks;
};
