#ifndef SCREENCOVER_H
#define SCREENCOVER_H

#include <QWidget>

class ScreenCover : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenCover(QWidget *parent = nullptr);

    /**
     * @brief setScreenPixmap 设置屏幕截屏作为取色背景
     * @param pix 屏幕截屏
     */
    void setScreenPixmap(const QPixmap& pix);

    /**
     * @brief color 获取当前颜色
     * @return 当前颜色
     */
    QColor color();
    /**
     * @brief updateView 刷新放大镜
     */
    void updateView();
signals:

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_pix;
    QPixmap m_screen;
    QPoint m_mousePoint;
    int m_viewSize; // 放大镜的尺寸
    int m_viewScale; // 视口缩放倍率
};

#endif // SCREENCOVER_H
