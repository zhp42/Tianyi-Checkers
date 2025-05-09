#ifndef HUMAN_CHOOSE_VS_H
#define HUMAN_CHOOSE_VS_H
#include <QPushButton>
#include <QWidget>
#include"human_game_vs.h"
namespace Ui {
class human_choose_vs;
}

class human_choose_vs : public QWidget
{
    Q_OBJECT
signals:
    void ret_signal();
public:
    explicit human_choose_vs(QWidget *parent = 0);
    ~human_choose_vs();

private:
    Ui::human_choose_vs *ui;
    QPushButton  vs_two;
    QPushButton  vs_three;
    QPushButton  vs_four;
    QPushButton  vs_six;
    QPushButton  vs_off;
    void ret();
    void six_person();
    void four_person();
    void three_person();
    void two_person();
    void game_ret();
    human_game_vs a;
};

#endif // HUMAN_CHOOSE_VS_H
