#ifndef PICKERMANAGER_H
#define PICKERMANAGER_H

#include <QAction>
#include <QObject>
#include <QScreen>
#include <QSystemTrayIcon>
#define MANAGER PickerManager::instance()


class ScreenCover;
class PickerManager : public QObject
{
    Q_OBJECT
    friend ScreenCover;
public:

    enum ColorFormat {
        Hex,
        CMYK,
        HSV,
        RGB,
        RGBA,
        FloatRGB,
        FloatRGBA,
    };

    static PickerManager* instance();

    void start();
    /**
     * @brief getScreenShotPixmap 获取到某一屏幕的图像
     * @param pScreen 获取截屏的颜色
     */
    QPixmap getScreenShotPixmap(QScreen *pScreen);

protected:
    /**
     * @brief pickerFinished 左键点击后的颜色
     * @param color 选中的颜色
     */
    void pickerFinished(const QColor &color);
    /**
     * @brief popMenu 弹出右键菜单
     * @param color 选中的颜色
     */
    void popMenu(const QColor &color);
private:
    explicit PickerManager(QObject *parent = nullptr);

private slots:
    void slotFormatClicked();
signals:

private:
    static PickerManager* _ins;
    QVector<ScreenCover*> m_covers;
    QSystemTrayIcon* m_tray;
    ColorFormat m_format;
    QAction* m_action_Hex;
    QAction* m_action_CMYK;
    QAction* m_action_HSV;
    QAction* m_action_RGB;
    QAction* m_action_RGBA;
    QAction* m_action_FloatRGB;
    QAction* m_action_FloatRGBA;
    QMenu* m_menu;
};

#endif // PICKERMANAGER_H
