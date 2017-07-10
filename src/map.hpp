#pragma once

#include <string>
#include <unordered_map>
#include "chunk.hpp"
#include "util.hpp"

struct map{
	std::string name = "world";
	std::unordered_map<chunk::position_type, chunk> chunks;
	// std::unordered_map<chunk::position_type, std::string> saved_chunks;
	
	// loads a chunk if it is saved
	// generates a chunk if it is not saved
	void load_chunk(const chunk::position_type& position);
	
	// saves a chunk to a file and unloads the chunk
	void save_chunk(const chunk::position_type& position) const;
	
	// saves all the loaded chunks and saves the map
	// void save_map(const std::string& filename) const;
	
	// generate a filename from a chunk position
	std::string generate_filename(const chunk::position_type& position) const;
};
