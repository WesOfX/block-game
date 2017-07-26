#include <SFML/Graphics.hpp>
#include "../world.hpp"

world w;

int main(){
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
		
		try{
			w.update();
		}
		catch(const std::exception& e){
			// std::cout << e.what() << std::endl;
		}
		
		window.clear();
		window.display();
	}
}
