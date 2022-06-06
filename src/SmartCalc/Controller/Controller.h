#pragma once
#include <QVector>

#include "../Model/CreditModel.h"
#include "../Model/DefaultCalcModel.h"
#include "../PlotView/PlotView.h"

namespace s21 {

class Controller {
 public:
    Controller(DefaultModel* d, CreditModel* c);
    double calculateDefault(std::string input_data, double x);
    std::pair<QVector<double>, QVector<double>> calculateDefaultVector(std::string input_data, double max_x,
                                                                       double max_y);
    s21::CreditModel::Result calculationCredit(s21::CreditModel::TypeCredit credit_t, double credit,
                                               double term, s21::CreditModel::TypeTerm term_t, double rate);
    ~Controller();

 private:
    s21::DefaultModel* _defModel;
    s21::CreditModel* _creditModel;
};

}  // namespace s21
