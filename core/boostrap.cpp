#include "pch.h"
#include "boostrap.h"
#include "services/CommandParamParsers.h"
#include "constants.h"
#include <utils/parser.h>
#include <shared/utils.h>

void initCommandParamFactory()
{
	CmdParamFactory::getInstance()->registerProvider(constants::CMD_MOVE, [](std::vector<std::string> params) {
	
		auto variable = atWithDefault(params, 1, "");

		if (variable.empty())
			return new MoveParamsModel();

		auto value = get_safe_float(atWithDefault(params, 2, ""));

		return new MoveParamsModel(variable, value);
	});
}
