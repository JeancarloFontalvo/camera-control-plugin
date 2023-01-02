#pragma once
#include "pch.h"
#include "base.h"

struct MoveParamsModel : public BaseModel {
	std::string variable = "";
	float value = 0.0f;

	MoveParamsModel(){}

	MoveParamsModel(std::string variable, float value)
	{
		this->variable = variable;
		this->value = value;
	}

	std::string toString() override {
		return std::format("MoveParamsModel: ({}, {})", variable, value);
	}
};
