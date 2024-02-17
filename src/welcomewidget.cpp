#include "welcomewidget.h"

#include <QVBoxLayout>

WelcomeWidget::WelcomeWidget(QWidget *parent)
    : QWidget{parent}
{
    m_title = new QLabel(tr("使用帮助"), this);
    m_content = new QLabel(this);
    m_cancel = new QPushButton(tr("关闭"), this);

    QVBoxLayout* layout = new QVBoxLayout;

    layout->addWidget(m_title);
    layout->addWidget(m_content);

    QHBoxLayout* btnLayout = new QHBoxLayout;

    btnLayout->addStretch();
    btnLayout->addWidget(m_cancel);

    layout->addLayout(btnLayout);

    setLayout(layout);

    QFont titleFont;
    titleFont.setPointSize(16);
    m_title->setFont(titleFont);
    m_title->setAlignment(Qt::AlignCenter);
    m_title->setFixedHeight(20);

    m_content->setPixmap(QPixmap(":/help.jpg"));
    m_content->setFixedSize(800, 600);

    connect(m_cancel, &QPushButton::clicked, this, [=](){
        this->close();
    });
}
