#pragma once

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#include "framework.h"
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include <bakkesmod/wrappers/wrapperstructs.h>

#include <string>
#include <format>
#include <vector>
#include <functional>
#include <memory>

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_stdlib.h"
#include "IMGUI/imgui_searchablecombo.h"
#include "IMGUI/imgui_rangeslider.h"

#include "logging.h"
#include "shared/models/base.h"
#include "shared/models/SensitivityModel.h"
#include "shared/models/MoveParamsModel.h"