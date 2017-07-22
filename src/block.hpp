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
	
	/*
	// sky light is a 4-bit value packed inside "lighting"
	uint8_t get_sky_light() const;
	void set_sky_light(uint8_t value);
	
	// block light is a 4-bit value packed inside "lighting"
	uint8_t get_light() const;
	void set_light(uint8_t value);
	
private:
	uint8_t lighting;
	*/
};

std::ostream& operator<<(
	std::ostream& os, 
	const block& b
);

std::istream& operator>>(
	std::istream& is,
	block& b
);
