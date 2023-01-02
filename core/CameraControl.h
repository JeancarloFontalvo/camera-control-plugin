#pragma once

#include "pch.h"
#include "bakkesmod/plugin/pluginwindow.h"
#include "services/StateManager.h"

#pragma comment(lib, "pluginsdk.lib")

class CameraControl : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	std::shared_ptr<StateManager> stateManager;

public:
	//constructors
	CameraControl();
	~CameraControl();
	// overrides
	virtual void onLoad();
	virtual void onUnload();
	
	// api
	bool IsApplicable();
private:
	void init();
	void log(std::string message);
	void onCamCommand(std::vector<std::string> params);
	void onMoveCamera(std::vector<std::string> params);
};

