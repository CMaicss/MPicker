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
    void showMessage(const QString& title, const QString& text);
private slots:
    void slotTrayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void slotActionStart();
    void slotActionExit();
private:
    QSystemTrayIcon* m_tray;
    QMenu* m_menu;
    QAction* m_action_exit;
    QAction* m_action_start;
};

#endif // TRAYICON_H
