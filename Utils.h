#pragma once
#include <string>
#include <vector>
#include <functional>
#include <bakkesmod/wrappers/wrapperstructs.h>

std::string atWithDefault(std::vector<std::string>& vector, int position, const std::string defaultValue);

std::string toString(Vector& vector);

template <typename T>
std::string toString(std::vector<T>& vector);

void runSafe(std::function<void()> action);
void runSafe(std::function<void()> action, std::function<void(std::string)> logger);