run:
	mkdir bin; mkdir -p data/world/chunks; g++ -std=c++17 -Wall -g -O2 src/main.cpp -o bin/run src/block.cpp src/chunk.cpp src/map.cpp src/entity.cpp src/generator.cpp src/world.cpp
	
test:
	mkdir bin; g++ -std=c++17 -Wall -g -O2 src/test/chunk_imager.cpp -o bin/chunk-imager src/test/ppm.cpp src/block.cpp src/chunk.cpp
	
clean:
	rm -r ./bin; rm -r ./data
