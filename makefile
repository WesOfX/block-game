run: src/main.cpp src/vector.hpp src/entity.hpp src/block.hpp src/chunk.hpp src/world.hpp
	g++ -std=c++17 -Wall -g src/main.cpp -o run src/entity.cpp src/block.cpp src/chunk.cpp src/world.cpp
	
clean:
	rm ./run
