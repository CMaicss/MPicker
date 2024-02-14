#include "shortcutwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QKeyEvent>
#include <QHBoxLayout>
#include "utils.h"
#include "pickermanager.h"
#define PADDING 40
ShortcutWidget::ShortcutWidget(QWidget *parent)
    : QDialog{parent}
{
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setWindowFlag(Qt::Tool);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFixedSize(400, 300);
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
    effect->setColor(QColor(0, 0, 0, 30));
    effect->setBlurRadius(30);
    effect->setOffset(0, 0);
    //this->setGraphicsEffect(effect);

    m_btnOK = new QPushButton(tr("OK"), this);
    m_btnCancel = new QPushButton(tr("Cancel"), this);

    int btnHeight = 24;
    int btnWidth = 130;

    m_btnOK->setGeometry(PADDING + 20, height() - PADDING - 20 - btnHeight, btnWidth, btnHeight);
    m_btnCancel->setGeometry(width() - PADDING - btnWidth - 20, height() - PADDING - 20 - btnHeight, btnWidth, btnHeight);

    connect(m_btnOK, &QPushButton::clicked, this, &ShortcutWidget::slotOK);
    connect(m_btnCancel, &QPushButton::clicked, this, &ShortcutWidget::slotClose);

    m_btnOK->setEnabled(false);
}

void ShortcutWidget::showKeys()
{
    m_keyNames.clear();
    for (int key : m_keyList) {
        QString keyName = Utils::getKeyName(Qt::Key(key));
        m_keyNames.append(keyName);
    }
    repaint();
}

void ShortcutWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(241, 243, 245));
    QPen pen;
    pen.setWidth(1);
    pen.setColor(QColor(221, 223, 225));
    painter.setPen(pen);
    int padding = PADDING;
    QPainterPath bgpath;
    QRect bgrect(padding, padding, width() - padding * 2, height() - padding * 2);
    bgpath.addRoundedRect(bgrect, 8, 8);
    painter.drawPath(bgpath);

    QRect titleRect(padding, padding, width() - 2 * padding, 40);
    QFont titleFont;
    titleFont.setPixelSize(18);
    painter.setPen(QColor(0, 0, 0));
    painter.setFont(titleFont);
    painter.drawText(titleRect, Qt::AlignCenter, tr("Please Enter Shortcut"));

    static QPixmap picture(":/enter-keyboard-shortcut.svg");

    painter.drawPixmap(width() / 2 - picture.width() / 2, 40 + padding + 16, picture);

    QFont keyFont;
    keyFont.setPixelSize(12);
    painter.setPen(QColor(0, 0, 0));
    painter.setFont(keyFont);

    painter.setBrush(QColor(255, 255, 255));
    int aWidth = 0;
    for (int i = 0; i < m_keyNames.size(); i++) {
        QRect frect = painter.fontMetrics().boundingRect(m_keyNames.at(i));
        aWidth += frect.width();
    }
    int keyPadding = 5;
    int keySpace = 4;
    aWidth += m_keyNames.size() * keyPadding * 2;
    aWidth += (m_keyNames.size() - 1) * keySpace;
    int startX = width() / 2 - aWidth / 2;
    int indexX = startX;
    for (int i = 0; i < m_keyNames.size(); i++) {
        QRect frect = painter.fontMetrics().boundingRect(m_keyNames.at(i));
        int twidth = frect.width();
        QRect trect(indexX, height() - PADDING - 20 - 24 - 40, twidth + keyPadding * 2, 20);
        indexX += trect.width() + keySpace;
        painter.drawRoundedRect(trect, 3, 3);
        painter.drawText(trect, Qt::AlignCenter, m_keyNames.at(i));
    }
}

void ShortcutWidget::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    // 如果按键不在支持范围内则忽略
    if (Utils::getKeyName(Qt::Key(key)) == "") {
        return;
    }

    // 如果所有按键是放开状态按下任意按键先清空预选列表A
    if (m_currentKeyList.size() == 0) {
        m_keyList.clear();
    }

    if(key == Qt::Key_Control && m_keyList.contains(Qt::Key_Control)) {
    } else if(key == Qt::Key_Alt && m_keyList.contains(Qt::Key_Alt)) {
        m_keyList.clear();
    } else if(key == Qt::Key_AltGr && m_keyList.contains(Qt::Key_AltGr)) {
        m_keyList.clear();
    } else if(key == Qt::Key_Meta && m_keyList.contains(Qt::Key_Meta)) {
        m_keyList.clear();
    } else {
        for (int key : m_keyList) {
            if (key != Qt::Key_Control && key != Qt::Key_Alt && key != Qt::Key_AltGr && key != Qt::Key_Meta) {
                m_keyList.removeOne(key);
            }
        }
    }
    // 如果当前组合键个数大于等于3则清空
    if (m_keyList.size() >= 3) {
        m_keyList.clear();
    }

    m_keyList.append(key);
    m_currentKeyList.append(key);
    m_key = Qt::Key(key);
    m_modifiers = event->modifiers();
    showKeys();
}

void ShortcutWidget::keyReleaseEvent(QKeyEvent *event)
{
    m_currentKeyList.removeOne(event->key());
    // 若只有修饰按键或只有普通键都不合法，需要清空
    auto cpKeyList = m_keyList;
    int beforSize = cpKeyList.size();
    cpKeyList.removeOne(int(Qt::Key_Control));
    cpKeyList.removeOne(int(Qt::Key_Alt));
    cpKeyList.removeOne(int(Qt::Key_AltGr));
    cpKeyList.removeOne(int(Qt::Key_Meta));
    if (cpKeyList.size() == 0) {
        m_keyList.clear();
    } else if (beforSize == cpKeyList.size()) {
        m_keyList.clear();
    }
    showKeys();

    m_btnOK->setEnabled(!m_keyList.isEmpty());
    if (m_btnOK->isEnabled()) {
        m_btnOK->setFocus();
    }
}

void ShortcutWidget::slotOK()
{
    MANAGER->registerShortcut(Utils::nativeModifiers(m_modifiers), Utils::nativeKeycode(m_key));
    slotClose();
    m_btnOK->setEnabled(false);
}

void ShortcutWidget::slotClose()
{
    m_keyList.clear();
    showKeys();
    close();
}
