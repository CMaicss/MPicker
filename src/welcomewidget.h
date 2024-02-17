#ifndef WELCOMEWIDGET_H
#define WELCOMEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
class WelcomeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeWidget(QWidget *parent = nullptr);

signals:

private:
    QLabel* m_title;
    QLabel* m_content;
    QPushButton *m_cancel;
};

#endif // WELCOMEWIDGET_H
