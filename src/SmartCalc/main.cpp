#include <QApplication>

#include "View/ViewApplication.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    s21::CreditModel creditPart;
    s21::DefaultModel defaultPart;
    s21::Controller controll(&defaultPart, &creditPart);
    ViewApplication app(&controll);
    app.connect(&app, SIGNAL(lastWindowClosed()), &app, SLOT(quit()));
    app.show();
    return a.exec();
}
