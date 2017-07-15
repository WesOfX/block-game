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
