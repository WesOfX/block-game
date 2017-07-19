#include "block.hpp"

bool block::visible() const{
	switch(id){
	case air: return false;
	default: return true;
	}
}

bool block::transparent() const{
	switch(id){
	case air: return true;
	case glass: return true;
	default: return false;
	}
}

uint8_t block::emittance() const{
	switch(id){
	default: return 0;
	}
}

/*
uint8_t get_sky_light() const{

}

void set_sky_light(uint8_t value){

}

uint8_t get_light() const{

}

void set_light(uint8_t value){

}
*/

std::ostream& operator<<(
	std::ostream& os, 
	const block& b
){
	os << (unsigned char)b.id;
	return os;
}

std::istream& operator>>(
	std::istream& is,
	block& b
){
	b.id = (block::id_type)is.get();
	return is;
}
