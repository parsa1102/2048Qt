#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QVector<QVector<qint64>> gameState;
    void makeGameState();
    void updateUi();
    bool luck();

private slots:
    void righClicked();
    void leftClicked();
    void upClicked();
    void downClicked();

};
#endif // WIDGET_H
