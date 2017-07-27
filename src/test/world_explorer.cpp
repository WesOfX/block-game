#include <SFML/Graphics.hpp>
#include "../world.hpp"
#include "../scene.hpp"
#include "../controller.hpp"

int main(){
	world w;
	// scene s;
	controller c;

	c.load_bindings();
	w.players.emplace_back();	
	
	// std::cout << "size of block: " << sizeof(block) << std::endl;
	// std::cout << "size of chunk: " << sizeof(chunk) << std::endl;

	sf::RenderWindow window(
		sf::VideoMode(800, 600), 
		"Block Game",
		sf::Style::Default,
		sf::ContextSettings(
			24,
			8,
			0,
			4,
			3
		)
	);
	window.setVerticalSyncEnabled(true);
	
	while(window.isOpen()){
		sf::Event e;
		while(window.pollEvent(e)){
			switch(e.type){
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
			c.update(w, e);
		}
				
		// std::cout << "chunks loaded: " << w.m.chunks.size() << std::endl;
		// s.update(w);
		
		window.clear();
		// window.draw(s);
		window.display();
	}
}
