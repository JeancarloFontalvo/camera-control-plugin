#pragma once
#include "base.h"
#include "constants.h"

struct Sensitivity : public BaseModel {
	float global;
	float x;
	float y;
	float z;
	float roll;
	float pitch;

	Sensitivity(
		float global = constants::DEFAULT_SENSITIVITY,
		float x = constants::DEFAULT_SENSITIVITY,
		float y = constants::DEFAULT_SENSITIVITY,
		float z = constants::DEFAULT_SENSITIVITY,
		float roll = constants::DEFAULT_SENSITIVITY,
		float pitch = constants::DEFAULT_SENSITIVITY) {

		this->global = global;
		this->x = x;
		this->y = y;
		this->z = z;
		this->roll = roll;
		this->pitch = pitch;
	}

	std::string toString() override
	{
		float global;
		float x;
		float y;
		float z;
		float roll;
		float pitch;

		return std::format("(gloabl: {}, x: {}, y: {}, z: {}, roll: {}, pitch: {})", global, x, y, z, roll, pitch);
	}
};