#include "../world.hpp"
#include "../scene.hpp"
#include "../controller.hpp"
#include "../view.hpp"

int main(){	
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
	p.position.y = -5.0f;
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
				
		std::cout << "chunks loaded: " << w.m.chunks.size() << std::endl;
		std::cout << "models loaded: " << s.chunk_models.size() << std::endl;
		s.update();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		window.draw(s);
		window.display();
	}
}
