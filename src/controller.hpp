#pragma once

#include <map>
// #include <SFML/Window/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "world.hpp"

struct controller{
	enum command{
		quit
	};
	std::map<sf::Keyboard::Key, command> key_bindings;
	~controller();
	void load_bindings();
	void save_bindings() const;
	void update(world& w, const sf::Event& e);
};
