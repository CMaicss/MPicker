#include <QApplication>
#include "pickermanager.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setApplicationName("MPicker");
    QApplication::setApplicationDisplayName("MPicker");

    MANAGER->start();
    return a.exec();
}
