#include "block.hpp"

bool block::visible() const{
	switch(id){
	case air: return false;
	default: return true;
	}
}

uint8_t block::opacity() const{
	switch(id){
	case air: return 0;
	case glass: return 0;
	case leaves: return 1;
	case fire: return 0;
	default: return 15;
	}
}

uint8_t block::emittance() const{
	switch(id){
	case fire: return 15;
	default: return 0;
	}
}

bool block::flammable() const{
	switch(id){
	case leaves: return true;
	default: return false;
	}
}

std::ostream& operator<<(
	std::ostream& os, 
	const block& b
){
	os << (unsigned char)b.id
	// os << (unsigned char)b.meta;
	   << (unsigned char)b.torch_light
	   << (unsigned char)b.sky_light;
	return os;
}

std::istream& operator>>(
	std::istream& is,
	block& b
){
	b.id = (block::id_type)is.get();
	// b.meta = is.get();
	b.torch_light = is.get();
	b.sky_light = is.get();
	return is;
}
