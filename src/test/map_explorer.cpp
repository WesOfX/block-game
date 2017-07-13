#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../world.hpp"

sf::RenderWindow window(sf::VideoMode(800, 600), "foo");
world w;

int main(){
	w.players.emplace_back();
	w.chunk_loading_distance = 4.5f;
	sf::Clock clock;
	static constexpr float player_speed = 3.0f;
	static constexpr float block_size = 1.0f,
	                       chunk_width = block_size * chunk::columns,
	                       chunk_height = block_size * chunk::rows;
	window.setVerticalSyncEnabled(true);
	window.setKeyRepeatEnabled(false);
	while(window.isOpen()){
		sf::Event e;
		while(window.pollEvent(e)){
			switch(e.type){
			case sf::Event::Closed:
				window.close();
			case sf::Event::KeyPressed:
				switch(e.key.code){
				case sf::Keyboard::A:
					w.players.back().velocity.x = -player_speed;
					break;
				case sf::Keyboard::E:
					w.players.back().velocity.x = player_speed;
					break;
				case sf::Keyboard::Comma:
					w.players.back().velocity.y = -player_speed;
					break;
				case sf::Keyboard::O:
					w.players.back().velocity.y = player_speed;
					break;
				default:
					break;
				}
				break;
			case sf::Event::KeyReleased:
				switch(e.key.code){
				case sf::Keyboard::A:
					w.players.back().velocity.x = 0.0f;
					break;
				case sf::Keyboard::E:
					w.players.back().velocity.x = 0.0f;
					break;
				case sf::Keyboard::Comma:
					w.players.back().velocity.y = 0.0f;
					break;
				case sf::Keyboard::O:
					w.players.back().velocity.y = 0.0f;
					break;
				default:
					break;
				break;
				}
				break;
			default:
				break;
			}
		}
		w.update();
		
		clock.restart();
		
		window.clear();
		
		window.setView(
			{
				{
					w.players.back().position.x * block_size,
					w.players.back().position.y * block_size
				}, 
				{
					800.0f,
					600.0f
				}
			}
		);
		
		// draw map
		for(auto& i: w.m.chunks){
			sf::RectangleShape rect(
				{chunk_width, chunk_height}
			);
			rect.setPosition(
				{
					i.first.x * chunk_width, 
					i.first.y * chunk_height
				}
			);
			rect.setFillColor({0, 191, 0});
			window.draw(rect);
		}
		
		window.display();
	}
}
