#include "QMW_MAIN.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QMW_MAIN w;
    w.show();
    return a.exec();
}
