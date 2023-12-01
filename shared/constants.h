#pragma once
#include <string>

namespace constants {

	const float DEFAULT_SENSITIVITY = 1.0F;
	const std::string PLUGIN_NAME = "CameraControl";
	const std::string PLUGIN_COMMAND_PREFIX = "camctrl_";

	// variables
	const std::string VAR_ENABLE = "enable";
	const std::string VAR_DEFAULT_SENSITIVITY = "default_sensitivity";
	const std::string VAR_X_SENSITIVITY = "x_sensitivity";
	const std::string VAR_Y_SENSITIVITY = "y_sensitivity";
	const std::string VAR_Z_SENSITIVITY = "z_sensitivity";
	const std::string VAR_ROLL_SENSITIVITY = "roll_sensitivity";
	const std::string VAR_PITCH_SENSITIVITY = "pitch_sensitivity";

	// commands
	const std::string CMD_MOVE = "move";
	const std::string CMD_GET_INFO = "info";

	namespace CmdVariables {
		const std::string VAR_X = "x";
		const std::string VAR_Y = "y";
		const std::string VAR_Z = "z";
		const std::string VAR_ROLL = "roll";
		const std::string VAR_PITCH = "pitch";
	}
}
