// SPDX-FileCopyrightText: 2011-2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include <QObject>
#include <QString>
#include <QPainter>
#include <QColor>

class Utils : public QObject
{
    Q_OBJECT
public:
    static QString colorToHex(QColor color);
    static QString colorToCMYK(QColor color);
    static QString colorToHSV(QColor color);
    static QString colorToRGB(QColor color);
    static QString colorToRGBA(QColor color);
    static QString colorToFloatRGB(QColor color);
    static QString colorToFloatRGBA(QColor color);
    static QString colorToTColor(QColor color);
    static void setProcessAutoRunSelf(bool isstart);
    static QString getKeyName(Qt::Key key);
    static bool isAutoRunSelf();
    static int round(double n);
    static unsigned int nativeModifiers(Qt::KeyboardModifiers modifiers);
    static unsigned int nativeKeycode(Qt::Key key);
    static QVariant getConfig(QString name);
    static void setConfig(QString name, QVariant value);
};
