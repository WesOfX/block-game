#include "../world.hpp"
#include "../scene.hpp"
#include "../controller.hpp"
#include "../view.hpp"

int main(){	
	// std::cout << "size of block: " << sizeof(block) << std::endl;
	// std::cout << "size of chunk: " << sizeof(chunk) << std::endl;

	sf::RenderWindow window(
		sf::VideoMode(1600, 900), 
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
	
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	window.setActive(true);
	
	glewInit();	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);
	glClearColor(0.1f, 0.1f, 0.1f, 0.0f);
	
	world w;
	scene s(w);
	controller c;
	player p;

	c.load_bindings();
	p.position = {8.0, 160.0f, 8.0f};
	p.velocity = {-1.0f / 16, 0.0f, 1.0f / 64};
	w.players.push_back(std::move(p));
	
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
				
		std::cout << "player x: " << w.players.back().position.x << std::endl;
		std::cout << "chunks loaded: " << w.m.chunks.size() << std::endl;
		std::cout << "models loaded: " << s.chunk_models.size() << std::endl;
		s.update();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		window.draw(s);
		window.display();
	}
}
