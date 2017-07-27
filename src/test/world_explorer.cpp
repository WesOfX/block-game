#include <SFML/Graphics.hpp>
#include "../world.hpp"

world w;

int main(){
	w.players.emplace_back();
	w.update();
	
	std::cout << "size of block: " << sizeof(block) << std::endl;
	std::cout << "size of chunk: " << sizeof(chunk) << std::endl;

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
		}

		std::cout << "chunks loaded: " << w.m.chunks.size() << std::endl;
		
		window.clear();
		window.display();
	}
}
