#include "block.hpp"

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
