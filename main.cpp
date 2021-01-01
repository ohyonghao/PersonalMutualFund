#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Post");
    QCoreApplication::setOrganizationDomain("ohyonghao.com");
    QCoreApplication::setApplicationName("Personal Mutual Fund");
    MainWindow w;
    w.show();
    return a.exec();
}
