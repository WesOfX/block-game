#include <iostream>
#include <chrono>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../modeler.hpp"
#include "../generator.hpp"
#include "../vbo.hpp"

sf::RenderWindow window{
	sf::VideoMode(800, 600),
	"Block Game"
};

modeler m;
chunk c;
generator gen;
model cm;

using namespace std::chrono;
steady_clock::time_point start, end;

int main(){
	
	start = steady_clock::now();
	c = gen({0, 0});
	end = steady_clock::now();
	std::cout 
 << "Chunk generated in " 
 << duration<float>(end - start).count()
 << "seconds" 
 << std::endl;
 
 	std::cout
 << "Number of blocks: "
 << chunk::rows * chunk::columns * chunk::layers
 << std::endl;
	
	start = steady_clock::now();
	cm = m.generate_chunk_model(c);
	end = steady_clock::now();
	std::cout 
 << "Chunk modeled generated in " 
 << duration<float>(end - start).count() 
 << " seconds" 
 << std::endl;
 
	std::cout 
 << "Number of vertices: " 
 << cm.vertices.size() 
 << std::endl;
 
 	model::bind(cm);
	
	bool running = true;
	while(running){
		sf::Event e;
		while(window.pollEvent(e)){
			switch(e.type){
			case sf::Event::Closed:
				running = false;
			default:
				break;
			}
		}
		
		window.clear({255, 0, 255});
		
		window.display();
	}
}
