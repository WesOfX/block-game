CC= g++
CFLAGS= -std=c++17 -Wall -g -O2
LDFLAGS= -lpthread -sfml-graphics -sfml-window -sfml-system
OBJS= obj/world.o obj/entity.o obj/map.o obj/chunk.o obj/block.o obj/generator.o obj/scene.o obj/modeler.o

all: bin/run bin/chunk-viewer

bin/run: obj/main.o $(OBJS) | bin data
	$(CC) $(CFLAGS) -o bin/run obj/main.o $(OBJS) -lpthread
	
bin/chunk-viewer: obj/chunk_viewer.o $(OBJS) | bin
	$(CC) $(CFLAGS) -o bin/chunk-viewer obj/chunk_viewer.o $(OBJS) -lpthread -lsfml-graphics -lsfml-window -lsfml-system

obj/main.o: src/main.cpp | obj
	$(CC) $(CFLAGS) -o obj/main.o -c src/main.cpp
	
obj/world.o: src/world.hpp src/world.cpp obj/entity.o obj/map.o | obj
	$(CC) $(CFLAGS) -o obj/world.o -c src/world.cpp
	
obj/entity.o: src/entity.hpp src/entity.cpp src/vec3.hpp | obj
	$(CC) $(CFLAGS) -o obj/entity.o -c src/entity.cpp

obj/map.o: src/map.hpp src/map.cpp obj/chunk.o obj/generator.o src/util.hpp | obj
	$(CC) $(CFLAGS) -o obj/map.o -c src/map.cpp
	
obj/chunk.o: src/chunk.hpp src/chunk.cpp src/vec2.hpp obj/block.o | obj
	$(CC) $(CFLAGS) -o obj/chunk.o -c src/chunk.cpp
	
obj/block.o: src/block.hpp src/block.cpp | obj
	$(CC) $(CFLAGS) -o obj/block.o -c src/block.cpp
	
obj/generator.o: src/generator.hpp src/generator.cpp src/noise.hpp obj/chunk.o | obj
	$(CC) $(CFLAGS) -o obj/generator.o -c src/generator.cpp

obj/chunk_viewer.o: src/test/chunk_viewer.cpp obj/scene.o | obj
	$(CC) $(CFLAGS) -o obj/chunk_viewer.o -c src/test/chunk_viewer.cpp
	
obj/scene.o: src/scene.hpp src/scene.cpp obj/modeler.o | obj
	$(CC) $(CFLAGS) -o obj/scene.o -c src/scene.cpp
	
obj/modeler.o: src/modeler.hpp src/modeler.cpp obj/chunk.o | obj
	$(CC) $(CFLAGS) -o obj/modeler.o -c src/modeler.cpp

bin:
	mkdir bin
	
data:
	mkdir -p data/world/chunks
	
obj:
	mkdir obj

clean:
	rm -r bin; rm -r data; rm -r obj
