#pragma once
#include "pch.h"
#include <string>
#include <vector>
#include <functional>

std::string atWithDefault(std::vector<std::string>& vector, int position, const std::string defaultValue);

std::string toString(Vector& vector);

template <typename T>
std::string toString(std::vector<T>& vector);

void runSafe(std::function<void()> action);
void runSafe(std::function<void()> action, std::function<void(std::string)> logger);

std::string commandNameResolver(std::string name);


template<typename T>
inline T& also(T& it, std::function<void(T&)> action)
{
	action(it);

	return it;
}

template<typename T>
inline T& also(T&& it, std::function<void(T&)> action)
{
	action(it);

	return it;
}

template<typename T, typename U>
inline U let(T& it, std::function<U(T&)> mapper)
{
	return mapper(it);
}

template<typename T, typename U>
inline U let(T&& it, std::function<U(T&)> mapper)
{
	return mapper(it);
}
