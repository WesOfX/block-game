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
	default: return 15;
	}
}

uint8_t block::emittance() const{
	switch(id){
	default: return 0;
	}
}

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
