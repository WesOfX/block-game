#include "entity.hpp"

void entity_t::move(position_t offset){
	position.x += offset.x;
	position.y += offset.y;
	position.z += offset.z;
}

void entity_t::accelerate(velocity_t ammount){
	velocity.x += ammount.x;
	velocity.y += ammount.y;
	velocity.z += ammount.z;
}

void entity_t::update(){

}
