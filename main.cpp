#include "cddb.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    cddb::init("./cddb.db");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
