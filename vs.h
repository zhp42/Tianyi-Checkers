#ifndef VS_H
#define VS_H
#include<QPushButton>
#include"human_choose_vs.h"
#include <QWidget>

namespace Ui {
class vs;
}

class vs : public QWidget
{
    Q_OBJECT

 private:
    QPushButton human;
    QPushButton robot;
    QPushButton link;
    QPushButton close;
private:
        void ret();
        void ret1();
        void show_choose_human();
       human_choose_vs a;
signals:
        void signal1();
public:
    explicit vs(QWidget *parent = 0);
    ~vs();

private:
    Ui::vs *ui;
};

#endif // VS_H
