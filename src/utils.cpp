#include "utils.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFontMetrics>
#include <QPainter>
#include <QString>
#include <QWidget>
#include <QtMath>
#include <QSettings>
static QMap<Qt::Key, QString> keyMap;
QString Utils::colorToHex(QColor color)
{
    return color.name().toUpper();
}

QString Utils::colorToCMYK(QColor color)
{
    return QString("(%1, %2, %3, %4)").arg(color.cyan()).arg(color.magenta()).arg(color.yellow()).arg(color.black());
}

QString Utils::colorToHSV(QColor color)
{
    return QString("(%1, %2, %3)").arg(color.hue()).arg(color.saturation()).arg(color.value());
}

QString Utils::colorToRGB(QColor color)
{
    return QString("(%1, %2, %3)").arg(color.red()).arg(color.green()).arg(color.blue());
}

QString Utils::colorToRGBA(QColor color)
{
    return QString("(%1, %2, %3, 1.0)").arg(color.red()).arg(color.green()).arg(color.blue());
}

QString Utils::colorToFloatRGB(QColor color)
{
    return QString("(%1, %2, %3)").arg(color.red() / 255.0).arg(color.green() / 255.0).arg(color.blue() / 255.0);
}

QString Utils::colorToFloatRGBA(QColor color)
{
    return QString("(%1, %2, %3, 1.0)").arg(color.red() / 255.0).arg(color.green() / 255.0).arg(color.blue() / 255.0);
}

QString Utils::colorToTColor(QColor color)
{
    return QString::number(color.red() + color.green() * 256 + color.blue() * 256 * 256);
}

#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
void Utils::setProcessAutoRunSelf(bool isstart)
{
    QSettings *settings = new QSettings(AUTO_RUN, QSettings::NativeFormat);

    QString application_name = QApplication::applicationName();
    QString path = settings->value(application_name).toString();

    if(isstart)
    {
        QString appPath = "\"" + QApplication::applicationFilePath() + "\"";
        QString newPath = QDir::toNativeSeparators(appPath);
        if (path != newPath)
        {
            settings->setValue(application_name, newPath);
        }
    }
    else settings->remove(application_name);

    // Thanks to https://blog.csdn.net/thequitesunshine007/article/details/119605740
}

QString Utils::getKeyName(Qt::Key key)
{
    if(keyMap.size() == 0) {
        keyMap.insert(Qt::Key_Control, "Ctrl");
        keyMap.insert(Qt::Key_Alt, "Alt");
        keyMap.insert(Qt::Key_Meta, "Super");
        keyMap.insert(Qt::Key_Up, "↑");
        keyMap.insert(Qt::Key_Down, "↓");
        keyMap.insert(Qt::Key_Left, "←");
        keyMap.insert(Qt::Key_Right, "→");
        keyMap.insert(Qt::Key_Shift, "Shift");
        keyMap.insert(Qt::Key_Enter, "↵");
        keyMap.insert(Qt::Key_Space, "␣");
        keyMap.insert(Qt::Key_1, "1");
        keyMap.insert(Qt::Key_2, "2");
        keyMap.insert(Qt::Key_3, "3");
        keyMap.insert(Qt::Key_4, "4");
        keyMap.insert(Qt::Key_5, "5");
        keyMap.insert(Qt::Key_6, "6");
        keyMap.insert(Qt::Key_7, "7");
        keyMap.insert(Qt::Key_8, "8");
        keyMap.insert(Qt::Key_9, "9");
        keyMap.insert(Qt::Key_0, "0");
        keyMap.insert(Qt::Key_A, "A");
        keyMap.insert(Qt::Key_B, "B");
        keyMap.insert(Qt::Key_C, "C");
        keyMap.insert(Qt::Key_D, "D");
        keyMap.insert(Qt::Key_E, "E");
        keyMap.insert(Qt::Key_F, "F");
        keyMap.insert(Qt::Key_G, "G");
        keyMap.insert(Qt::Key_H, "H");
        keyMap.insert(Qt::Key_I, "I");
        keyMap.insert(Qt::Key_J, "J");
        keyMap.insert(Qt::Key_K, "K");
        keyMap.insert(Qt::Key_L, "L");
        keyMap.insert(Qt::Key_M, "M");
        keyMap.insert(Qt::Key_N, "N");
        keyMap.insert(Qt::Key_O, "O");
        keyMap.insert(Qt::Key_P, "P");
        keyMap.insert(Qt::Key_Q, "Q");
        keyMap.insert(Qt::Key_R, "R");
        keyMap.insert(Qt::Key_S, "S");
        keyMap.insert(Qt::Key_T, "T");
        keyMap.insert(Qt::Key_U, "U");
        keyMap.insert(Qt::Key_V, "V");
        keyMap.insert(Qt::Key_W, "W");
        keyMap.insert(Qt::Key_X, "X");
        keyMap.insert(Qt::Key_Y, "Y");
        keyMap.insert(Qt::Key_Z, "Z");
        keyMap.insert(Qt::Key_Escape, "Esc");
        keyMap.insert(Qt::Key_Tab, "Tab");
        keyMap.insert(Qt::Key_Backspace, "Back");
        keyMap.insert(Qt::Key_Delete, "Del");
        keyMap.insert(Qt::Key_Comma, ",");
        keyMap.insert(Qt::Key_Period, ".");
        keyMap.insert(Qt::Key_Slash, "/");
        keyMap.insert(Qt::Key_Semicolon, ";");
        keyMap.insert(Qt::Key_Equal, "=");
        keyMap.insert(Qt::Key_Apostrophe, "'");
        keyMap.insert(Qt::Key_Minus, "-");
        keyMap.insert(Qt::Key_BracketLeft, "[");
        keyMap.insert(Qt::Key_BracketRight, "]");
    }
    return keyMap.value(key);
}

bool Utils::isAutoRunSelf()
{
    QSettings *settings = new QSettings(AUTO_RUN, QSettings::NativeFormat);

    QString application_name = QApplication::applicationName();
    QString path = settings->value(application_name).toString();

    QString appPath = "\"" + QApplication::applicationFilePath() + "\"";
    QString newPath = QDir::toNativeSeparators(appPath);
    return path == newPath;
}

int Utils::round(double n)
{
    if (n > 0)
        return n - int(n) >= 0.5 ? int(n)+1 : int(n);
    else
        return -n - int(-n) >= 0.5 ? -(int(-n) + 1) : -int(-n);
}
