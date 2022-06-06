#pragma once
#include <exception>
#include <functional>
#include <iostream>
#include <memory>

//    *****************************************Resolved_v2.0***************************************
namespace s21 {
using funcD_DD = std::function<double(double, double)>;
using funcD_D = std::function<double(double)>;
enum class Priority { FIRST = 1, SECOND, THIRD, FOURTH };
enum class Direction { BOTTOM, TOP };
enum class LOC { FALSE, TRUE };

class Node_Tree {
 protected:
    std::weak_ptr<Node_Tree> _parent;
    LOC _loc = LOC::FALSE;

 public:
    explicit Node_Tree(std::shared_ptr<Node_Tree> parent) : _parent(parent) {}
    void setLoc() { _loc = LOC::TRUE; }
    bool isLoc() { return _loc == LOC::TRUE; }

    virtual Priority getPriority() = 0;

    virtual std::shared_ptr<Node_Tree> getArg1() = 0;
    virtual void setArg1(std::shared_ptr<Node_Tree> new_arg1) = 0;
    virtual std::shared_ptr<Node_Tree> getArg2() = 0;
    virtual void setArg2(std::shared_ptr<Node_Tree> new_arg2) = 0;

    virtual double calc(double arg1 = 0.0, double arg2 = 0.0, double x = 0.0) = 0;
    void setParent(std::shared_ptr<Node_Tree> new_parent) { _parent = new_parent; }

    virtual Direction getDirection() = 0;

    std::weak_ptr<Node_Tree> getParent() const { return _parent; }

    virtual ~Node_Tree() {}
};

using sp_node = std::shared_ptr<Node_Tree>;

class Node_Value : public Node_Tree {
 private:
    double _value;

 public:
    Node_Value(sp_node parent, double value) : Node_Tree(parent), _value(value) {}

    Priority getPriority() { throw std::invalid_argument("Invalid argument, it is not function1"); }

    sp_node getArg1() { throw std::invalid_argument("Invalid argument, it is not function2"); }
    void setArg1(sp_node new_arg1) { throw std::invalid_argument("Invalid argument, it is not function3"); }
    sp_node getArg2() { throw std::invalid_argument("Invalid argument, it is not function4"); }
    void setArg2(sp_node new_arg2) { throw std::invalid_argument("Invalid argument, it is not function5"); }
    Direction getDirection() { throw std::invalid_argument("Invalid argument, it is not function6"); }
    double calc(double arg1 = 0.0, double arg2 = 0.0, double x = 0.0) { return _value; }
    void setValue(double x) { _value = x; }
    ~Node_Value() {}
};

bool is_value(std::shared_ptr<Node_Tree> arg);

class Node_Variable : public Node_Tree {
 public:
    explicit Node_Variable(std::shared_ptr<Node_Tree> parent) : Node_Tree(parent) {}

    sp_node getArg1() { throw std::invalid_argument("Invalid argument, it is not function"); }
    void setArg1(sp_node new_arg1) { throw std::invalid_argument("Invalid argument, it is not function"); }
    sp_node getArg2() { throw std::invalid_argument("Invalid argument, it is not function"); }
    void setArg2(sp_node new_arg2) { throw std::invalid_argument("Invalid argument, it is not function"); }
    Priority getPriority() { throw std::invalid_argument("Invalid argument, it is not function"); }

    double calc(double arg1 = 0.0, double arg2 = 0.0, double x = 0.0) { return x; }
    Direction getDirection() { throw std::invalid_argument("Invalid argument, it is not function"); }
    ~Node_Variable() {}
};

bool is_variable(std::shared_ptr<Node_Tree> arg);

class Node_Func_un : public Node_Tree {
 protected:
    funcD_D _func;
    Priority _prio = Priority::FOURTH;
    sp_node _arg1;

 public:
    Node_Func_un(sp_node parent, sp_node arg1, funcD_D new_func)
        : Node_Tree(parent), _func(new_func), _arg1(arg1) {}

    Priority getPriority() override { return _prio; }

    sp_node getArg1() override { return _arg1; }
    void setArg1(sp_node new_arg1) override { _arg1 = new_arg1; }
    sp_node getArg2() override { throw std::invalid_argument("Invalid argument, it is not function1"); }
    void setArg2(sp_node new_arg2) override {
        throw std::invalid_argument("Invalid argument, it is not function2");
    }

    double calc(double arg1 = 0.0, double arg2 = 0.0, double x = 0.0) override {
        double result = 0.0;
        result = _func(is_variable(_arg1) ? x : arg1);
        return result;
    }
    Direction getDirection() override {
        throw std::invalid_argument("Invalid argument, it is not function3");
    }
    ~Node_Func_un() {}
};

bool is_unary(std::shared_ptr<Node_Tree> arg);

class Node_Func_bi : public Node_Tree {
 protected:
    funcD_DD _func;
    Priority _prio;
    sp_node _arg1;
    sp_node _arg2;
    Direction _direct;

 public:
    Node_Func_bi(sp_node parent, sp_node arg1, sp_node arg2, Priority new_p, Direction dir, funcD_DD func)
        : Node_Tree(parent), _func(func), _prio(new_p), _arg1(arg1), _arg2(arg2), _direct(dir) {}

    Priority getPriority() override { return _prio; }

    sp_node getArg1() override { return _arg1; }
    void setArg1(sp_node new_arg1) override { _arg1 = new_arg1; }
    sp_node getArg2() override { return _arg2; }
    void setArg2(sp_node new_arg2) override { _arg2 = new_arg2; }

    double calc(double arg1 = 0.0, double arg2 = 0.0, double x = 0.0) override {
        double result = 0.0;
        result = _func(is_variable(_arg1) ? x : arg1, is_variable(_arg2) ? x : arg2);
        return result;
    }
    Direction getDirection() override { return _direct; }
    ~Node_Func_bi() {}
};

bool is_binary(std::shared_ptr<Node_Tree> arg);

}  // namespace s21
