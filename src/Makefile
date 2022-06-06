BD=../build/
CC=g++
APP=$(BD)SmartCalc.app
CFLAGS=-c
GTESTFLAGS=-lgtest -lpthread
MAN=./Documentation

SOURCES=./SmartCalc/SmartCalc/Model/Default/TreeNodes.cpp \
        ./SmartCalc/SmartCalc/Model/Default/functionPtr.cpp \
        ./SmartCalc/PlotLibrary//qcustomplot.cpp \
        ./SmartCalc/main.cpp \
        ./SmartCalc/Model/Default/DefaultCalcModel.cpp \
        ./SmartCalc/Model/Credit/CreditModel.cpp \
        ./SmartCalc/Controller/Controller.cpp \
        ./SmartCalc/View/ViewApplication.cpp \
        ./SmartCalc/PlotView/PlotView.cpp
HEADERS=./Model/Default/TreeNodes.h \
        ./Model/Default/functionPtr.h \
        ./Model/Default/DefaultCalcModel.h \
        ./Model/Default/FSM.h \
        ./Model/Default/Tree.h \
        ./Model/Credit/CreditModel.h \
        ./Controller/Controller.h \
        ./PlotLibrary/qcustomplot.h \
        ./UI/PlotView.h \
        ./View/ViewApplication.h \
        ./PlotView/PlotView.h

all: build

build: $(BD)SmartCalc.pro
	cd $(BD); qmake SmartCalc.pro
	make -C $(BD)

./$(BD)SmartCalc.pro:
	cp SmartCalc.pro $(BD)

./$(BD)%.o: */*/%.cpp
	$(CC) $(CFLAGS) $< -o $@

install: build
	@mkdir $(HOME)/Applications/SmartCalc/ 2>/dev/null
	cp -rf $(APP) $(HOME)/Applications/SmartCalc/
	cp -rf $(MAN) $(HOME)/Applications/SmartCalc/
	make clean

uninstall: 
	rm -rf $(HOME)/Applications/SmartCalc

clean:
	rm -rf ./$(BD)* ./../build/.qmake.stash ./../build/Makefile
dvi:
	open doc.pdf

dist:
	tar -cvf $(HOME)/Applications/SmartCalc/../SmartCalc.tar $(HOME)/Applications/SmartCalc.app/ ./doc.pdf
	gzip $(HOME)/Applications/SmartCalc/../SmartCalc.tar
#    TESTS

./$(BD)test.o: test.cpp
	$(CC) $(CFLAGS) $< -o $@

tests: $(BD)CreditModel.o $(BD)DefaultCalcModel.o $(BD)functionPtr.o $(BD)Tree.o $(BD)TreeNodes.o $(BD)test.o
	$(CC) $^ -o $(BD)test $(GTESTFLAGS) -I./ -L./
	./$(BD)test
leaks:
	leaks --atExit -- ./$(BD)test

cpplint:
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp ./SmartCalc/*.cpp ./SmartCalc/Controller/*.cpp ./SmartCalc/Model/*.cpp ./SmartCalc/PlotView/*.cpp ./SmartCalc/View/*.cpp
	python3 ../materials/linters/cpplint.py --extensions=h ./SmartCalc/Controller/*.h ./SmartCalc/Model/*.h ./SmartCalc/PlotView/*.h ./SmartCalc/View/*.h