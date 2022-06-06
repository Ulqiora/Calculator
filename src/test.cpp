#include <gtest/gtest.h>

#include <cmath>

#include "SmartCalc/Model/CreditModel.h"
#include "SmartCalc/Model/DefaultCalcModel.h"

s21::DefaultModel pars;
s21::CreditModel credit;

TEST(Tree, easy_1) {
    try {
        std::string input = "10+10*2";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), 30.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Tree, easy_2) {
    try {
        std::string input = "5^2*2";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), 50.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Tree, easy_3) {
    try {
        std::string input = "1+2*3^4-5";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), 158.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}
TEST(Tree, easy_4) {
    try {
        std::string input = "1-2-3-4";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), -8.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Tree, easy_5) {
    try {
        std::string input = "10-10/2";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), 5.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}
TEST(Tree, easy_6) {
    try {
        std::string input = "2-3^4/5";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), -14.2, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Tree, easy_7) {
    try {
        std::string input = "4*(-4)";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), -16.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Tree, easy_8) {
    try {
        std::string input = "-----5";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), -5.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Tree, easy_9) {
    try {
        std::string input = "4*(-4)";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), -16.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Tree, easy_10) {
    try {
        std::string input = "5*8/2*9";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), 180.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Tree, easy_11) {
    try {
        std::string input = "(cos(1))^2+(sin(1))^2";
        s21::Tree tree = pars.parseString(input);
        ASSERT_NEAR(tree.calc(0.0), 1.0, 1e-6);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Credit, easy_1) {
    try {
        s21::CreditModel::Result res = credit.calcCredit(s21::CreditModel::TypeCredit::ANNUITY, 1000000.0,
                                                         24, s21::CreditModel::TypeTerm::MONTH, 24.0);
        ASSERT_NEAR(res.mountlyPayment.front(), 52871.10, 1);
        ASSERT_NEAR(res.overpayment, 268906.40, 1);
        ASSERT_NEAR(res.totalPayment, 1268906.40, 1);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

TEST(Credit, easy_2) {
    try {
        s21::CreditModel::Result res = credit.calcCredit(s21::CreditModel::TypeCredit::DIFF, 1000000.0, 24,
                                                         s21::CreditModel::TypeTerm::MONTH, 24.0);
        ASSERT_NEAR(res.mountlyPayment.front(), 61666.67, 1);
        ASSERT_NEAR(res.mountlyPayment.back(), 42500.00, 1);
        ASSERT_NEAR(res.overpayment, 250000.00, 1);
        ASSERT_NEAR(res.totalPayment, 1250000.00, 1);
    } catch (const std::exception& e) {
        ASSERT_NEAR(1.0, 30.0, 1e-6);
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
