#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include<QPushButton>
#include<vs.h>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
private:
    QPushButton ready;
    QPushButton end;
    vs  a;
private:
        void choose();
        void ret();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
