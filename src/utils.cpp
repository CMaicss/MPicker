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

bool Utils::isAutoRunSelf()
{
    QSettings *settings = new QSettings(AUTO_RUN, QSettings::NativeFormat);

    QString application_name = QApplication::applicationName();
    QString path = settings->value(application_name).toString();

    QString appPath = "\"" + QApplication::applicationFilePath() + "\"";
    QString newPath = QDir::toNativeSeparators(appPath);
    return path == newPath;
}
