#pragma once
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
namespace s21 {

std::function<double(double)> getFunctionPtr(std::string id);

std::function<double(double, double)> getFunctionPtr(char id);

}  // namespace s21
