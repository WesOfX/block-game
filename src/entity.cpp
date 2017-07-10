#include "entity.hpp"

void entity::move(const entity::position_type& offset){
	position += offset;
}

void entity::accelerate(const entity::position_type& amount){
	velocity += amount;
}

void entity::update(){
	position += velocity;
}
