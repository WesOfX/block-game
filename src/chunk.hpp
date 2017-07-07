#pragma once

#include <array>
#include <vector>
#include "block.hpp"
#include "entity.hpp"

struct chunk_t{
	static constexpr size_t rows = 16, columns = 16, layers = 256;	
	std::array<std::array<std::array<block_t, layers>, columns>, rows> blocks;
	std::vector<entity_t> entities;
	void update_blocks();
	void update_entities(); //std::chrono?
};
