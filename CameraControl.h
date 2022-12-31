#pragma once

#include "bakkesmod/plugin/bakkesmodplugin.h"

#pragma comment(lib, "pluginsdk.lib")

class CameraControl : public BakkesMod::Plugin::BakkesModPlugin
{
public:
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

