#include "SyntacticAnalyzer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    SyntacticAnalyzer w;
    w.show();
    return a.exec();
}
