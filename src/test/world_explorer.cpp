#include <SFML/Graphics.hpp>
#include "../world.hpp"
#include "../scene.hpp"

world w;
scene s;

int main(){
	w.players.emplace_back();	
	
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
				
		s.update(w);
		
		window.clear();
		window.draw(s);
		window.display();
	}
}
