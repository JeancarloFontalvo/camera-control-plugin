#pragma once
#include "pch.h"
#include "models/base.h"

class CmdParamFactory {

private:
	static CmdParamFactory* instance;
	CmdParamFactory();
	~CmdParamFactory();
	std::map<std::string, std::function<BaseModel(std::vector<std::string>)>> factories;
public:

	static CmdParamFactory* getInstance();

	// instance methods
	void registerProvider(std::string name, std::function<BaseModel(std::vector<std::string>)> provider);

	template <ModelConcept<BaseModel> T>
	T get(std::string name, std::vector<std::string> params);

};

inline void CmdParamFactory::registerProvider(std::string name, std::function<BaseModel(std::vector<std::string>)> provider)
{
	if (this->factories.find(name) != this->factories.end()) {
		return;
	}

	this->factories[name] = provider;
}

template <ModelConcept<BaseModel> T>
inline T CmdParamFactory::get(std::string name, std::vector<std::string> params)
{
	if (this->factories.find(name) == this->factories.end()) {

		throw std::exception(std::format("unsupported or not provider found for {}", name));
	}

	return (T) this->factories[name](params);
}
