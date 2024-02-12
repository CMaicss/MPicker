#include "pickermanager.h"
#include "screencover.h"
#include <QApplication>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QStyle>
#include <QMenu>
#include <QClipboard>
#include "utils.h"
#include "trayicon.h"
PickerManager* PickerManager::_ins = nullptr;
PickerManager *PickerManager::instance()
{
    if(!_ins) _ins = new PickerManager;
    return _ins;
}

void PickerManager::start()
{
    auto screens = QApplication::screens();
    // 去掉复制屏
    int i = 0;
    while (i < screens.size()) {
        for (int j = screens.size() - 1; j > i; j--) {
            if (screens.at(i)->geometry().topLeft() == screens.at(j)->geometry().topLeft()) {
                screens.removeAt(j);
            }
        }
        i++;
    }

    for (auto screen : screens) {
        QPixmap pix = getScreenShotPixmap(screen);
        ScreenCover* cover = new ScreenCover();
        m_covers.append(cover);
        cover->setScreenPixmap(pix);
        cover->setGeometry(screen->geometry());
        cover->show();
        cover->raise();
        cover->activateWindow();
        cover->setFocus();
    }
}

QPixmap PickerManager::getScreenShotPixmap(QScreen *pScreen)
{
    QPixmap result;
    result = pScreen->grabWindow(0);
    return result;
}

void PickerManager::pickerFinished(const QColor &color)
{
    QClipboard *clipboard = QApplication::clipboard(); //获取系统剪贴板指针
    QString color_name;
    if (m_format == ColorFormat::Hex) {
       color_name = Utils::colorToHex(color);
    } else if (m_format == ColorFormat::CMYK) {
        color_name = Utils::colorToCMYK(color);
    } else if (m_format == ColorFormat::HSV) {
        color_name = Utils::colorToHSV(color);
    } else if (m_format == ColorFormat::RGB) {
        color_name = Utils::colorToRGB(color);
    } else if (m_format == ColorFormat::RGBA) {
        color_name = Utils::colorToRGBA(color);
    } else if (m_format == ColorFormat::FloatRGB) {
        color_name = Utils::colorToFloatRGB(color);
    } else if (m_format == ColorFormat::FloatRGBA) {
        color_name = Utils::colorToFloatRGBA(color);
    }
    qDebug()<<"Picker:"<<color_name;
    clipboard->setText(color_name);//设置剪贴板内容
    m_tray->showMessage("取色器", QString("颜色值 %1 已经复制到您的剪贴板。").arg(color_name));
    close();
}

void PickerManager::popMenu(const QColor &color)
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    m_action_Hex->setText(Utils::colorToHex(color));
    m_action_CMYK->setText(Utils::colorToCMYK(color));
    m_action_HSV->setText(Utils::colorToHSV(color));
    m_action_RGB->setText(Utils::colorToRGB(color));
    m_action_RGBA->setText(Utils::colorToRGBA(color));
    m_action_FloatRGB->setText(Utils::colorToFloatRGB(color));
    m_action_FloatRGBA->setText(Utils::colorToFloatRGBA(color));
    m_menu->exec(QCursor::pos());

    pickerFinished(color);
}

PickerManager::PickerManager(QObject *parent)
    : QObject{parent}
{
    m_tray = new TrayIcon;

    m_action_Hex = new QAction;
    m_action_CMYK = new QAction;
    m_action_HSV = new QAction;
    m_action_RGB = new QAction;
    m_action_RGBA = new QAction;
    m_action_FloatRGB = new QAction;
    m_action_FloatRGBA = new QAction;

    m_menu = new QMenu();
    m_menu->addAction(m_action_Hex);
    m_menu->addAction(m_action_CMYK);
    m_menu->addAction(m_action_HSV);
    m_menu->addAction(m_action_RGB);
    m_menu->addAction(m_action_RGBA);
    m_menu->addAction(m_action_FloatRGB);
    m_menu->addAction(m_action_FloatRGBA);

    connect(m_action_Hex, &QAction::triggered, this, &PickerManager::slotFormatClicked);
    connect(m_action_CMYK, &QAction::triggered, this, &PickerManager::slotFormatClicked);
    connect(m_action_HSV, &QAction::triggered, this, &PickerManager::slotFormatClicked);
    connect(m_action_RGB, &QAction::triggered, this, &PickerManager::slotFormatClicked);
    connect(m_action_RGBA, &QAction::triggered, this, &PickerManager::slotFormatClicked);
    connect(m_action_FloatRGB, &QAction::triggered, this, &PickerManager::slotFormatClicked);
    connect(m_action_FloatRGBA, &QAction::triggered, this, &PickerManager::slotFormatClicked);

    m_format = ColorFormat::Hex;
}

void PickerManager::close()
{
    QApplication::setOverrideCursor(Qt::ArrowCursor);
    for(auto cover : m_covers) {
        cover->hide();
        delete cover;
    }
    m_covers.clear();

}

void PickerManager::slotFormatClicked()
{
    if (sender() == m_action_Hex) {
        m_format = ColorFormat::Hex;
    } else if (sender() == m_action_CMYK) {
        m_format = ColorFormat::CMYK;
    } else if (sender() == m_action_HSV) {
        m_format = ColorFormat::HSV;
    } else if (sender() == m_action_RGB) {
        m_format = ColorFormat::RGB;
    } else if (sender() == m_action_RGBA) {
        m_format = ColorFormat::RGBA;
    } else if (sender() == m_action_FloatRGB) {
        m_format = ColorFormat::FloatRGB;
    } else if (sender() == m_action_FloatRGBA) {
        m_format = ColorFormat::FloatRGBA;
    }
}


