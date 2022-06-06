#include "Tree.h"

namespace s21 {
Tree::Tree() { _root = _current = nullptr; }

Tree::Tree(const Tree &tree) {
    _root = tree._root;
    _current = tree._current;
}
double Tree::calc(double x) { return calc_Arg(_root, x); }

void Tree::delete_tree() { _root = _current = nullptr; }

double Tree::calc_Arg(sp_node node, double x) {
    double res = 0.0;
    if (is_binary(node)) {
        res = node->calc(calc_Arg(node->getArg1(), x), calc_Arg(node->getArg2(), x), x);
    } else if (is_unary(node)) {
        res = node->calc(calc_Arg(node->getArg1(), x), 0.0, x);
    } else if (is_variable(node)) {
        res = node->calc(0.0, 0.0, x);
    } else if (is_value(node)) {
        res = node->calc();
    }
    return res;
}

void Tree::add_node(double value) {
    std::shared_ptr<Node_Tree> node(new Node_Value(nullptr, value));
    if (is_variable(_current) || is_value(_current))
        throw std::invalid_argument("Fatal error, error then adding a node!");
    if (is_unary(_current) && _current->getArg1() != nullptr)
        throw std::invalid_argument("Fatal error, error then adding a node!");
    if (is_binary(_current) && _current->getArg2() != nullptr)
        throw std::invalid_argument("Fatal error, error then adding a node!");
    if (_root == nullptr) {
        _root = _current = node;
    } else if (is_binary(_current) && _current->getArg2() == nullptr) {
        _current->setArg2(node);
        node->setParent(_current);
    } else if (is_unary(_current) && _current->getArg1() == nullptr) {
        _current->setArg1(node);
        node->setParent(_current);
    }
}

void Tree::add_node(char s) {
    std::shared_ptr<Node_Tree> node(new Node_Variable(nullptr));
    if (is_variable(_current) || is_value(_current))
        throw std::invalid_argument("Fatal error, error then adding a node!");
    if (is_unary(_current) && _current->getArg1() != nullptr)
        throw std::invalid_argument("Fatal error, error then adding a node!");
    if (is_binary(_current) && _current->getArg2() != nullptr)
        throw std::invalid_argument("Fatal error, error then adding a node!");
    if (_root == nullptr) {
        _root = _current = node;
    } else if (is_binary(_current) && _current->getArg2() == nullptr) {
        _current->setArg2(node);
        node->setParent(_current);
    } else if (is_unary(_current) && _current->getArg1() == nullptr) {
        _current->setArg1(node);
        node->setParent(_current);
    }
}

void Tree::add_node(funcD_D f) {
    std::shared_ptr<Node_Tree> node(new Node_Func_un(nullptr, nullptr, f));
    if (_current != nullptr) {
        if (is_unary(_current)) {
            _current->setArg1(node);
            node->setParent(_current);
            _current = node;
        } else if (is_binary(_current)) {
            _current->setArg2(node);
            node->setParent(_current);
            _current = node;
        }
    } else {
        _root = _current = node;
    }
}

void Tree::add_node(Priority p, Direction d, funcD_DD f) {
    std::shared_ptr<Node_Tree> node(new Node_Func_bi(nullptr, nullptr, nullptr, p, d, f));
    if (is_unary(_current) && _current->getArg1() == nullptr)
        throw std::invalid_argument("Fatal error, error then adding a node!");
    if (is_binary(_current) && _current->getArg2() == nullptr)
        throw std::invalid_argument("Fatal error, error then adding a node!");
    editCurrentForBiFunc(node);
    if (_current->isLoc()) {
        node->setArg1(_current);
        _current->setParent(node);
        _root = _current = node;
    } else {
        if (is_value(_current) || is_variable(_current)) {
            node->setArg1(_current);
            _current->setParent(node);
            _root = _current = node;
        } else {
            if (_current->getPriority() > node->getPriority()) {
                add_NewRoot(node);
            } else if (_current->getPriority() < node->getPriority()) {
                add_ButtomFunction(node);
            } else {
                if (node->getDirection() == Direction::BOTTOM) {
                    if (_current->getDirection() == Direction::TOP)
                        add_TopFunction(node);
                    else
                        add_ButtomFunction(node);
                } else {
                    add_TopFunction(node);
                }
            }
        }
    }
}

void Tree::add_NewRoot(sp_node node) {
    node->setArg1(_current);
    _current->setParent(node);
    _root = _current = node;
}
void Tree::add_ButtomFunction(sp_node node) {
    node->setArg1(_current->getArg2());
    node->setParent(_current);
    _current->setArg2(node);
    node->getArg1()->setParent(node);
    _current = node;
}
void Tree::add_TopFunction(sp_node node) {
    if (_current->getParent().lock() != nullptr) {
        node->setArg1(_current);
        node->setParent(_current->getParent().lock());
        _current->getParent().lock()->setArg2(node);
        _current->setParent(node);
        _current = node;
    } else {
        node->setArg1(_current);
        _current->setParent(node);
        _root = _current = node;
    }
}

void Tree::editCurrentForBiFunc(sp_node node) {
    if (_current->isLoc()) {
        _current = _current->getParent().lock() == nullptr ? _current : _current->getParent().lock();
    }
    if (node->getDirection() == Direction::BOTTOM) {
        while (_current->getParent().lock() != nullptr && _current->getPriority() > node->getPriority()) {
            _current = _current->getParent().lock();
        }
    } else {
        while (_current->getParent().lock() != nullptr && _current->getPriority() >= node->getPriority()) {
            _current = _current->getParent().lock();
        }
    }
}

void Tree::TreeConnect(Tree tree) {
    if (_current == nullptr) {
        _root = _current = tree._root;
    } else {
        if (is_binary(_current)) {
            _current->setArg2(tree._root);
            tree._root->setParent(_current);
        } else {
            _current->setArg1(tree._root);
            tree._root->setParent(_current);
        }
    }
}
void Tree::treeLoc() { _root->setLoc(); }
}  // namespace s21
