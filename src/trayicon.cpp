#include "trayicon.h"
#include "pickermanager.h"
#include "utils.h"
#include <QApplication>
#include <QMenu>
TrayIcon::TrayIcon()
{
    m_tray = new QSystemTrayIcon(this);
    connect(m_tray, &QSystemTrayIcon::activated, this, &TrayIcon::slotTrayIconActivated);
    QIcon logo(":/logo.svg");
    m_tray->setIcon(logo);
    m_tray->show();

    m_menu = new QMenu;
    m_action_start = new QAction(tr("Pick"));
    m_action_exit = new QAction(tr("Exit"));
    m_action_autoRun = new QAction(tr("Run with system"));
    m_action_autoRun->setCheckable(true);
    connect(m_action_start, &QAction::triggered, this, &TrayIcon::slotActionStart);
    connect(m_action_exit, &QAction::triggered, this, &TrayIcon::slotActionExit);
    connect(m_action_autoRun, &QAction::triggered, this, &TrayIcon::slotActionAutoRun);
    m_menu->addAction(m_action_start);
    m_menu->addAction(m_action_autoRun);
    m_menu->addAction(m_action_exit);

    loadConfig();
}

void TrayIcon::showMessage(const QString &title, const QString &text)
{
    m_tray->showMessage(title, text);
}

void TrayIcon::loadConfig()
{
    m_action_autoRun->setChecked(Utils::isAutoRunSelf());
}

void TrayIcon::slotTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::ActivationReason::Trigger) {
        MANAGER->start();
    } else if (reason == QSystemTrayIcon::ActivationReason::Context) {
        m_menu->exec(QCursor::pos());
    }
}

void TrayIcon::slotActionStart()
{
    MANAGER->start();
}

void TrayIcon::slotActionExit()
{
    QApplication::exit();
}

void TrayIcon::slotActionAutoRun(bool autoRun)
{
    Utils::setProcessAutoRunSelf(autoRun);
}
