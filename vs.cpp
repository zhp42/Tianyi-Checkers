#include "vs.h"
#include "ui_vs.h"
#include<QMovie>
#include <QLabel>
vs::vs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vs)
{

     ui->setupUi(this);//载入ui
     QMovie *movie = new QMovie(":/image/image/QQ图片20190423184037.gif");//嵌入动态图
     ui->label->setMovie(movie);//把动态图放入书签插件中
     movie->start();//播放动态图
    resize(500,500);//窗口大小
     setWindowTitle("跳棋");//窗口名称
     human.setText("人人对战");//按钮文本
     human.setParent(this);//设置按钮父对象
     human.move(200,100);//设置按钮位置

     robot.setText("人机对战");
     robot.setParent(this);
     robot.move(200,150);
     link.setText("网络对战");
     link.setParent(this);
     link.move(200,200);

     close.setText("返回");
     close.setParent(this);
     close.move(200,250);
     connect(&close,&QPushButton::pressed,this,&vs::ret);
     connect(&human,&QPushButton::pressed,this,&vs::show_choose_human);
     connect(&a,&human_choose_vs::ret_signal,this,&vs::ret1);
}

vs::~vs()
{
    delete ui;
}
void vs::ret()
{
        emit signal1();
}
void vs::show_choose_human()
{
    this->hide();
    a.show();
}
void vs::ret1()
{
    this->show();
    a.hide();
}
