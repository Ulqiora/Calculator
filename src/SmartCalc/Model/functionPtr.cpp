#include "functionPtr.h"
namespace s21 {
std::function<double(double)> getFunctionPtr(std::string id) {
    std::function<double(double)> out;
    if (id == "cos") {
        out = [](double x) { return cos(x); };
    } else if (id == "sin") {
        out = [](double x) { return sin(x); };
    } else if (id == "tan") {
        out = [](double x) { return tan(x); };
    } else if (id == "acos") {
        out = [](double x) { return acos(x); };
    } else if (id == "asin") {
        out = [](double x) { return asin(x); };
    } else if (id == "atan") {
        out = [](double x) { return atan(x); };
    } else if (id == "sqrt") {
        out = [](double x) { return sqrt(x); };
    } else if (id == "ln") {
        out = [](double x) { return log(x); };
    } else if (id == "log") {
        out = [](double x) { return log10(x); };
    } else {
        throw std::invalid_argument("Invalid argument, error name function");
    }
    return out;
}

std::function<double(double, double)> getFunctionPtr(char id) {
    std::function<double(double, double)> out;
    if (id == '+') {
        out = [](double x, double y) { return x + y; };
    } else if (id == '-') {
        out = [](double x, double y) { return x - y; };
    } else if (id == '%') {
        out = [](double x, double y) { return fmod(x, y); };
    } else if (id == '*') {
        out = [](double x, double y) { return x * y; };
    } else if (id == '/') {
        out = [](double x, double y) { return x / y; };
    } else if (id == '^') {
        out = [](double x, double y) { return pow(x, y); };
    }
    return out;
}
}  // namespace s21
