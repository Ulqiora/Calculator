#include "ViewApplication.h"

#include "ui_ViewApplication.h"

ViewApplication::ViewApplication(s21::Controller* c, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::ViewApplication), _control(c) {
    ui->setupUi(this);
    // this->Size
    connect(ui->button0, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button1, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button2, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button3, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button4, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button5, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button6, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button7, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button8, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->button9, SIGNAL(released()), this, SLOT(button_click()));

    connect(ui->buttonX, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonTan, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonAtan, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonCos, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonAcos, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonSin, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonAsin, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonPow, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonSqrt, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonLn, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonLog, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonAdd, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonSub, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonMul, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonDiv, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonBracC, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonBracO, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonPointer, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonMod, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonPI, SIGNAL(released()), this, SLOT(button_click()));
    connect(ui->buttonExp, SIGNAL(released()), this, SLOT(button_click()));

    connect(ui->buttonC, SIGNAL(released()), this, SLOT(button_C_click()));
    connect(ui->buttonAC, SIGNAL(released()), this, SLOT(button_AC_click()));
    connect(ui->buttonEqual, SIGNAL(released()), this, SLOT(calculation()));
    connect(ui->buttonCalcCredit, SIGNAL(released()), this, SLOT(calculationCredit()));
}

ViewApplication::~ViewApplication() { delete ui; }

void ViewApplication::on_tabWidget_currentChanged(int index) { this->setFixedSize(1050, 510); }

void ViewApplication::button_click() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button != nullptr) {
        ui->InputString2->setText("");
        ui->InputString1->setText(ui->InputString1->text() + button->text());
    } else {
        ui->InputString2->setText("Нажата неизвестная клавиша");
    }
}

void ViewApplication::button_C_click() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button != nullptr) {
        ui->InputString2->setText("");
        ui->InputString1->setText("");
    } else {
        ui->InputString2->setText("Нажата неизвестная клавиша");
    }
}

void ViewApplication::button_AC_click() {
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button != nullptr) {
        ui->InputString1->backspace();
    } else {
        ui->InputString2->setText("Нажата неизвестная клавиша");
    }
}

void ViewApplication::calculation() {
    std::string f = ui->InputString1->text().toStdString();
    f = s21::convertString(f, "mod", "%");
    f = s21::convertString(f, "π", "P");
    try {
        Qt::CheckState curState = ui->Plot_or_not->checkState();
        if (curState == Qt::CheckState::Unchecked) {
            double result = _control->calculateDefault(f, ui->buttonXValue->value());
            ui->InputString2->setText(QString::fromStdString(std::to_string(result)));
        } else {
            PlotView fd(nullptr);
            std::pair<QVector<double>, QVector<double>> res =
                _control->calculateDefaultVector(f, ui->buttonXMax->value(), ui->buttonYMax->value());
            fd.PlotGraph(res, ui->buttonXMax->value(), ui->buttonYMax->value());
            fd.exec();
        }
    } catch (const std::exception& e) {
        ui->InputString2->setText(e.what());
    }
}

void ViewApplication::calculationCredit() {
    s21::CreditModel::TypeTerm t_term = ui->Type_term->currentText() == "years"
                                            ? s21::CreditModel::TypeTerm::YEARS
                                            : s21::CreditModel::TypeTerm::MONTH;
    s21::CreditModel::TypeCredit t_credit = ui->Type_credit->currentText() == "Annuity"
                                                ? s21::CreditModel::TypeCredit::ANNUITY
                                                : s21::CreditModel::TypeCredit::DIFF;
    s21::CreditModel::Result result = _control->calculationCredit(
        t_credit, ui->buttonTotalCredit->value(), ui->buttonTerm->value(), t_term, ui->buttonRate->value());

    ui->labelOverpay->setText(QString::fromStdString(std::to_string(result.overpayment)));
    ui->labelTotal->setText(QString::fromStdString(std::to_string(result.totalPayment)));
    if (t_credit == s21::CreditModel::TypeCredit::ANNUITY)
        ui->labelMonthPay->setText(QString::fromStdString(std::to_string(result.mountlyPayment.front())));
    else
        ui->labelMonthPay->setText(QString::fromStdString(std::to_string(result.mountlyPayment.front()) +
                                                          "..." +
                                                          std::to_string(result.mountlyPayment.back())));
}

void ViewApplication::on_ViewApplication_destroyed() { this->close(); }
