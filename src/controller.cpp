#include <SFML/Window/Event.hpp>
#include "controller.hpp"

controller::~controller(){
	save_bindings();
}

void controller::load_bindings(){
	// TODO
	// load bindings or generate default bindings
}

void controller::save_bindings() const{
	
}

void controller::update(world& w, const sf::Event& e){
	switch(e.type){
	case sf::Event::KeyPressed:
		switch(key_bindings[e.key.code]){
		default:
			break;
		}
		break;
	case sf::Event::KeyReleased:
		switch(key_bindings[e.key.code]){
		default:
			break;
		}
		break;
	default:
		break;
	}
}
