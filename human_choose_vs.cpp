#include "human_choose_vs.h"
#include "ui_human_choose_vs.h"
#include<iostream>
#include <QLabel>
#include <QMovie>
extern int people;
human_choose_vs::human_choose_vs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::human_choose_vs)
{
      ui->setupUi(this);
      QMovie *movie = new QMovie(":/image/image/20140530162134_TWnJz.gif");
      ui->label->setMovie(movie);
      movie->start();


      resize(500,500);
      setWindowTitle("跳棋");
      vs_two.setParent(this);
      vs_two.setText("双人对战");
      vs_two.move(200,100);

      vs_three.setParent(this);
      vs_three.setText("三人对战");
      vs_three.move(200,150);

      vs_four.setParent(this);
      vs_four.setText("四人对战");
      vs_four.move(200,200);

      vs_six.setParent(this);
      vs_six.setText("六人对战");
      vs_six.move(200,250);

      vs_off.setParent(this);
      vs_off.setText("返回");
      vs_off.move(200,300);
      connect(&vs_off,&QPushButton::pressed,this,&human_choose_vs::ret);
      connect(&vs_six,&QPushButton::pressed,this,&human_choose_vs::six_person);
      connect(&vs_four,&QPushButton::pressed,this,&human_choose_vs::four_person);
      connect(&vs_three,&QPushButton::pressed,this,&human_choose_vs::three_person);
      connect(&vs_two,&QPushButton::pressed,this,&human_choose_vs::two_person);
      connect(&a,&human_game_vs::ret_signal_game,this,&human_choose_vs::game_ret);

      //connect(&a,&vs_human::signal1,this,&Widget::ret);
}

human_choose_vs::~human_choose_vs()
{
    delete ui;
}
void human_choose_vs::game_ret()
{
    this->show();
    a.hide();
}

void human_choose_vs::ret()
{
    emit  ret_signal();
}
void human_choose_vs::six_person()
{
     people=6;
    this->hide();
    a.show();
    a.time.start(1000);
}
void human_choose_vs::four_person()
{
    people=4;
    this->hide();
    a.show();
    a.time.start(1000);
}
void human_choose_vs::three_person()
{
     people=3;
    this->hide();
    a.show();
    a.time.start(1000);
}
void human_choose_vs::two_person()
{
     people=2;
    this->hide();
    a.show();
    a.time.start(1000);
}
