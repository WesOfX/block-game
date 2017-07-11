#include <fstream>
#include <sstream>
#include "ppm.hpp"
#include "../chunk.hpp"

std::string filename;
ppm::image<chunk::rows, chunk::columns> img;
chunk c;

block::id_type top_block(size_t row, size_t column){
	for(auto layer = chunk::layers - 1; layer >= 0; --layer){
		if(c.blocks[row][column][layer].id != block::air)
			return c.blocks[row][column][layer].id;
	}
	return block::air;
}

ppm::pixel to_pixel(block::id_type id){
	switch(id){
	case block::air:
		return {1.0f, 1.0f, 1.0f};
	case block::grass:
		return {0.0f, 0.75f, 0.0f};
	case block::stone:
		return {0.4f, 0.4f, 0.4f};
	default:
		return {1.0f, 0.0f, 1.0f};
	}
}

int main(int argc, const char* argv[]){
	for(auto i = 0; i < argc; ++i){
		std::stringstream ss;
		ss << argv[i];
		// if(ss.str() == flag)... else
		filename = ss.str();
	}
	
	std::ifstream fin{filename};
	fin >> c;
	
	for(size_t row = 0; row < chunk::rows; ++row)
		for(size_t column = 0; column < chunk::columns; ++column)
			for(size_t layer = 0; layer < chunk::layers; ++layer)
				img[row][column] = to_pixel(top_block(row, column));
	
	std::ofstream fout{filename + ".ppm"};
	fout << img;
}
