run:
	g++ -std=c++17 -Wall -g -O2 src/main.cpp -o run src/block.cpp src/chunk.cpp src/map.cpp src/entity.cpp
	
test:
	g++ -std=c++17 -Wall -g -O2 src/test/chunk_imager.cpp -o chunk-imager src/test/ppm.cpp src/block.cpp src/chunk.cpp
	
clean:
	rm ./run; rm ./chunk_imager.cpp
