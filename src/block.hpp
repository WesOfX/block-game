#pragma once

#include <iostream>

struct block{
	enum id_type: uint8_t{
		air,
		grass,
		dirt,
		stone,
		glass,
		leaves,
		fire
	};
	
	id_type id = air;
	uint8_t torch_light:4, sky_light:4;
	
	bool visible() const;
	uint8_t opacity() const;
	uint8_t emittance() const;
	bool flammable() const;
};

std::ostream& operator<<(
	std::ostream& os, 
	const block& b
);

std::istream& operator>>(
	std::istream& is,
	block& b
);
