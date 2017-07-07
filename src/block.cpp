#include "block.hpp"

bool block_t::transparent() const{
	switch(id){
	case block_t::id_t::grass:
		return false;
	case block_t::id_t::dirt:
		return false;
	case block_t::id_t::stone:
		return false;
	case block_t::id_t::glass:
		return true;
	default:
		return false;
	}
}
