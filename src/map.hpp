#pragma once

#include <string>
#include <unordered_map>
#include "chunk.hpp"
#include "generator.hpp"
#include "util.hpp" // for std::hash<chunk::position_type>

struct map{
	generator gen = {};
	std::unordered_map<chunk::position_type, chunk> chunks;
	std::queue<chunk::position_type> chunk_updates;
	
	~map();
	
	// loads chunk if a file exists. generates a new chunk if not
	bool load_chunk(const chunk::position_type& position);
	void generate_chunk(const chunk::position_type& position);
	void save_chunk(const chunk::position_type& position);
	void unload_chunk(const chunk::position_type& position);
	
	// saves all the chunks
	void save();
	
private:
	static std::string generate_filename(const chunk::position_type& position);
};
