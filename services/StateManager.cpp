#include "pch.h"
#include "StateManager.h"
#include "shared/utils.h"
#include "shared/constants.h"

Sensitivity StateManager::getCurrentSensitity(std::shared_ptr<CVarManagerWrapper> cvarManager)
{
    return Sensitivity(
        cvarManager->getCvar(commandNameResolver(constants::VAR_DEFAULT_SENSITIVITY)).getFloatValue(),
        cvarManager->getCvar(commandNameResolver(constants::VAR_X_SENSITIVITY)).getFloatValue(),
        cvarManager->getCvar(commandNameResolver(constants::VAR_Y_SENSITIVITY)).getFloatValue(),
        cvarManager->getCvar(commandNameResolver(constants::VAR_Z_SENSITIVITY)).getFloatValue(),
        cvarManager->getCvar(commandNameResolver(constants::VAR_ROLL_SENSITIVITY)).getFloatValue(),
        cvarManager->getCvar(commandNameResolver(constants::VAR_PITCH_SENSITIVITY)).getFloatValue()
    );
}
