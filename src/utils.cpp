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
#include <windows.h>
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

unsigned int Utils::nativeModifiers(Qt::KeyboardModifiers modifiers)
{
    quint32 native = 0;
    if (modifiers & Qt::ShiftModifier)
        native |= MOD_SHIFT;
    if (modifiers & Qt::ControlModifier)
        native |= MOD_CONTROL;
    if (modifiers & Qt::AltModifier)
        native |= MOD_ALT;
    if (modifiers & Qt::MetaModifier)
        native |= MOD_WIN;
    return native;
}

unsigned int Utils::nativeKeycode(Qt::Key key)
{
    switch (key)
    {
    case Qt::Key_Escape:
        return VK_ESCAPE;
    case Qt::Key_Tab:
    case Qt::Key_Backtab:
        return VK_TAB;
    case Qt::Key_Backspace:
        return VK_BACK;
    case Qt::Key_Return:
    case Qt::Key_Enter:
        return VK_RETURN;
    case Qt::Key_Insert:
        return VK_INSERT;
    case Qt::Key_Delete:
        return VK_DELETE;
    case Qt::Key_Pause:
        return VK_PAUSE;
    case Qt::Key_Print:
        return VK_PRINT;
    case Qt::Key_Clear:
        return VK_CLEAR;
    case Qt::Key_Home:
        return VK_HOME;
    case Qt::Key_End:
        return VK_END;
    case Qt::Key_Left:
        return VK_LEFT;
    case Qt::Key_Up:
        return VK_UP;
    case Qt::Key_Right:
        return VK_RIGHT;
    case Qt::Key_Down:
        return VK_DOWN;
    case Qt::Key_PageUp:
        return VK_PRIOR;
    case Qt::Key_PageDown:
        return VK_NEXT;
    case Qt::Key_F1:
        return VK_F1;
    case Qt::Key_F2:
        return VK_F2;
    case Qt::Key_F3:
        return VK_F3;
    case Qt::Key_F4:
        return VK_F4;
    case Qt::Key_F5:
        return VK_F5;
    case Qt::Key_F6:
        return VK_F6;
    case Qt::Key_F7:
        return VK_F7;
    case Qt::Key_F8:
        return VK_F8;
    case Qt::Key_F9:
        return VK_F9;
    case Qt::Key_F10:
        return VK_F10;
    case Qt::Key_F11:
        return VK_F11;
    case Qt::Key_F12:
        return VK_F12;
    case Qt::Key_F13:
        return VK_F13;
    case Qt::Key_F14:
        return VK_F14;
    case Qt::Key_F15:
        return VK_F15;
    case Qt::Key_F16:
        return VK_F16;
    case Qt::Key_F17:
        return VK_F17;
    case Qt::Key_F18:
        return VK_F18;
    case Qt::Key_F19:
        return VK_F19;
    case Qt::Key_F20:
        return VK_F20;
    case Qt::Key_F21:
        return VK_F21;
    case Qt::Key_F22:
        return VK_F22;
    case Qt::Key_F23:
        return VK_F23;
    case Qt::Key_F24:
        return VK_F24;
    case Qt::Key_Space:
        return VK_SPACE;
    case Qt::Key_Asterisk:
        return VK_MULTIPLY;
    case Qt::Key_Plus:
        return VK_ADD;
    case Qt::Key_Comma:
        return VK_SEPARATOR;
    case Qt::Key_Minus:
        return VK_SUBTRACT;
    case Qt::Key_Slash:
        return VK_DIVIDE;
    case Qt::Key_MediaNext:
        return VK_MEDIA_NEXT_TRACK;
    case Qt::Key_MediaPrevious:
        return VK_MEDIA_PREV_TRACK;
    case Qt::Key_MediaPlay:
        return VK_MEDIA_PLAY_PAUSE;
    case Qt::Key_MediaStop:
        return VK_MEDIA_STOP;
    case Qt::Key_VolumeDown:
        return VK_VOLUME_DOWN;
    case Qt::Key_VolumeUp:
        return VK_VOLUME_UP;
    case Qt::Key_VolumeMute:
        return VK_VOLUME_MUTE;

    case Qt::Key_0:
    case Qt::Key_1:
    case Qt::Key_2:
    case Qt::Key_3:
    case Qt::Key_4:
    case Qt::Key_5:
    case Qt::Key_6:
    case Qt::Key_7:
    case Qt::Key_8:
    case Qt::Key_9:
        return key;

    case Qt::Key_A:
    case Qt::Key_B:
    case Qt::Key_C:
    case Qt::Key_D:
    case Qt::Key_E:
    case Qt::Key_F:
    case Qt::Key_G:
    case Qt::Key_H:
    case Qt::Key_I:
    case Qt::Key_J:
    case Qt::Key_K:
    case Qt::Key_L:
    case Qt::Key_M:
    case Qt::Key_N:
    case Qt::Key_O:
    case Qt::Key_P:
    case Qt::Key_Q:
    case Qt::Key_R:
    case Qt::Key_S:
    case Qt::Key_T:
    case Qt::Key_U:
    case Qt::Key_V:
    case Qt::Key_W:
    case Qt::Key_X:
    case Qt::Key_Y:
    case Qt::Key_Z:
        return key;

    default:
        return 0;
    }
}

#define CONFIG_PATH "HKEY_CURRENT_USER\\Software\\Maicss\\MPicker"
QVariant Utils::getConfig(QString name)
{
    QSettings *settings = new QSettings(CONFIG_PATH, QSettings::NativeFormat);
    return settings->value(name);
}

void Utils::setConfig(QString name, QVariant value)
{
    QSettings *settings = new QSettings(CONFIG_PATH, QSettings::NativeFormat);
    settings->setValue(name, value);
}
