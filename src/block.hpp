#pragma once

#include <cstdint>

struct block_t{
	enum class id_t: uint8_t{
		grass,
		dirt,
		stone,
		glass
	};
	
	id_t id;
	
	bool transparent() const;
};
