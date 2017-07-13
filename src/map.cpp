#include <fstream>
#include "map.hpp"

map::~map(){
	save();
}

void map::load_chunk(const chunk::position_type& position){
	// If the chunk is already loaded
	if(chunks.count(position) > 0) return;
	
	auto filename = generate_filename(position);
	std::ifstream fin{filename, std::ios::binary};
	// If the file is good and it's not empty
	if(fin && fin.peek() != std::ifstream::traits_type::eof()){
		// load chunk from file
		chunk c;
		fin >> c;
		chunks.insert({position, c});
	}
	else{
		// generate new chunk
		chunks.emplace(position, gen(position));
	}
}

void map::save_chunk(const chunk::position_type& position){
	// If the chunk doesn't exist
	if(chunks.find(position) == chunks.end()) return;
	
	auto filename = generate_filename(position);
	std::ofstream fout{filename, std::ios::binary};
	if(fout) fout << chunks.at(position);
	else throw std::runtime_error(
		"Failed to save chunk "
	  + std::to_string(position.x)
	  + ", "
	  + std::to_string(position.y)
	);
}

void map::unload_chunk(const chunk::position_type& position){
	chunks.erase(position);
}

void map::save(){
	for(auto& i: chunks) save_chunk(i.first);
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
