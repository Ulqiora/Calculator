#pragma once
#include <cmath>
#include <iostream>
#include <vector>
namespace s21 {

class CreditModel {
 public:
    enum class TypeCredit { ANNUITY, DIFF };
    enum class TypeTerm { MONTH, YEARS };
    class Result {
     public:
        Result() : mountlyPayment(0), overpayment(0.0), totalPayment(0.0) {}
        std::vector<double> mountlyPayment;
        double overpayment;
        double totalPayment;
    };

 public:
    CreditModel() {}
    Result calcCredit(TypeCredit type, double creditAmount, double term, TypeTerm term_t,
                      double interestRate);
    ~CreditModel() {}

 private:
    Result calcCredit_A(double creditAmount, double term, double interestRate);
    Result calcCredit_D(double creditAmount, double term, double interestRate);
};

}  // namespace s21
