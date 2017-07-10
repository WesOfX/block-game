#include <fstream>
#include "map.hpp"

void map::load_chunk(const chunk::position_type& position){
	auto filename = generate_filename(position);
	std::ifstream fin{filename, std::ios::binary};
	chunk c;
	if(fin) fin >> c;
	else throw std::runtime_error("Failed to load chunk: " + filename);
	chunks.insert({position, c});
}

void map::save_chunk(const chunk::position_type& position) const{
	auto filename = generate_filename(position);
	std::ofstream fout{filename, std::ios::binary};
	if(fout) fout << chunks.at(position);
	else throw std::runtime_error("Failed to save chunk: " + filename);
}

std::string map::generate_filename(const chunk::position_type& position) const{
	return {
		"data/world/chunks/"
	  + std::to_string(position.x) 
	  + "r" 
	  + std::to_string(position.y) 
	  + "c"
	};
}
