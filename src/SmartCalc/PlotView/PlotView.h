#pragma once

#include <QDialog>

#include "../PlotLibrary/qcustomplot.h"

namespace Ui {
class PlotView;
}

class PlotView : public QDialog {
    Q_OBJECT

 public:
    explicit PlotView(QWidget *parent = nullptr);
    void PlotGraph(std::pair<QVector<double>, QVector<double>> val, double max_x, double max_y);
    ~PlotView();

 private:
    Ui::PlotView *ui;
};
