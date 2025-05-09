#include "widget.h"
#include "ui_widget.h"
#include"vs.h"
#include <QDebug>
#include <QCompleter>
#include <QStringList>
#include <QMovie>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{

    ui->setupUi(this);//载入ui

     resize(500,500);//窗口大小
     ready.setParent(this);//为按钮设置父对象为本窗口
     ready.setText("开始");//按钮文本
     ready.move(200,350);//按钮位置
     end.setText("结束");
     end.move(200,400);
     end.setParent(this);
     connect(&ready,&QPushButton::pressed,this,&Widget::choose);//连接按钮事件与对应的槽函数
     connect(&end,&QPushButton::pressed,this,&Widget::close);
     connect(&a,&vs::signal1,this,&Widget::ret);


       ui->IMAGE->setPixmap(QPixmap(":/image/image/微信图片_20190404130500.jpg"));//嵌入图片
       ui->IMAGE->setScaledContents(true);

}
Widget::~Widget()
{
    delete ui;
}
void Widget::choose()
{
    this->hide();
    a.show();
}
void Widget::ret()
{
    this->show();
    a.hide();
}
