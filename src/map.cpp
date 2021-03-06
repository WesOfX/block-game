#include <fstream>
#include "map.hpp"

map::~map(){
	save();
}

bool map::load_chunk(const chunk::position_type& position){
	// If the chunk is already loaded
	if(chunks.count(position) > 0) return true;
	
	auto filename = generate_filename(position);
	std::ifstream fin{filename, std::ios::binary};

	push_update(position);
	// If the file is good and it's not empty
	if(fin && fin.peek() != std::ifstream::traits_type::eof()){
		// load chunk from file
		chunk c;
		fin >> c;
		chunks[position] = c;
		return true;
	}
	else{ 
		generate_chunk(position);
		return false;
	}
}

void map::generate_chunk(const chunk::position_type& position){
	chunk c;
	gen.generate_terrain(c, position);
	chunks[position] = c;
}

void map::save_chunk(const chunk::position_type& position) const{
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

void map::save() const{
	for(auto& i: chunks){ 
		save_chunk(i.first);
		// unload_chunk(i.first); // Causes segmentation fault
	}
}

bool map::has_updates() const{
	return !chunk_updates.empty();
}

void map::push_update(const chunk::position_type& chunk_position){
	chunk_updates.push(chunk_position);
}

const chunk::position_type& map::next_update(){
	return chunk_updates.front();
}

void map::pop_update(){
	chunk_updates.pop();
}

std::string map::generate_filename(const chunk::position_type& position){
	return {
		"data/world/chunks/"
	  + std::to_string(position.x) 
	  + "r" 
	  + std::to_string(position.y) 
	  + "c"
	};
}
