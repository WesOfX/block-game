CC= g++
CFLAGS= -std=c++17 -Wall -g -O2
LDFLAGS= -lpthread -lGLEW -lGLU -lGL -lsfml-graphics -lsfml-window -lsfml-system
OBJS= obj/world.o obj/entity.o obj/mob.o obj/player.o obj/map.o obj/chunk.o obj/block.o obj/generator.o obj/updater.o obj/scene.o obj/modeler.o obj/vbo.o obj/vao.o obj/atlas.o obj/shader.o

all: bin/world-explorer

#all: bin/run bin/chunk-viewer bin/world-explorer

#bin/run: obj/main.o $(OBJS) | bin data
#	$(CC) $(CFLAGS) -o bin/run obj/main.o $(OBJS) $(LDFLAGS)
	
#bin/chunk-viewer: obj/chunk_viewer.o $(OBJS) | bin
#	$(CC) $(CFLAGS) -o bin/chunk-viewer obj/chunk_viewer.o $(OBJS) $(LDFLAGS)
	
bin/world-explorer: obj/world_explorer.o $(OBJS) | bin
	$(CC) $(CFLAGS) -o bin/world-explorer obj/world_explorer.o $(OBJS) $(LDFLAGS)

#obj/main.o: src/main.cpp | obj
#	$(CC) $(CFLAGS) -o obj/main.o -c src/main.cpp
	
obj/world.o: src/world.hpp src/world.cpp obj/updater.o obj/mob.o obj/player.o | obj
	$(CC) $(CFLAGS) -o obj/world.o -c src/world.cpp
	
obj/entity.o: src/entity.hpp src/entity.cpp src/vec3.hpp | obj
	$(CC) $(CFLAGS) -o obj/entity.o -c src/entity.cpp
	
obj/mob.o: src/mob.hpp src/mob.cpp src/entity.hpp | obj
	$(CC) $(CFLAGS) -o obj/mob.o -c src/mob.cpp
	
obj/player.o: src/player.hpp src/player.cpp src/mob.hpp | obj
	$(CC) $(CFLAGS) -o obj/player.o -c src/player.cpp

obj/map.o: src/map.hpp src/map.cpp obj/chunk.o obj/generator.o src/util.hpp | obj
	$(CC) $(CFLAGS) -o obj/map.o -c src/map.cpp
	
obj/chunk.o: src/chunk.hpp src/chunk.cpp src/vec2.hpp obj/block.o | obj
	$(CC) $(CFLAGS) -o obj/chunk.o -c src/chunk.cpp
	
obj/block.o: src/block.hpp src/block.cpp | obj
	$(CC) $(CFLAGS) -o obj/block.o -c src/block.cpp
	
obj/generator.o: src/generator.hpp src/generator.cpp src/noise.hpp obj/chunk.o | obj
	$(CC) $(CFLAGS) -o obj/generator.o -c src/generator.cpp
	
obj/updater.o: src/updater.hpp src/updater.cpp obj/chunk.o | obj
	$(CC) $(CFLAGS) -o obj/updater.o -c src/updater.cpp

obj/chunk_viewer.o: src/test/chunk_viewer.cpp obj/modeler.o obj/generator.o obj/updater.o obj/vbo.o obj/vao.o obj/atlas.o obj/shader.o | obj
	$(CC) $(CFLAGS) -o obj/chunk_viewer.o -c src/test/chunk_viewer.cpp
	
obj/scene.o: src/scene.hpp src/scene.cpp obj/modeler.o | obj
	$(CC) $(CFLAGS) -o obj/scene.o -c src/scene.cpp
	
obj/vbo.o: src/vbo.hpp src/vbo.cpp obj/modeler.o | obj
	$(CC) $(CFLAGS) -o obj/vbo.o -c src/vbo.cpp
	
obj/vao.o: src/vao.hpp src/vao.cpp | obj
	$(CC) $(CFLAGS) -o obj/vao.o -c src/vao.cpp
	
obj/modeler.o: src/modeler.hpp src/modeler.cpp obj/chunk.o obj/atlas.o | obj
	$(CC) $(CFLAGS) -o obj/modeler.o -c src/modeler.cpp
	
obj/atlas.o: src/atlas.hpp src/atlas.cpp | obj
	$(CC) $(CFLAGS) -o obj/atlas.o -c src/atlas.cpp

obj/shader.o: src/shader.hpp src/shader.cpp | obj
	$(CC) $(CFLAGS) -o obj/shader.o -c src/shader.cpp
	
obj/world_explorer.o: src/test/world_explorer.cpp | obj
	$(CC) $(CFLAGS) -o obj/world_explorer.o -c src/test/world_explorer.cpp

bin:
	mkdir bin
	
data:
	mkdir -p data/world/chunks
	
obj:
	mkdir obj

clean:
	rm -r bin; rm -r data; rm -r obj
