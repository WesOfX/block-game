#include <fstream>
#include "map.hpp"

void map::load_chunk(const chunk::position_type& position){
	auto filename = generate_filename(position);
	if(chunks.count(position) > 0)
		throw std::runtime_error("Chunk already exists: " + filename);
	std::ifstream fin{filename, std::ios::binary};
	if(!fin)
		// generate new chunk
		chunks.emplace(std::make_pair(position, gen(position)));
	else{
		// load chunk from file
		chunk c;
		if(fin) fin >> c;
		else throw std::runtime_error("Failed to load chunk: " + filename);
		chunks.insert({position, c});
	}
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
