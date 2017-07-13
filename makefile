run:
	mkdir bin; mkdir -p data/world/chunks; g++ -std=c++17 -Wall -g -O2 src/main.cpp -o bin/run -lpthread src/block.cpp src/chunk.cpp src/map.cpp src/entity.cpp src/generator.cpp src/world.cpp
chunk_imager:
	mkdir bin; mkdir -p data/world/chunks; g++ -std=c++17 -Wall -g -O2 src/test/chunk_imager.cpp -o bin/chunk_imager src/test/ppm.cpp src/block.cpp src/chunk.cpp
	
map_explorer:
	mkdir bin; mkdir -p data/world/chunks; g++ -std=c++17 -Wall -g -O2 src/test/map_explorer.cpp -o bin/map_explorer -lpthread -lsfml-graphics -lsfml-window -lsfml-system src/entity.cpp src/block.cpp src/chunk.cpp src/generator.cpp src/map.cpp src/world.cpp
	
clean:
	rm -r ./bin; rm -r ./data
