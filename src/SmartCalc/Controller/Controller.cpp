#include "Controller.h"
namespace s21 {
Controller::Controller(DefaultModel* d, CreditModel* c) {
    _defModel = d;
    _creditModel = c;
}

Controller::~Controller() {
    delete _defModel;
    delete _creditModel;
}

double Controller::calculateDefault(std::string input_data, double x) {
    try {
        Tree tree(_defModel->parseString(input_data));
        return tree.calc(x);
    } catch (const std::exception& e) {
        throw;
    }
}

s21::CreditModel::Result Controller::calculationCredit(s21::CreditModel::TypeCredit credit_t, double credit,
                                                       double term, s21::CreditModel::TypeTerm term_t,
                                                       double rate) {
    return _creditModel->calcCredit(credit_t, credit, term, term_t, rate);
}
std::pair<QVector<double>, QVector<double>> Controller::calculateDefaultVector(std::string input_data,
                                                                               double max_x, double max_y) {
    std::pair<QVector<double>, QVector<double>> res;
    double x = -max_x;
    try {
        Tree tree(_defModel->parseString(input_data));
        while (x <= max_x) {
            double y = tree.calc(x);
            if (fabs(y) < max_y) {
                res.first.push_back(x);
                res.second.push_back(y);
            }
            x += (0.1);
        }
    } catch (const std::exception& e) {
        throw;
    }
    return res;
}
}  // namespace s21
