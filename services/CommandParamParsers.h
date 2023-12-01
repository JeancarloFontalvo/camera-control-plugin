#pragma once
#include "pch.h"
#include "models/base.h"

class CmdParamFactory {

private:
	typedef std::function<BaseModel*(std::vector<std::string>)> Creator;
	static CmdParamFactory* instance;
	CmdParamFactory();
	~CmdParamFactory();
	std::map<std::string, Creator> factories;
public:

	static CmdParamFactory* getInstance();

	// instance methods
	void registerProvider(std::string name, Creator provider);

	template <ModelConcept<BaseModel> T>
	BaseModel* get(std::string name, std::vector<std::string> params);

};

inline void CmdParamFactory::registerProvider(std::string name, Creator provider)
{
	if (this->factories.find(name) != this->factories.end()) {
		return;
	}

	this->factories[name] = provider;
}

template <ModelConcept<BaseModel> T>
inline BaseModel* CmdParamFactory::get(std::string name, std::vector<std::string> params)
{
	if (this->factories.find(name) == this->factories.end()) {

		throw std::exception(std::format("unsupported or not provider found for {}", name).data());
	}

	return this->factories[name](params);
}
