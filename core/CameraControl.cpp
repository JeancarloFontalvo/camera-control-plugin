#include "pch.h"
#include "CameraControl.h"
#include <sstream>
#include "shared/utils.h"
#include "utils/parser.h"
#include "shared/constants.h"
#include <core/boostrap.h>
#include <services/CommandParamParsers.h>

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

	initCommandParamFactory();

	_globalCvarManager = cvarManager;

	std::string defaultSensitivityString = to_string_with_precision(constants::DEFAULT_SENSITIVITY);

	// variables
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_ENABLE), "0", "Enable Camera Control", true, true, 0, true, 1);
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_DEFAULT_SENSITIVITY), defaultSensitivityString, "Default sensitivity for axes and rotation parameters");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_X_SENSITIVITY), defaultSensitivityString, "Default sensitivity for x axis if empty takes default sensitivity");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_Y_SENSITIVITY), defaultSensitivityString, "Default sensitivity for y axis if empty takes default sensitivity");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_Z_SENSITIVITY), defaultSensitivityString, "Default sensitivity for z axis if empty takes default sensitivity");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_ROLL_SENSITIVITY), defaultSensitivityString, "Default sensitivity for roll rotation if empty takes default sensitivity");
	_globalCvarManager->registerCvar(commandNameResolver(constants::VAR_PITCH_SENSITIVITY), defaultSensitivityString, "Default sensitivity for pitch rotation if empty takes default sensitivity");

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
	auto cmdParamModel = (MoveParamsModel*)(CmdParamFactory::getInstance()->get<MoveParamsModel>(constants::CMD_MOVE, params));

	this->log("Sensitivity params: " + sensitivity.toString());
	this->log("Command params: " + cmdParamModel->toString());

	this->log("setting camera location");
	auto camera = gameWrapper->GetCamera();
	Vector currentLocation = also<Vector>(camera.GetLocation(), [this](Vector& loc) {
		this->log(std::format("current location: {}", toString(loc)));
	});

	Rotator currentRotation = also<Rotator>(camera.GetRotation(), [this](Rotator& rot) {
		this->log(std::format("current rotator: ({}, {}, {})", rot.Roll, rot.Pitch, rot.Yaw));
	});

	if (cmdParamModel->variable.compare(constants::CmdVariables::VAR_X) == 0)
		currentLocation.X += sensitivity.x * cmdParamModel->value;

	if (cmdParamModel->variable.compare(constants::CmdVariables::VAR_Y) == 0)
		currentLocation.Y += sensitivity.y * cmdParamModel->value;

	if (cmdParamModel->variable.compare(constants::CmdVariables::VAR_Z) == 0)
		currentLocation.Z += sensitivity.z * cmdParamModel->value;

	if (cmdParamModel->variable.compare(constants::CmdVariables::VAR_ROLL) == 0)
		currentRotation.Roll += sensitivity.roll * cmdParamModel->value;

	if (cmdParamModel->variable.compare(constants::CmdVariables::VAR_PITCH) == 0)
		currentRotation.Pitch += sensitivity.pitch * cmdParamModel->value;

	this->log(std::format("new location: {}", toString(currentLocation)));
	this->log(std::format("new rotator: ({}, {}, {})", currentRotation.Roll, currentRotation.Pitch, currentRotation.Yaw));

	camera.SetLocation(currentLocation);
	camera.SetRotation(currentRotation);

	this->log(log.str());
}

