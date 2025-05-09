#ifndef HUMAN_GAME_VS_H
#define HUMAN_GAME_VS_H

#include <QWidget>
#include <QWidget>
#include<QPushButton>
#include<cmath>
#include <QTimer>  //计时器头文件
#include<QLCDNumber> //显示计时器头文件
#include<QTime>
#include<algorithm>
#include<QtMath>
#include<QtAlgorithms>
namespace Ui {
class human_game_vs;
}

class human_game_vs : public QWidget
{
    Q_OBJECT

public:
    explicit human_game_vs(QWidget *parent = 0);
       ~human_game_vs();
        int x,y,sign;
        int x1,y1;
        int left_x,right_x;
        double yy;
        int round_x;//画背景图的小圆圈坐标;
        int biaoji=0;
        int go_sign=0;
        int after_chess_x,after_chess_y;
        int go_sign1=0;
        int chess_press_x,chess_press_y;
        int go_times=0;
        int sum2=0;
        int late_bug=0;
        QTimer time;

signals:
             void ret_signal_game();
private:
      Ui::human_game_vs *ui;
      void mousePressEvent(QMouseEvent *e);//鼠标点击事件；
      QLCDNumber *show_time;
      QPushButton regret;//设置悔棋按钮；
      QPushButton ret;//设置返回按钮；
      QPushButton go;//设置下棋按钮；

      void gogogo1();
      void paintEvent(QPaintEvent  *);//画棋盘及画棋子事件；
      void ret1();//设置返回按钮属性；
      void regret_chess();//悔棋函数；
      void resetting_chess(); //初始化（重置）棋子函数；
      void gogogo();  //下棋函数；
      void winner_score();//胜利函数；
      void overtime();//超时函数；
};

#endif // HUMAN_GAME_VS_H
