#pragma once

#include <QMainWindow>
#include <QVector>

#include "../Controller/Controller.h"

namespace Ui {
class ViewApplication;
}

class ViewApplication : public QMainWindow {
    Q_OBJECT

 public:
    explicit ViewApplication(s21::Controller* c, QWidget* parent = nullptr);
    ~ViewApplication();

 private slots:
    void button_click();
    void button_C_click();
    void button_AC_click();
    void calculation();
    void calculationCredit();
    void on_tabWidget_currentChanged(int index);

    void on_ViewApplication_destroyed();

 private:
    Ui::ViewApplication* ui;
    s21::Controller* _control;
};
