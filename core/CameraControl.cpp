#include "pch.h"
#include "CameraControl.h"
#include <sstream>
#include "shared/utils.h"
#include "utils/parser.h"
#include "shared/constants.h"

BAKKESMOD_PLUGIN(CameraControl, "Camera control", "1.0", PLUGINTYPE_REPLAY | PLUGINTYPE_SPECTATOR)

using namespace std::placeholders;

std::shared_ptr<CVarManagerWrapper> _globalCvarManager;

bool CameraControl::IsApplicable()
{
	return (gameWrapper->IsInReplay() || gameWrapper->IsInGame()) && 
			!gameWrapper->GetCamera().IsNull() && 
				gameWrapper->GetCamera().GetCameraState().compare("CameraState_ReplayFly_TA") == 0;
}

CameraControl::CameraControl()
{
	this->stateManager = std::shared_ptr<StateManager>();
}

CameraControl::~CameraControl()
{
	this->stateManager.reset();
}

void CameraControl::onLoad() {
	this->log("init plugin:: camera control");
	this->init();
}

void CameraControl::onUnload() {

}

void CameraControl::init() {

	_globalCvarManager = cvarManager;

	// variables
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_ENABLE), "0", "Enable Camera Control", true, true, 0, true, 1);
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_DEFAULT_SENSITIVITY), "1.0", "Default sensitivity for axes and rotation parameters");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_X_SENSITIVITY), "", "Default sensitivity for x axis if empty takes default sensitivity");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_Y_SENSITIVITY), "", "Default sensitivity for y axis if empty takes default sensitivity");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_Z_SENSITIVITY), "", "Default sensitivity for z axis if empty takes default sensitivity");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_ROLL_SENSITIVITY), "", "Default sensitivity for roll rotation if empty takes default sensitivity");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_PITCH_SENSITIVITY), "", "Default sensitivity for pitch rotation if empty takes default sensitivity");

	// hooks
	cvarManager->registerNotifier(commandNameResolver(constants::CMD_MOVE), std::bind(&CameraControl::onMoveCamera, this, _1), "Move camera", PERMISSION_REPLAY);
	cvarManager->registerNotifier(commandNameResolver(constants::CMD_GET_INFO), std::bind(&CameraControl::onCamCommand, this, _1), "Prints the current camera info to the console", PERMISSION_REPLAY);
}

void CameraControl::log(std::string message) {
	cvarManager->log(message);
}

void CameraControl::onCamCommand(std::vector<std::string> params)
{
	if (!this->IsApplicable()) {
		return;
	}

	this->log("tryin to get camera info...");
	auto pov = gameWrapper->GetCamera().GetPOV();

	std::stringstream log;

	log << std::endl << "location => " << toString(pov.location) << std::endl;
	log << "rotation => {pitch: " << pov.rotation.Pitch << ", roll: " << pov.rotation.Roll << ", yall: " << pov.rotation.Yaw << "}" << std::endl;

	this->log(log.str());
}

void CameraControl::onMoveCamera(std::vector<std::string> params)
{
	if (!this->IsApplicable()) {
		return;
	}

	std::stringstream log;

	auto sensitivity = this->stateManager->getCurrentSensitity(cvarManager);

	auto x = get_safe_float(atWithDefault(params, 1, ""));
	auto y = get_safe_float(atWithDefault(params, 2, ""));
	auto z = get_safe_float(atWithDefault(params, 3, ""));

	log << "params: ";
	log << "x: " << x << ", ";
	log << "y: " << y << ", ";
	log << "z: " << z << ", ";

	this->log("setting camera location");
	auto camera = gameWrapper->GetCamera();
	auto currentLocation = camera.GetLocation();

	camera.SetLocation(currentLocation + Vector(x, y, z));

	this->log(log.str());
}

