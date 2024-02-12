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
signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap m_pix;
    QPixmap m_screen;
};

#endif // SCREENCOVER_H
