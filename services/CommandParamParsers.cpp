#include "pch.h"
#include "CommandParamParsers.h"

CmdParamFactory* CmdParamFactory::instance = NULL;

CmdParamFactory::CmdParamFactory()
{
    this->factories = std::map<std::string, Creator>();
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

