#pragma once

#include <array>
#include <iostream>
#include "vec2.hpp"
#include "block.hpp"

struct chunk{
	typedef vec2<int16_t> position_type;
	static constexpr size_t rows = 16, columns = 16, layers = 256;
	std::array<std::array<std::array<block, rows>, columns>, layers> blocks;
};

std::ostream& operator<<(
	std::ostream& os, 
	const chunk& c
);

std::istream& operator>>(
	std::istream& is,
	chunk& c
);
