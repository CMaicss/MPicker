#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>
#include <QAction>
class TrayIcon : public QObject
{
    Q_OBJECT
public:
    TrayIcon();
    /**
     * @brief showMessage 弹出系统通知
     * @param title 通知标题
     * @param text 通知内容文本
     */
    void showMessage(const QString& title, const QString& text);

    void loadConfig();
private slots:
    /**
     * @brief slotTrayIconActivated 点击托盘图标响应
     * @param reason 托盘图标点击方式
     */
    void slotTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    /**
     * @brief slotActionStart 点击托盘菜单中的拾色按钮
     */
    void slotActionStart();
    /**
     * @brief slotActionExit 点击托盘菜单中的退出按钮
     */
    void slotActionExit();
    /**
     * @brief slotActionAutoRun 设置是否随系统启动
     * @param autoRun 是否自动启动
     */
    void slotActionAutoRun(bool autoRun);
    /**
     * @brief slotActionShortcut 显示快捷键修改对话框
     */
    void slotActionShortcut();
private:
    QSystemTrayIcon* m_tray;
    QMenu* m_menu;
    QAction* m_action_exit;
    QAction* m_action_start;
    QAction* m_action_autoRun;
    QAction* m_action_shortcut;
};

#endif // TRAYICON_H
