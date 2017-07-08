#include <fstream>
#include "map.hpp"

void map::load_chunk(const chunk::position_type& position){
	
}

void map::save_chunk(const chunk::position_type& position){
	std::ofstream fout{"test"};
	if(fout) fout << chunks.at(position);
	else throw std::runtime_error("Failed to save chunk: ");
}

void map::save_map(std::string filename){

}
