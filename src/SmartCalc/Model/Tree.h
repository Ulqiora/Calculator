#pragma once
#include <exception>
#include <iostream>
#include <memory>

#include "TreeNodes.h"

namespace s21 {

class Tree {
 public:
    Tree();
    Tree(const Tree &tree);

 public:
    double calc(double x);
    void delete_tree();

 private:
    double calc_Arg(sp_node node, double x);

 public:
    void add_node(double value);
    void add_node(char s);
    void add_node(funcD_D f);
    void add_node(Priority p, Direction d, funcD_DD f);
    void add_NewRoot(sp_node node);
    void add_ButtomFunction(sp_node node);
    void add_TopFunction(sp_node node);
    void editCurrentForBiFunc(sp_node node);
    void TreeConnect(Tree tree);
    void treeLoc();
    //    ПОЛЯ КЛАССА
 private:
    sp_node _root;
    sp_node _current;
};

}  // namespace s21
