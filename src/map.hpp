#pragma once

#include <string>
#include <unordered_map>
#include "chunk.hpp"
#include "generator.hpp"
#include "util.hpp" // for std::hash<chunk::position_type>

struct map{
	generator gen = {};
	std::unordered_map<chunk::position_type, chunk> chunks;
	
	~map();
	
	// loads chunk if a file exists. generates a new chunk if not
	bool load_chunk(const chunk::position_type& position);
	void generate_chunk(const chunk::position_type& position);
	void save_chunk(const chunk::position_type& position) const;
	void unload_chunk(const chunk::position_type& position);
	
	// saves all the chunks
	void save() const;
	
	bool has_updates() const;
	void push_update(const chunk::position_type& block_position);
	const chunk::position_type& next_update();
	void pop_update();
	
private:
	std::queue<chunk::position_type> chunk_updates;

	static std::string generate_filename(const chunk::position_type& position);
};
