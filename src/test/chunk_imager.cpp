#include <fstream>
#include <sstream>
#include "ppm.hpp"
#include "../chunk.hpp"

std::string filename;
ppm::image<chunk::rows, chunk::columns> img;
chunk c;

ppm::pixel to_pixel(block b){
	// TODO
	return {1.0f, 0.0f, 1.0f};
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
				img[row][column] = to_pixel(c.blocks[row][column][layer]);
	
	std::ofstream fout{filename + ".ppm"};
	fout << img;
}
