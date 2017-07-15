#pragma once

#include <iostream>

struct block{
	enum id_type: uint8_t{
		air,
		grass,
		dirt,
		stone,
		glass
	};
	
	id_type id = air;
	
	bool visible() const;
	bool transparent() const;
};

std::ostream& operator<<(
	std::ostream& os, 
	const block& b
);

std::istream& operator>>(
	std::istream& is,
	block& b
);
