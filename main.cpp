#include "cddb.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    cddb::init("./cddb.db");
    cddb::seedDatabase();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
