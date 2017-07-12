#include <iostream>
#include "world.hpp"

world w;

int main(){	
	w.players.emplace_back();
	w.update();
}
