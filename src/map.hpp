#pragma once

#include <string>
#include <unordered_map>
#include "chunk.hpp"
#include "util.hpp"

struct map{
	std::string name;
	std::unordered_map<chunk::position_type, chunk> chunks;
	std::unordered_map<chunk::position_type, std::string> saved_chunks;
	
	// loads a chunk if it is saved
	// generates a chunk if it is not saved
	void load_chunk(const chunk::position_type& position);
	
	// saves a chunk to a file and unloads the chunk
	void save_chunk(const chunk::position_type& position);
	
	// saves all the loaded chunks and saves the map
	void save_map(std::string filename);
};
