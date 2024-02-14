#ifndef PICKERMANAGER_H
#define PICKERMANAGER_H

#include <QAction>
#include <QObject>
#include <QScreen>
#include <QAbstractNativeEventFilter>
#define MANAGER PickerManager::instance()

class ShortcutEventFilter;
class ScreenCover;
class TrayIcon;
class ShortcutWidget;
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
        TColor,
    };

    static PickerManager* instance();

    void start();
    /**
     * @brief getScreenShotPixmap 获取到某一屏幕的图像
     * @param pScreen 获取截屏的颜色
     */
    QPixmap getScreenShotPixmap(QScreen *pScreen);
    /**
     * @brief showShortcutWidget 显示修改快捷键对话框
     */
    void showShortcutWidget();
    /**
     * @brief registerShortcut 修改快捷键
     * @param mod
     * @param key
     */
    void registerShortcut(const unsigned int& mod, const unsigned int& key);
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
    /**
     * @brief close 关闭拾取
     */
    void close();
private slots:
    void slotFormatClicked();
signals:

private:
    static PickerManager* _ins;
    QVector<ScreenCover*> m_covers;
    ColorFormat m_format;
    QAction* m_action_Hex;
    QAction* m_action_CMYK;
    QAction* m_action_HSV;
    QAction* m_action_RGB;
    QAction* m_action_RGBA;
    QAction* m_action_FloatRGB;
    QAction* m_action_FloatRGBA;
    QAction* m_action_TColor;
    QMenu *m_menu;

    TrayIcon *m_tray;
    ShortcutWidget *m_shortcutWidget;

    ShortcutEventFilter* m_filter;
};

class ShortcutEventFilter : public QAbstractNativeEventFilter {
public:
    ShortcutEventFilter(const unsigned int& mod, const unsigned int& key);
    ~ShortcutEventFilter();
    void registerShortcut(const unsigned int& mod, const unsigned int& key);
public:
    bool nativeEventFilter(const QByteArray &eventType, void *message, qintptr *result);
private:
    unsigned int m_mod, m_key;
};

#endif // PICKERMANAGER_H
