#pragma once

#include <cstdint>
#include "entity.hpp"

struct mob: public entity{
	enum id_type: uint8_t{
		ghost,
		human,
		sheep
	};
	static constexpr float max_pitch = 0.5f, min_pitch = 0.5f, north = 0.0f;
	id_type id = ghost;
	float yaw = 0.0f, pitch = 0.0f; // radians
	
	bool flys() const;
	float speed() const;
	
	void rotate(float yaw_ammount, float pitch_ammount = 0.0f); // relative
	void orient(float yaw_ammount, float pitch_ammount = 0.0f); // absolute
};
