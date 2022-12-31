#include "pch.h"
#include "Utils.h"
#include <sstream>

std::string atWithDefault(std::vector<std::string>& vector, int position, const std::string defaultValue)
{
	try
	{
		return vector.at(position);
	}
	catch (const std::exception&)
	{
		return defaultValue;
	}
}

std::string toString(Vector& vector)
{
	std::stringstream str;

	str << vector.X;
	str << vector.Y;
	str << vector.Z;

	return str.str();
}

void runSafe(std::function<void()> action)
{
	try
	{
		action();
	}
	catch (const std::exception&)
	{
		return;
	}
}

void runSafe(std::function<void()> action, std::function<void(std::string)> logger)
{
	try
	{
		action();
	}
	catch (const std::exception& e)
	{
		logger(e.what());
	}
}

template <typename T>
std::string toString(std::vector<T>& vector) 
{
	std::stringstream str;

	for (auto item = vector.begin(); item != vector.end(); item++) {
		str << *item;
	}

	return str.str();
}
