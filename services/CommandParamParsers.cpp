#include "pch.h"
#include "CommandParamParsers.h"

CmdParamFactory* CmdParamFactory::instance = NULL;

CmdParamFactory::CmdParamFactory()
{
    this->factories = std::map<std::string, std::function<BaseModel(std::vector<std::string>)>>();
}

CmdParamFactory::~CmdParamFactory()
{
    this->factories.clear();
}

CmdParamFactory* CmdParamFactory::getInstance()
{
    if (instance == NULL) {
        instance = new CmdParamFactory();
    }

    return instance;
}

