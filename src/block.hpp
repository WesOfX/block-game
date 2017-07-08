#pragma once

#include <iostream>

struct block{
	enum id_type: uint8_t{
		grass,
		dirt,
		stone,
		glass
	};
	
	id_type id;
};

std::ostream& operator<<(
	std::ostream& os, 
	const block& b
);

std::istream& operator>>(
	std::istream& is,
	block& b
);
