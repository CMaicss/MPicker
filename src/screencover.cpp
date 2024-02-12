#include "screencover.h"
#include "pickermanager.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QPainterPath>
#include <QRadialGradient>
#ifdef __WIN32__
#include <Windows.h>
#endif
#define VIEW_SIZE 13
#define VIEW_SCALE 16
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

void ScreenCover::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        MANAGER->clean();
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
    //QRect pix_r(event->x(), event->y(), 11, 11);
    QPoint point = event->pos();
    int scaled_size = VIEW_SIZE * VIEW_SCALE;
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
    m_pix = QApplication::primaryScreen()->grabWindow(0,
                                                      point.x() - (VIEW_SIZE - 1) / 2,
                                                      point.y() - (VIEW_SIZE - 1) / 2,
                                                      VIEW_SIZE / dotsPerInch, VIEW_SIZE/ dotsPerInch);


    QPixmap cursor_pixmap(scaled_size, scaled_size);
    cursor_pixmap.fill(QColor(0, 0, 0, 0));
    QPainter painter(&cursor_pixmap);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制圆形像素区
    painter.save();
    QPainterPath circlePath;
    circlePath.addEllipse(shadow_padding, shadow_padding, scaled_size - 2 * shadow_padding, scaled_size - 2 * shadow_padding);
    painter.setClipPath(circlePath);
    painter.drawPixmap(0, 0, scaled_size, scaled_size, m_pix);
    painter.restore();

    // 绘制中心像素框
    painter.save();
    painter.setPen(QColor(255,220,50));
    painter.setRenderHint(QPainter::Antialiasing, false);
    int c_x = VIEW_SCALE * ((VIEW_SIZE - 1) / 2);
    int c_y = c_x;
    int c_w = VIEW_SCALE;
    int c_h = c_w;
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
    //update();
}

void ScreenCover::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setBrush(m_screen);
    painter.drawRect(rect());
}
