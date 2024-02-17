#include <QApplication>
#include "welcomewidget.h"
#include "pickermanager.h"
#include "utils.h"
void showWelcome();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setApplicationName("MPicker");
    QApplication::setApplicationDisplayName("MPicker");
    QApplication::setQuitOnLastWindowClosed(false);

    auto firstBoot = Utils::getConfig("firstBoot");
    if (!firstBoot.isValid() || !firstBoot.toBool()) {
        showWelcome();
        Utils::setConfig("firstBoot", true);
    }

    QIcon logo(":/logo.svg");
    a.setWindowIcon(logo);
    MANAGER;
    return a.exec();
}

void showWelcome() {
    WelcomeWidget* welcome = new WelcomeWidget;
    welcome->show();
}
