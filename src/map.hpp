#pragma once

#include <string>
#include <unordered_map>
#include "chunk.hpp"
#include "generator.hpp"
#include "util.hpp" // for std::hash<chunk::position_type>

struct map{
	~map();

	generator gen = {};
	std::unordered_map<chunk::position_type, chunk> chunks;
	// std::unordered_map<chunk::position_type, std::string> saved_chunks;
	
	// loads a chunk if it is saved
	bool load_chunk(const chunk::position_type& position);
	
	// generates a chunk if it does not exist	
	void generate_chunk(const chunk::position_type& position);
	
	// saves a chunk to a file
	void save_chunk(const chunk::position_type& position);
	
	void unload_chunk(const chunk::position_type& position);
	
	// saves all the chunks
	void save();
	
	// generate a filename from a chunk position
	std::string generate_filename(const chunk::position_type& position) const;
};
