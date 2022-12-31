#include "pch.h"
#include "CameraControl.h"
#include <sstream>
#include "Utils.h"
#include "utils/parser.h"
#include "shared/constants.h"

BAKKESMOD_PLUGIN(CameraControl, "Camera control", "1.0", PLUGINTYPE_REPLAY | PLUGINTYPE_SPECTATOR)

using namespace std::placeholders;

bool CameraControl::IsApplicable()
{
	return (gameWrapper->IsInReplay() || gameWrapper->IsInGame()) && 
			!gameWrapper->GetCamera().IsNull() && 
				gameWrapper->GetCamera().GetCameraState().compare("CameraState_ReplayFly_TA") == 0;
}

void CameraControl::onLoad() {
	this->log("init plugin:: camera control");
	this->init();
}

void CameraControl::onUnload() {

}

void CameraControl::init() {
	// variables
	cvarManager->registerCvar(constants:: "camera_control_cam_enable", "0", "Enable Camera Control", true, true, 0, true, 1);
	cvarManager->registerCvar("cam_con_cam_x", "0", "X axis");
	cvarManager->registerCvar("camera_control_cam_y", "0", "y axis");
	cvarManager->registerCvar("camera_control_cam_z", "0", "z axis");
	cvarManager->registerCvar("camera_control_cam_pitch", "0", "pitch axis");
	cvarManager->registerCvar("camera_control_cam_roll", "0", "roll axis");

	// hooks
	cvarManager->registerNotifier("camera_control_cam_move", std::bind(&CameraControl::onMoveCamera, this, _1), "Move camera", PERMISSION_REPLAY);
	cvarManager->registerNotifier("camera_control_cam_info", std::bind(&CameraControl::onCamCommand, this, _1), "Prints the current camera info to the console", PERMISSION_REPLAY);
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
	log << "location = x: " << pov.location.X << ", y: " << pov.location.Y << ", z: " << pov.location.Z << std::endl;

	this->log(log.str());
	log.clear();

	log << "rotation = pitch: " << pov.rotation.Pitch << ", roll: " << pov.rotation.Roll << ", yall: " << pov.rotation.Yaw << std::endl;

	this->log(log.str());
}

void CameraControl::onMoveCamera(std::vector<std::string> params)
{
	if (!this->IsApplicable()) {
		return;
	}

	std::stringstream log;

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

	runSafe([this]() {
		this->log("Tryin run safe with exception handlin :v");
		throw std::exception("exception from run safe");
	}, std::bind(&CameraControl::log, this, _1));

	this->log(log.str());
}

