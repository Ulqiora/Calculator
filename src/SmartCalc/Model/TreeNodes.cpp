#include "TreeNodes.h"
namespace s21 {
bool is_binary(std::shared_ptr<Node_Tree> arg) {
    bool result = false;
    try {
        result = ((std::dynamic_pointer_cast<Node_Func_bi>(arg)) != nullptr);
    } catch (const std::exception& e) {
    }
    return result;
}

bool is_unary(std::shared_ptr<Node_Tree> arg) {
    bool result = false;
    try {
        result = ((std::dynamic_pointer_cast<Node_Func_un>(arg)) != nullptr);
    } catch (const std::exception& e) {
    }
    return result;
}

bool is_variable(std::shared_ptr<Node_Tree> arg) {
    bool result = false;
    try {
        result = ((std::dynamic_pointer_cast<Node_Variable>(arg)) != nullptr);
    } catch (const std::exception& e) {
    }
    return result;
}

bool is_value(std::shared_ptr<Node_Tree> arg) {
    bool result = false;
    try {
        result = ((std::dynamic_pointer_cast<Node_Value>(arg)) != nullptr);
    } catch (const std::exception& e) {
    }
    return result;
}

}  // namespace s21
