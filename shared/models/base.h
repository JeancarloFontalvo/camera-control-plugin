#pragma once
#include "constants.h"

template<class T, class U>
concept ModelConcept = std::is_base_of<U, T>::value;

struct BaseModel {
public:
	virtual std::string toString() {
		return "";
	}
};