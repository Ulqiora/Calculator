#include "DefaultCalcModel.h"

namespace s21 {

DefaultModel::DefaultModel()
    : _numBracket(0),
      _curChar(),
      _temp(""),
      _trees(),
      _machine(
          "1234567890.e+-*/^%%cosintaqrlgx()P",
          {State::START, State::VALUE, State::POINT, State::DECIMAL, State::CHAR_E, State::CHAR_E,
           State::SIGN_E, State::E_EXP, State::OPERATION, State::OPERATION1, State::FUNCTION, State::SIGN,
           State::BRACKET_CLOSE, State::BRACKET_OPEN, State::VARIABLE, State::MATH_PI, State::EULER_CONST},
          State::START, {State::VALUE, State::DECIMAL, State::E_EXP, State::BRACKET_CLOSE, State::VARIABLE},
          {Event::E_DIGIT, Event::E_POINT, Event::E_E, Event::E_UNARY, Event::E_BINARY, Event::E_SIGN,
           Event::E_VARIABLE}) {
    _machine.addWay(State::START, Event::E_DIGIT, State::VALUE, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::START, Event::E_SIGN, State::SIGN, [this]() { add_sign(); });
    _machine.addWay(State::START, Event::E_BRACKET_OPEN, State::BRACKET_OPEN, [this]() { createNewTree(); });
    _machine.addWay(State::START, Event::E_UNARY, State::FUNCTION, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::START, Event::E_VARIABLE, State::VARIABLE,
                    [this]() { _trees.top().add_node('x'); });
    _machine.addWay(State::START, Event::E_E, State::EULER_CONST,
                    [this]() { _trees.top().add_node(exp(1)); });
    _machine.addWay(State::START, Event::E_MATH_PI, State::MATH_PI,
                    [this]() { _trees.top().add_node(acos(-1)); });
    ////////////////////////////////////////////////////////////////////////////////////
    _machine.addWay(State::MATH_PI, Event::E_SIGN, State::OPERATION1, [this]() { addOper(); });
    _machine.addWay(State::MATH_PI, Event::E_BINARY, State::OPERATION, [this]() { addOper(); });
    _machine.addWay(State::MATH_PI, Event::E_BRACKET_CLOSE, State::BRACKET_CLOSE, [this]() { popTree(); });
    ////////////////////////////////////////////////////////////////////////////////////
    _machine.addWay(State::EULER_CONST, Event::E_SIGN, State::OPERATION1, [this]() { addOper(); });
    _machine.addWay(State::EULER_CONST, Event::E_BINARY, State::OPERATION, [this]() { addOper(); });
    _machine.addWay(State::EULER_CONST, Event::E_BRACKET_CLOSE, State::BRACKET_CLOSE,
                    [this]() { popTree(); });
    ////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////

    _machine.addWay(State::VALUE, Event::E_DIGIT, State::VALUE, [this]() { add_char(); });
    _machine.addWay(State::VALUE, Event::E_POINT, State::POINT, [this]() { add_char(); });
    _machine.addWay(State::VALUE, Event::E_E, State::CHAR_E, [this]() { add_char(); });
    _machine.addWay(State::VALUE, Event::E_SIGN, State::OPERATION1, [this]() {
        _trees.top().add_node(std::stod(_temp));
        addOper();
    });
    _machine.addWay(State::VALUE, Event::E_BINARY, State::OPERATION, [this]() {
        _trees.top().add_node(std::stod(_temp));
        addOper();
    });
    _machine.addWay(State::VALUE, Event::E_BRACKET_CLOSE, State::BRACKET_CLOSE, [this]() {
        _trees.top().add_node(std::stod(_temp));
        popTree();
    });
    ////////////////////////////////////////////////////////////////////////////////////

    _machine.addWay(State::POINT, Event::E_DIGIT, State::DECIMAL, [this]() { add_char(); });
    _machine.addWay(State::DECIMAL, Event::E_DIGIT, State::DECIMAL, [this]() { add_char(); });
    _machine.addWay(State::DECIMAL, Event::E_E, State::CHAR_E, [this]() { add_char(); });
    _machine.addWay(State::DECIMAL, Event::E_SIGN, State::OPERATION1, [this]() {
        _trees.top().add_node(std::stod(_temp));
        addOper();
    });
    _machine.addWay(State::DECIMAL, Event::E_BINARY, State::OPERATION, [this]() {
        _trees.top().add_node(std::stod(_temp));
        addOper();
    });
    _machine.addWay(State::DECIMAL, Event::E_BRACKET_CLOSE, State::BRACKET_CLOSE, [this]() {
        _trees.top().add_node(std::stod(_temp));
        popTree();
    });
    ////////////////////////////////////////////////////////////////////////////////////

    _machine.addWay(State::CHAR_E, Event::E_SIGN, State::SIGN_E, [this]() { add_char(); });
    _machine.addWay(State::CHAR_E, Event::E_DIGIT, State::E_EXP, [this]() { add_char(); });
    ////////////////////////////////////////////////////////////////////////////////////

    _machine.addWay(State::SIGN_E, Event::E_DIGIT, State::E_EXP, [this]() { add_char(); });
    ////////////////////////////////////////////////////////////////////////////////////

    _machine.addWay(State::E_EXP, Event::E_DIGIT, State::E_EXP, [this]() { add_char(); });
    _machine.addWay(State::E_EXP, Event::E_SIGN, State::OPERATION1, [this]() {
        _trees.top().add_node(std::stod(_temp));
        addOper();
    });
    _machine.addWay(State::E_EXP, Event::E_BINARY, State::OPERATION, [this]() {
        _trees.top().add_node(std::stod(_temp));
        addOper();
    });
    _machine.addWay(State::E_EXP, Event::E_BRACKET_CLOSE, State::BRACKET_CLOSE, [this]() {
        _trees.top().add_node(std::stod(_temp));
        popTree();
    });
    ////////////////////////////////////////////////////////////////////////////////////

    _machine.addWay(State::BRACKET_OPEN, Event::E_BRACKET_OPEN, State::BRACKET_OPEN,
                    [this]() { createNewTree(); });
    _machine.addWay(State::BRACKET_OPEN, Event::E_SIGN, State::SIGN, [this]() { add_sign(); });
    _machine.addWay(State::BRACKET_OPEN, Event::E_UNARY, State::FUNCTION, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::BRACKET_OPEN, Event::E_VARIABLE, State::VARIABLE,
                    [this]() { _trees.top().add_node('x'); });
    _machine.addWay(State::BRACKET_OPEN, Event::E_DIGIT, State::VALUE, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::BRACKET_OPEN, Event::E_E, State::EULER_CONST,
                    [this]() { _trees.top().add_node(exp(1)); });
    _machine.addWay(State::BRACKET_OPEN, Event::E_MATH_PI, State::MATH_PI,
                    [this]() { _trees.top().add_node(acos(-1.0)); });

    _machine.addWay(State::FUNCTION, Event::E_UNARY, State::FUNCTION, [this]() { add_char(); });
    _machine.addWay(State::FUNCTION, Event::E_BRACKET_OPEN, State::BRACKET_OPEN, [this]() {
        addFunc();
        createNewTree();
    });

    _machine.addWay(State::VARIABLE, Event::E_BINARY, State::OPERATION, [this]() { addOper(); });
    _machine.addWay(State::VARIABLE, Event::E_SIGN, State::OPERATION1, [this]() { addOper(); });
    _machine.addWay(State::VARIABLE, Event::E_BRACKET_CLOSE, State::BRACKET_CLOSE, [this]() { popTree(); });

    _machine.addWay(State::SIGN, Event::E_VARIABLE, State::VARIABLE, [this]() {
        addFunc();
        _trees.top().add_node('x');
    });
    _machine.addWay(State::SIGN, Event::E_DIGIT, State::VALUE, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::SIGN, Event::E_UNARY, State::FUNCTION, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::SIGN, Event::E_BRACKET_OPEN, State::BRACKET_OPEN, [this]() { createNewTree(); });
    _machine.addWay(State::SIGN, Event::E_SIGN, State::SIGN, [this]() { add_sign(); });
    _machine.addWay(State::SIGN, Event::E_E, State::EULER_CONST,
                    [this]() { _trees.top().add_node(exp(1)); });
    _machine.addWay(State::SIGN, Event::E_MATH_PI, State::MATH_PI,
                    [this]() { _trees.top().add_node(acos(-1.0)); });

    _machine.addWay(State::BRACKET_CLOSE, Event::E_BINARY, State::OPERATION, [this]() { addOper(); });
    _machine.addWay(State::BRACKET_CLOSE, Event::E_SIGN, State::OPERATION1, [this]() { addOper(); });
    _machine.addWay(State::BRACKET_CLOSE, Event::E_BRACKET_CLOSE, State::BRACKET_CLOSE,
                    [this]() { popTree(); });

    _machine.addWay(State::OPERATION, Event::E_VARIABLE, State::VARIABLE,
                    [this]() { _trees.top().add_node('x'); });
    _machine.addWay(State::OPERATION, Event::E_DIGIT, State::VALUE, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::OPERATION, Event::E_BRACKET_OPEN, State::BRACKET_OPEN,
                    [this]() { createNewTree(); });
    _machine.addWay(State::OPERATION, Event::E_UNARY, State::FUNCTION, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::OPERATION, Event::E_E, State::EULER_CONST,
                    [this]() { _trees.top().add_node(exp(1)); });
    _machine.addWay(State::OPERATION, Event::E_MATH_PI, State::MATH_PI,
                    [this]() { _trees.top().add_node(acos(-1.0)); });

    _machine.addWay(State::OPERATION1, Event::E_VARIABLE, State::VARIABLE,
                    [this]() { _trees.top().add_node('x'); });
    _machine.addWay(State::OPERATION1, Event::E_DIGIT, State::VALUE, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::OPERATION1, Event::E_BRACKET_OPEN, State::BRACKET_OPEN,
                    [this]() { createNewTree(); });
    _machine.addWay(State::OPERATION1, Event::E_UNARY, State::FUNCTION, [this]() {
        clearTemp();
        add_char();
    });
    _machine.addWay(State::OPERATION1, Event::E_SIGN, State::SIGN, [this]() { add_sign(); });
    _machine.addWay(State::OPERATION1, Event::E_E, State::EULER_CONST,
                    [this]() { _trees.top().add_node(exp(1)); });
    _machine.addWay(State::OPERATION1, Event::E_MATH_PI, State::MATH_PI,
                    [this]() { _trees.top().add_node(acos(-1.0)); });
}

Tree DefaultModel::parseString(std::string const& input_string) {
    _numBracket = 0.0;
    _machine.resetCurrentState();
    while (_trees.size() != 0) _trees.pop();
    _trees.push(Tree());
    for (auto i : input_string) {
        Event e;
        if (_machine._checkSymbolInAlphabet(i) == false)
            throw std::invalid_argument("Error symbol in string");
        _curChar = i;
        if (is_number(i)) {
            e = Event::E_DIGIT;
        } else if (is_point(i)) {
            e = Event::E_POINT;
        } else if (is_e(i)) {
            e = Event::E_E;
        } else if (is_sign(i)) {
            e = Event::E_SIGN;
        } else if (is_operation(i)) {
            e = Event::E_BINARY;
        } else if (is_function(i)) {
            e = Event::E_UNARY;
        } else if (is_variable_char(i)) {
            e = Event::E_VARIABLE;
        } else if (is_bracketOpen(i)) {
            e = Event::E_BRACKET_OPEN;
            _numBracket++;
        } else if (is_bracketClose(i)) {
            e = Event::E_BRACKET_CLOSE;
            _numBracket--;
        } else if (is_PI(i)) {
            e = Event::E_MATH_PI;
        } else {
            throw std::invalid_argument("Invalid argument, error symbol in string");
        }
        if (_numBracket < 0) throw std::invalid_argument("Invalid argument, bracket number != 0");
        try {
            _machine.process(e);
        } catch (const std::exception& e) {
            throw;
        }
    }
    if (_numBracket != 0) throw std::invalid_argument("Invalid argument, bracket number is not equal 0");
    if (_machine.is_finish()) {
        if (_machine.getCurrentState() == State::VALUE || _machine.getCurrentState() == State::DECIMAL ||
            _machine.getCurrentState() == State::E_EXP)
            _trees.top().add_node(std::stod(_temp));
    } else {
        throw std::invalid_argument("Invalid argument, this string is not correct!");
    }
    return _trees.top();
}

void DefaultModel::clearTemp() { _temp = ""; }
void DefaultModel::add_char() { _temp += _curChar; }
void DefaultModel::add_sign() {
    if (_curChar == '-') {
        _trees.top().add_node([](double x) { return -x; });
    } else {
        _trees.top().add_node([](double x) { return -x; });
    }
}

void DefaultModel::addFunc() { _trees.top().add_node(getFunctionPtr(_temp)); }

void DefaultModel::addOper() {
    if (_curChar == '+') {
        _trees.top().add_node(s21::Priority::FIRST, Direction::BOTTOM,
                              [](double x, double y) { return x + y; });
    } else if (_curChar == '-') {
        _trees.top().add_node(s21::Priority::FIRST, Direction::TOP,
                              [](double x, double y) { return x - y; });
    } else if (_curChar == '%') {
        _trees.top().add_node(s21::Priority::FIRST, Direction::TOP,
                              [](double x, double y) { return fmod(x, y); });
    } else if (_curChar == '*') {
        _trees.top().add_node(s21::Priority::SECOND, Direction::BOTTOM,
                              [](double x, double y) { return x * y; });
    } else if (_curChar == '/') {
        _trees.top().add_node(s21::Priority::SECOND, Direction::TOP,
                              [](double x, double y) { return x / y; });
    } else if (_curChar == '^') {
        _trees.top().add_node(s21::Priority::THIRD, Direction::TOP,
                              [](double x, double y) { return pow(x, y); });
    } else {
        printf("fdsa");
    }
}

void DefaultModel::popTree() {
    s21::Tree t = _trees.top();
    _trees.pop();
    t.treeLoc();
    _trees.top().TreeConnect(t);
}

void DefaultModel::createNewTree() { _trees.push(Tree()); }

bool DefaultModel::is_PI(char s) { return (s == 'P'); }
bool DefaultModel::is_number(char s) { return (std::strchr("1234567890", s) != nullptr); }
bool DefaultModel::is_point(char s) { return (s == '.'); }
bool DefaultModel::is_e(char s) { return (s == 'e'); }
bool DefaultModel::is_sign(char s) { return (s == '+' || s == '-'); }
bool DefaultModel::is_operation(char s) { return s == '*' || s == '/' || s == '^' || s == '%'; }
bool DefaultModel::is_function(char s) { return (std::strchr("cosintaqrlg", s) != nullptr); }
bool DefaultModel::is_variable_char(char s) { return s == 'x'; }
bool DefaultModel::is_bracketOpen(char s) { return s == '('; }
bool DefaultModel::is_bracketClose(char s) { return s == ')'; }
}  // namespace s21
