#pragma once
#include <cmath>
#include <cstring>
#include <stack>

#include "FSM.h"
namespace s21 {

class DefaultModel {
 public:
    enum class State {
        START = 0,
        VALUE,
        POINT,
        DECIMAL,
        CHAR_E,
        SIGN_E,
        E_EXP,
        OPERATION,
        OPERATION1,  //    for dinary plus and minus
        FUNCTION,
        SIGN,
        BRACKET_OPEN,
        BRACKET_CLOSE,
        VARIABLE,
        MATH_PI,
        EULER_CONST
    };

    enum class Event {
        E_DIGIT = 0,
        E_POINT,
        E_E,
        E_SIGN,
        E_UNARY,
        E_BINARY,
        E_BRACKET_OPEN,
        E_BRACKET_CLOSE,
        E_MATH_PI,
        E_VARIABLE
    };

 public:
    DefaultModel();

    Tree parseString(std::string const& input_string);

    ~DefaultModel() {}

 private:
    void clearTemp();
    void add_char();
    void add_sign();
    void addFunc();
    void addOper();
    void popTree();
    void createNewTree();

 private:
    //********************************
    //      определение типа символа
    //********************************
 private:
    bool is_PI(char s);
    bool is_number(char s);
    bool is_point(char s);
    bool is_e(char s);
    bool is_sign(char s);
    bool is_operation(char s);
    bool is_function(char s);
    bool is_variable_char(char s);
    bool is_bracketOpen(char s);
    bool is_bracketClose(char s);
    //**********************
    //    Поля Класса
    //**********************
 private:
    int _numBracket;
    char _curChar;
    std::string _temp;
    std::stack<Tree> _trees;
    FSM<State, Event> _machine;
};

std::string convertString(const std::string& inputStr, const std::string& src, const std::string& dst);

}  // namespace s21
