#include <iostream>
#include <chrono>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include "../modeler.hpp"
#include "../generator.hpp"

sf::RenderWindow window{
	sf::VideoMode(800, 600),
	"Block Game"
};

modeler m;
chunk c;
generator gen;
model cm;

int main(){
	c = gen({0, 0});
	std::cout << "generated" << std::endl;
	auto start = std::chrono::steady_clock::now();
	cm = m.generate_chunk_model(c);
	auto end = std::chrono::steady_clock::now();
	std::cout << "modeled in " << std::chrono::duration<float>(end - start).count() << "seconds" << std::endl;
	std::cout << "vertices: " << cm.size() << std::endl;
	
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
