QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17
QMAKE_CFLAGS_WARN_ON -= -Wextra
QMAKE_CXXFLAGS_WARN_ON -= -Wextra

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/SmartCalc/Model/TreeNodes.cpp \
    ../src/SmartCalc/Model/Tree.cpp \
    ../src/SmartCalc/Model/functionPtr.cpp \
    ../src/SmartCalc/PlotLibrary/qcustomplot.cpp \
    ../src/SmartCalc/main.cpp \
    ../src/SmartCalc/Model/DefaultCalcModel.cpp \
    ../src/SmartCalc/Model/CreditModel.cpp \
    ../src/SmartCalc/Controller/Controller.cpp \
    ../src/SmartCalc/View/ViewApplication.cpp \
    ../src/SmartCalc/PlotView/PlotView.cpp \


HEADERS += \
    ../src/SmartCalc/Model/TreeNodes.h \
    ../src/SmartCalc/Model/functionPtr.h \
    ../src/SmartCalc/Model/DefaultCalcModel.h \
    ../src/SmartCalc/Model/FSM.h \
    ../src/SmartCalc/Model/Tree.h \
    ../src/SmartCalc/Model/CreditModel.h \
    ../src/SmartCalc/Controller/Controller.h \
    ../src/SmartCalc/PlotLibrary//qcustomplot.h \
    ../src/SmartCalc/UI/PlotView.h \
    ../src/SmartCalc/View/ViewApplication.h \
    ../src/SmartCalc/PlotView/PlotView.h

FORMS += \
    ../src/SmartCalc/UI/PlotView.ui \
    ../src/SmartCalc/UI/ViewApplication.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
macx:ICON = ../src/SmartCalc/SmartCalc.icns