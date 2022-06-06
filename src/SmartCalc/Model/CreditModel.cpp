#include "CreditModel.h"
namespace s21 {
CreditModel::Result CreditModel::calcCredit(TypeCredit type, double creditAmount, double term,
                                            TypeTerm term_t, double interestRate) {
    Result res;
    if (term_t == TypeTerm::YEARS) term *= 12.0;
    interestRate = (interestRate / 100.0) / 12.0;
    if (type == TypeCredit::ANNUITY) {
        res = calcCredit_A(creditAmount, term, interestRate);
    } else {
        res = calcCredit_D(creditAmount, term, interestRate);
    }
    return res;
}

CreditModel::Result CreditModel::calcCredit_A(double creditAmount, double term, double interestRate) {
    Result res;
    res.mountlyPayment.push_back(creditAmount *
                                 (interestRate + interestRate / (pow((1 + interestRate), term) - 1)));
    res.totalPayment = res.mountlyPayment.front() * term;
    res.overpayment = res.totalPayment - creditAmount;
    return res;
}

CreditModel::Result CreditModel::calcCredit_D(double creditAmount, double term, double interestRate) {
    Result res;
    double constPaymentMounth = creditAmount / term;
    double creditBalance = creditAmount;
    do {
        res.mountlyPayment.push_back(constPaymentMounth + creditBalance * interestRate);
        res.totalPayment += res.mountlyPayment.back();
        creditBalance = creditBalance - constPaymentMounth;
    } while (fabs(creditBalance) > 1e-2);
    res.overpayment = res.totalPayment - creditAmount;
    return res;
}
}  // namespace s21
