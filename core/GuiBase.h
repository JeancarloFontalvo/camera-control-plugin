#pragma once
#include "bakkesmod/plugin/pluginwindow.h"

class PluginWindowBase : public BakkesMod::Plugin::PluginWindow
{
public:
	virtual ~PluginWindowBase() = default;

	bool isWindowOpen_ = false;
	std::string menuTitle_ = "BakkesPluginTemplate1";

	std::string GetMenuName() override;
	std::string GetMenuTitle() override;
	void SetImGuiContext(uintptr_t ctx) override;
	bool ShouldBlockInput() override;
	bool IsActiveOverlay() override;
	void OnOpen() override;
	void OnClose() override;
	void Render() override;

	virtual void RenderWindow() = 0;
};