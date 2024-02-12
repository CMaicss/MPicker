#include "utils.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFontMetrics>
#include <QPainter>
#include <QString>
#include <QWidget>
#include <QtMath>

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

