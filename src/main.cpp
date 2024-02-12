#include <QApplication>
#include "pickermanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setApplicationName("MPicker");
    QApplication::setApplicationDisplayName("MPicker");
    QApplication::setQuitOnLastWindowClosed(false);

    QIcon logo(":/logo.svg");
    a.setWindowIcon(logo);
    MANAGER;
    return a.exec();
}
