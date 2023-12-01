#pragma once
#include <bakkesmod/wrappers/GameWrapper.h>
#include "shared/models/SensitivityModel.h"

class StateManager
{
public: 
	Sensitivity getCurrentSensitity(std::shared_ptr<CVarManagerWrapper> cvarManager);
};

