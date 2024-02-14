#ifndef SHORTCUTWIDGET_H
#define SHORTCUTWIDGET_H

#include <QDialog>
#include <QLabel>
class ShortcutWidget : public QDialog
{
    Q_OBJECT
public:
    explicit ShortcutWidget(QWidget *parent = nullptr);

    void showKeys();
protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent* event) override;

    void keyReleaseEvent(QKeyEvent* event) override;
private slots:
    void slotOK();
    void slotClose();
signals:

private:
    QPushButton* m_btnOK;
    QPushButton* m_btnCancel;
    QVector<int> m_keyList;
    QVector<int> m_currentKeyList;
    QVector<QString> m_keyNames;
    Qt::KeyboardModifiers m_modifiers;
    Qt::Key m_key;
};

#endif // SHORTCUTWIDGET_H
