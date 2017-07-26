#include <cmath>
#include "mob.hpp"

bool mob::flys() const{
	switch(id){
	case ghost: return true;
	default: return false;
	}
}

float mob::speed() const{
	switch(id){
	case ghost: return 200;
	default: return 100;
	}
}

void mob::rotate(float yaw_ammount, float pitch_ammount){
	yaw += yaw_ammount;
	pitch += pitch_ammount;
	clamp_orientation();
}

void mob::orient(float yaw_ammount, float pitch_ammount){
	yaw = yaw_ammount;
	pitch = pitch_ammount;
	clamp_orientation();
}

void mob::clamp_orientation(){
	if(yaw < -2.0f || yaw > 2.0f) yaw = fmod(yaw, 2.0f);
	if(pitch < min_pitch) pitch = min_pitch;
	if(pitch > max_pitch) pitch = max_pitch;
}
