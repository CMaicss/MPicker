#include "screencover.h"
#include "pickermanager.h"
#include "utils.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QPainterPath>
#include <QRadialGradient>
#ifdef __WIN32__
#define WINVER 0x0A00
#include <Windows.h>
#include <Winuser.h>
#endif
ScreenCover::ScreenCover(QWidget *parent)
    : QWidget{parent}
{
    // 设置窗口属性
    // X11BypassWindowManagerHint表示不受窗口管理器控制, 好把取色透明窗口铺满全屏
    // WindowStaysOnTopHint 表示窗口永远置顶
    // FramelessWindowHint 表示窗口不显示窗口边框和标题栏
    // Tool 利用Qt::Tool的特有属性实现不在任务栏显示图标
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::Tool);
    // 设置窗口背景透明
    setAttribute(Qt::WA_TranslucentBackground, true);
    setMouseTracking(true);


    m_viewScale = 10;
    m_viewSize = 200;
}

void ScreenCover::setScreenPixmap(const QPixmap &pix)
{
    m_screen = pix;
    update();
}

QColor ScreenCover::color()
{
    return QColor(m_pix.toImage().pixel(m_pix.width() / 2, m_pix.height() / 2));
}

void ScreenCover::updateView()
{
    QPoint point = m_mousePoint;
    int sampleSize = m_viewSize / m_viewScale;
    qreal realyScale = m_viewSize / sampleSize;
    int shadow_padding = 10;
    qreal dotsPerInch = 0;
#ifdef __WIN32__
    HWND hd = GetDesktopWindow();
    int zoom = GetDpiForWindow(hd);
    dotsPerInch = qreal(zoom) / 96;
#elif
    QScreen *screen = qApp->primaryScreen();
    dotsPerInch = screen->logicalDotsPerInchX() / 96;
#endif

    sampleSize = sampleSize / dotsPerInch;
    do {
        sampleSize++;
        m_pix = this->grab(QRect(point.x() - (sampleSize - 1) / 2,
                                 point.y() - (sampleSize - 1) / 2,
                                 sampleSize, sampleSize));
    } while (m_pix.width() % 2 == 0);
    QPixmap cursor_pixmap(m_viewSize, m_viewSize);
    cursor_pixmap.fill(QColor(0, 0, 0, 0));
    QPainter painter(&cursor_pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制圆形像素区
    painter.save();
    QPainterPath circlePath;
    circlePath.addEllipse(shadow_padding, shadow_padding, m_viewSize - 2 * shadow_padding, m_viewSize - 2 * shadow_padding);
    painter.setClipPath(circlePath);
    painter.drawPixmap(0, 0, m_viewSize, m_viewSize, m_pix);
    painter.restore();

    // 绘制中心像素框
    painter.save();
    painter.setPen(QColor(255,220,50));
    painter.setRenderHint(QPainter::Antialiasing, false);
    int c_w = m_viewSize / m_pix.width();
    int c_h = c_w;
    int c_x = m_viewSize / 2 - c_w / 2;
    int c_y = c_x;
    painter.drawRect(c_x, c_y, c_w, c_h);
    painter.restore();

    // 绘制圆形边框
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    QPen pen;
    pen.setWidth(2);
    pen.setColor(QColor(180, 180, 180));
    painter.setPen(pen);
    painter.drawPath(circlePath);
    painter.restore();
    QApplication::setOverrideCursor(QCursor(cursor_pixmap));
}

void ScreenCover::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        MANAGER->close();
    }
}

void ScreenCover::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton) {
        MANAGER->pickerFinished(color());
    } else if (event->button() == Qt::MouseButton::RightButton) {
        MANAGER->popMenu(color());
    }
}

void ScreenCover::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePoint = event->pos();
    updateView();
}

void ScreenCover::wheelEvent(QWheelEvent *event)
{
    int offset = event->angleDelta().y();
    m_viewScale += offset / 120;
    if (m_viewScale < 1) m_viewScale = 1;
    if (m_viewScale > 15) m_viewScale = 15;
    updateView();
}

void ScreenCover::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setBrush(m_screen);
    painter.drawRect(rect());
}
