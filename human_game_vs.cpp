#include "human_game_vs.h"
#include "ui_human_game_vs.h"
#include <QPainter>
#include<QPixmap>
#include<QBrush>
#include<QPushButton>
#include <QMouseEvent>
#include<cmath>
#include<QDebug>
#include <QFont>
#include <QLayout>
#include <QTextCodec>
#include<QMessageBox>
#include<qdebug>
#include<algorithm>
extern int people;
int book[17][17];
int space[17][17];
 int chess_sign=4,biaoji=0;
 int chess_x,chess_y,chess_x1,chess_y1,first_x,first_y,sum=0;
 int before_chess_sign;//用作悔棋;
 int overchess=0,over_time_i=0,over_time_j=60;
human_game_vs::human_game_vs(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::human_game_vs)
{
       ui->setupUi(this);
       ui->lcdNumber->display(over_time_j);//显示计时器
       //human_game_vs::resetting_chess();//棋盘初始化
       update();
       setWindowTitle("跳棋");  //设置窗口标题
       time.setParent(this);//设置父对象
       resize(1100,1080);//设置窗口大小
       ret.setParent(this);

       //设计返回按钮参数和函数
       ret.setText("返回");
       ret.move(800,600);
       ret.resize(250,150);

       //设计悔棋按钮参数和函数
       regret.setParent(this);
       regret.setText("悔棋");
       regret.move(800,400);
       regret.resize(250,150);

       //设计出棋按钮参数和函数
       go.setParent(this);
       go.setText("出棋");
       go.move(800,200);
       go.resize(250,150);

       //设置三个按钮和计时器的发出信号条件和发出信号后接收信号的槽函数
       connect(&go,&QPushButton::pressed,this,&human_game_vs::gogogo);
       connect(&ret,&QPushButton::pressed,this,&human_game_vs::ret1);
       connect(&regret,&QPushButton::pressed,this,&human_game_vs::regret_chess);
       connect(&time,&QTimer::timeout,this,&human_game_vs::overtime);



}

human_game_vs::~human_game_vs()
{
    delete ui;
}
//出棋函数
void human_game_vs::gogogo()
{
    // 重置该重置的
    go_times=0;
    go_sign1=0;
    sum=0;
    go_sign=0;
    biaoji=0;
    before_chess_sign=chess_sign;



    if(people==6)  {    //游戏人数为6人时，轮棋设置，以下类推
        if(chess_sign<6)
               chess_sign++;
            else
               chess_sign=1;
    }
    else if(people==4){
            if(chess_sign==4||chess_sign==1)
                chess_sign+=2;
            else if(chess_sign==3)
                chess_sign++;
            else if(chess_sign==6)
                chess_sign=1;
    }
    else if(people==3){
            if(chess_sign==2||chess_sign==4)
                chess_sign+=2;
            else
                chess_sign=2;

    }
    else if(people==2){
            if(chess_sign==4)
                chess_sign=1;
            else
                chess_sign=4;
    }
    over_time_i=0;over_time_j=60;
    ui->lcdNumber->display(over_time_j);

    }
//重置棋子函数。
void human_game_vs::resetting_chess()
{


    if(people!=3){
        for(int i=0;i<17;i++)
            for(int j=0;j<17;j++)
            {
                if(space[j][i]==10||book[j][i]==100)
                    continue;
                if(i<4&&j>3&&j<9)
                    book[j][i]=1;
                else if(i>3&&j<4)
                    book[j][i]=2;
                else if(i>8&&i<13&&j>3&&j<8)
                    book[j][i]=3;
                else if(i>12&&j>8)
                    book[j][i]=4;
                else if(i>8&&i<13&&j>12)
                    book[j][i]=5;
                else if(i>3&&i<8&&j>8&&j<13)
                    book[j][i]=6;
                if((i<4&&j<4)||(i<4&&j>7)||(i<9&&j>12)||(i>12&&j>12)||(i>12&&j<9)||(i>7&&j<4))
                    book[j][i]=100;

            }
    }
    else{   //考虑三人模式的特殊性。
        for(int i=0;i<17;i++)
            for(int j=0;j<17;j++)
            {
                if(space[j][i]==10)
                    continue;
                if(i>3&&j<4)      //棋盘初始化，在每一个该放棋子的位置赋棋子值
                    book[j][i]=2;
                else if(i>12&&j>8)
                    book[j][i]=4;
                else if(i>3&&i<8&&j>8&&j<13)
                    book[j][i]=6;
                else if(i<4&&j>3&&j<9)
                    book[j][i]=10;
                else if(i>8&&i<13&&j>3&&j<8)
                    book[j][i]=10;
                else if(i>8&&i<13&&j>12)
                    book[j][i]=10;
                if((i<4&&j<4)||(i<4&&j>7)||(i<9&&j>12)||(i>12&&j>12)||(i>12&&j<9)||(i>7&&j<4))
                    book[j][i]=100;
            }
    }
                        //优化上述非0值棋子
    //把六角星之外的数组所涉及到的位置全部赋值为100，以便后面的函数处理
    //左中上角无用棋盘
    for(int i=5;i<9;i++)
        for(int j=0;j<i-4;j++)
            book[j][i]=100;

    //左下下角无用棋盘
    for(int i=9;i<12;i++)
        for(int j=14-9+i;j<17;j++)
            book[i][j]=100;

    //右中下角无用棋盘
    for(int i=14;i<17;i++)
        for(int j=9;j<i-14+10;j++)
            book[i][j]=100;

    //右上上角无用棋盘
    for(int j=0;j<3;j++)
        for(int i=5+j;i<8;i++)
            book[i][j]=100;


    //中间待走棋盘赋值为10，以便后面的函数处理
    //中间游戏棋盘
    int sign=0;
    for(int i=4;i<9;i++){
        for(int j=4;j<9+sign;j++)
        {
              book[i][j]=10;
              space[i][j]=10;//用于胜利函数
        }
        sign++;
    }
    sign=0;
    for(int i=12;i>8;i--){
        for(int j=8-sign;j<13;j++)
         {
               book[i][j]=10;
               space[i][j]=10;//用于胜利函数
         }
        sign++;
    }

}
//返回函数。
void human_game_vs::ret1()
{
    //重置该重置的
    //human_game_vs::resetting_chess();
    late_bug=0;
    time.stop();
    go_times=0;
    over_time_i=0;over_time_j=60;
    ui->lcdNumber->display(over_time_j);
    sum=0;
    go_sign=0;
    chess_sign=4;
    biaoji=0;
    go_sign1=0;
    update();
    emit ret_signal_game();//发出返回信号给槽函数处理
}
//超时函数

void human_game_vs::overtime()
{


    over_time_i++;
    over_time_j--;
    if(over_time_i==60){
            human_game_vs::regret_chess();//调用悔棋函数，使已走但未出的棋子返回至初始位置
            human_game_vs::gogogo();  //超时则调用走棋函数，让下一个玩家走棋
            over_time_i=0;over_time_j=60;//重置计时器参数
            update();
    }
}

//绘画事件
void human_game_vs::paintEvent(QPaintEvent *)
{
    QPainter p(this);
   //插入棋盘
    p.drawPixmap(0,0,1100,1080,QPixmap(":/image/image/65.jpg"));
    ui->lcdNumber->display(over_time_j);//显示计时器
    if(!late_bug){
        human_game_vs::resetting_chess();//防止棋子初始化显示不全
        late_bug++;
    }
    //画左斜线。
    double next_y;
    yy=9*15*sqrt(3);left_x=60;right_x=60;
    next_y=yy;
    for(int i=1; i<=17;i++){
        if(i>=1&&i<=4){
            p.drawLine(left_x,next_y,right_x,yy);//给予坐标画线
            left_x+=30;right_x+=60;next_y+=30*sqrt(3);//变化坐标画下一条线
        }
        if(i>=5&&i<=9) {
            if(i==5){
                left_x=60;right_x=7*60;next_y=15*sqrt(3);yy=25*15*sqrt(3);
            }
            p.drawLine(left_x,yy,right_x,next_y);
            left_x+=60;right_x+=30;next_y+=30*sqrt(3);
        }
      if(i>=14&&i<=17){
            if(i==14){
                left_x=10*60;right_x=11*60+30;next_y=19*15*sqrt(3);yy=25*15*sqrt(3);
            }
            p.drawLine(left_x,yy,right_x,next_y);
            left_x+=60;right_x+=30;next_y+=30*sqrt(3);
        }
        if(i>=10&&i<=13) {
            if(i==10){
                left_x=5*60+30;right_x=10*60;next_y=9*15*sqrt(3);yy=27*15*sqrt(3);
            }
            p.drawLine(left_x,yy,right_x,next_y);
            left_x+=30;right_x+=60;yy+=30*sqrt(3);
        }
    }

    //画右斜线
    yy=25*15*sqrt(3);left_x=60;right_x=60;
    next_y=yy;
    for(int i=1; i<=17;i++){
        if(i>=1&&i<=4){
            p.drawLine(left_x,yy,right_x,next_y);
            left_x+=60;right_x+=30;next_y-=30*sqrt(3);
        }
        if(i>=5&&i<=9) {
            if(i==5){
                left_x=420;right_x=60;next_y=33*15*sqrt(3);yy=9*15*sqrt(3);
            }
            p.drawLine(left_x,next_y,right_x,yy);
            left_x+=30;right_x+=60;next_y-=30*sqrt(3);
        }
      if(i>=14&&i<=17){
            if(i==14){
                left_x=11*60+30;right_x=10*60;next_y=15*15*sqrt(3);yy=9*15*sqrt(3);
            }
            p.drawLine(left_x,next_y,right_x,yy);
            left_x+=30;right_x+=60;next_y-=30*sqrt(3);
        }
        if(i>=10&&i<=13) {
            if(i==10){
                left_x=10*60;right_x=5*60+30;next_y=7*15*sqrt(3);yy=25*15*sqrt(3);
            }
            p.drawLine(left_x,yy,right_x,next_y);
            left_x+=60;right_x+=30;next_y-=30*sqrt(3);
        }
    }
    //画横线。
     yy=15*sqrt(3);left_x=420;right_x=420;
    for(int i=1; i<=17;i++){
        if(i>=1&&i<=4){
            p.drawLine(left_x,yy,right_x,yy);
            round_x=left_x;
            for(int j=0;j<=(right_x-left_x)/60;j++)
           {


                //画背景小棋
                QBrush background_chess;//创建画刷
                background_chess.setColor(Qt::white);//给予画刷颜色
                background_chess.setStyle(Qt::SolidPattern);//给予画刷涂色类型
                p.setBrush(background_chess);//将画刷给予画家
                p.drawEllipse(QPointF(round_x,yy),10,10);//让画家画圆
                 round_x+=60;//改变坐标后画下一个圆

           }
            left_x-=30;right_x+=30;;//同上
        }
        if(i>=5&&i<=9) {
            if(i==5){
                left_x=60;right_x=13*60;
            }
            p.drawLine(left_x,yy,right_x,yy);
            round_x=left_x;
            for(int j=0;j<=(right_x-left_x)/60;j++)
           {
                QBrush background_chess;
                background_chess.setColor(Qt::white);
                background_chess.setStyle(Qt::SolidPattern);
                p.setBrush(background_chess);
                p.drawEllipse(QPointF(round_x,yy),10,10);
                round_x+=60;
           }
            left_x+=30;right_x-=30;
        }
        if(i>=14&&i<=17){
            if(i==14){
                left_x=5*60+30;right_x=8*60+30;
            }
            p.drawLine(left_x,yy,right_x,yy);
            //画背景小棋
            round_x=left_x;
            for(int j=0;j<=(right_x-left_x)/60;j++)
           {

                QBrush background_chess;
                background_chess.setColor(Qt::white);
                background_chess.setStyle(Qt::SolidPattern);
                p.setBrush(background_chess);
                p.drawEllipse(QPointF(round_x,yy),10,10);
                round_x+=60;

           }
            left_x+=30;right_x-=30;
        }
        if(i>=10&&i<=13) {
            if(i==10){
                left_x-=60;right_x+=60;
            }
            p.drawLine(left_x,yy,right_x,yy);
            //画背景小棋
            round_x=left_x;
            for(int j=0;j<=(right_x-left_x)/60;j++)
           {

                QBrush background_chess;
                background_chess.setColor(Qt::white);
                background_chess.setStyle(Qt::SolidPattern);
                p.setBrush(background_chess);
                p.drawEllipse(QPointF(round_x,yy),10,10);
                round_x+=60;


           }
            left_x-=30;right_x+=30;
        }
        yy += 30*sqrt(3);
    }

    //
    for(int i=0;i<17;i++)
        for(int j=0;j<17;j++)
        {
            int x,y;
            //数组下标转化为窗口坐标
            y=j*30*sqrt(3)+15*sqrt(3);
            if(j>3)
                x=i*60-(j-4)*30+60;
            else
                x=i*60+(4-j)*30+60;

            //画棋子
            if(book[i][j]==1)
            {
                if(people==2||people==6||people==4)
                {
                            QBrush up;
                            up.setColor(Qt::yellow);
                            up.setStyle(Qt::SolidPattern);
                            p.setBrush(up);
                            p.drawEllipse(QPointF(x,y),15,15);
                }

            }
           else if(book[i][j]==2)
           {
               if(people==3||people==6)
                {
                                QBrush leftup;
                                leftup.setColor(Qt::blue);
                                leftup.setStyle(Qt::SolidPattern);
                                p.setBrush(leftup);
                                p.drawEllipse(QPointF(x,y),15,15);
                 }
           }
           else if(book[i][j]==3)
           {
               if(people==4||people==6)
               {
                           QBrush rightup;
                           rightup.setColor(Qt::black);
                           rightup.setStyle(Qt::SolidPattern);
                           p.setBrush(rightup);
                           p.drawEllipse(QPointF(x,y),15,15);
               }
            }
           else if(book[i][j]==4)
           {
                 QBrush down;
                 down.setColor(Qt::red);
                 down.setStyle(Qt::SolidPattern);
                 p.setBrush(down);
                 p.drawEllipse(QPointF(x,y),15,15);
           }
           else if(book[i][j]==5)
           {
                if(people==6)
                {
                            QBrush rightdown;
                            rightdown.setColor(Qt::lightGray);
                            rightdown.setStyle(Qt::SolidPattern);
                            p.setBrush(rightdown);
                            p.drawEllipse(QPointF(x,y),15,15);
                }
           }
          else if(book[i][j]==6)
          {
                if(people==3||people==4||people==6)
                {
                            QBrush rightup;
                            rightup.setColor(Qt::green);
                            rightup.setStyle(Qt::SolidPattern);
                            p.setBrush(rightup);
                            p.drawEllipse(QPointF(x,y),15,15);
                }
          }
     }
    //出棋提示语设置
    QString str;
         if(chess_sign==4)
             str="红方出棋";
         else if(chess_sign==5)
             str="灰方出棋";
        else if(chess_sign==6)
             str="绿方出棋";
         else if(chess_sign==1)
             str="黄方出棋";
         else if(chess_sign==2)
             str="蓝方出棋";
         else if(chess_sign==3)
             str="黑方出棋";
    int i = 100,j = 800; //str位置
     QPainterPath path;
     QPen pen(Qt::yellow);//轮廓为黑色的
     QPainter painter(this);
     pen.setStyle(Qt::SolidLine);//轮廓线为实线
     pen.setWidth(3);//设置字体轮廓线条粗细
     QFont font("Times New Roman", 30);//设置字体样式与大小
     font.setLetterSpacing(QFont::PercentageSpacing,-2); //设置字间距 默认100%
     font.setLetterSpacing(QFont::AbsoluteSpacing,1);
     font.setBold(true);//设置粗体
     path.addText(i, j, font, str);//add path
     painter.strokePath(path, pen);//set SolidLine style
     painter.fillPath(path, QBrush(Qt::white));//字体颜色
     painter.drawPath(path);
     ui->label_2->setFont(font);
     ui->label->setFont(font);
     ui->label->setText(QString::number(go_times));
     ui->label_3->setFont(font);
     ui->label_4->setFont(font);
     if(biaoji){
     ui->label_3->show();
     ui->label_4->hide();
     }
     else{
     ui->label_4->show();
     ui->label_3->hide();
     }
     update();
}

//鼠标点击事件
void human_game_vs::mousePressEvent(QMouseEvent *e)
{

    if(e->button()==Qt::LeftButton)
    {
       //捕获鼠标左键点击的坐标
        x1=e->x();
        y1=e->y();
        //窗口坐标转化为数组下标
        chess_y=y1/(30*sqrt(3));
        chess_x=(x1+chess_y*30-150)/60;
        qDebug()<<"数组下标"<<chess_x<<chess_y;
        qDebug()<<"数组量"<<book[chess_x][chess_y];
        qDebug()<<"之前标记"<<biaoji;
        sum2=0;
        if(book[chess_x][chess_y]==100)//点击至无用棋盘则结束点击事件
            return;
        if(biaoji&&book[chess_x][chess_y]!=10)//选中即将移动的棋子但点击到不能移动的位置时或选中其他棋子时取消选中，结束事件。
        {
            biaoji=0;
            return;
        }
        if(!biaoji&&go_times>=1&&(chess_y!=after_chess_y||chess_x!=after_chess_x)) //
            return;
        if(book[chess_x][chess_y]==chess_sign){  //选中该走的棋子后标记选中，保存选中棋子下标，结束事件。
             biaoji=1;
             chess_x1=chess_x;
             chess_y1=chess_y;
             qDebug()<<"after_标记"<<biaoji;

        }


        if(biaoji&&book[chess_x][chess_y]==10){
                    //相邻跳的两种情况如下。
            if((chess_x==chess_x1+1&&chess_y==chess_y1)||(chess_x==chess_x1-1&&chess_y==chess_y1)||(chess_y==chess_y1+1&&chess_x==chess_x1)||(chess_y==chess_y1-1&&chess_x==chess_x1)){
                if(go_sign||go_sign1)//相邻跳后则不能继续走棋，也同时消除了相邻跳后走两个棋子的bug。
                  {/*chess_x=chess_x1;chess_y=chess_y1;*/
                    return;}
                qDebug()<<"x1"<<chess_x1<<"y1"<<chess_y1;
                book[chess_x1][chess_y1]=10;//棋子起走位置转为可走位置
                book[chess_x][chess_y]=chess_sign;//可走位置转为棋子起走位置
                update();//更新画面（调用绘画函数）
                biaoji=0;//取消选中
                before_chess_sign=chess_sign;//保存走棋玩家号数，消除悔棋悔到上个玩家的棋子的bug
                if(!sum){ sum++;first_x=chess_x1;first_y=chess_y1;}//悔棋用
                go_sign++;//相邻跳后不能继续走棋
                after_chess_x=chess_x;after_chess_y=chess_y;//保存棋子终走点，用来消除走棋后还能走另一个棋子的bug及悔棋用
                go_times++;//走棋一次，走棋数则加一
                winner_score();//调用胜利函数判断是否胜利


            }
            else if((chess_x==chess_x1-1&&chess_y==chess_y1-1)||(chess_x==chess_x1+1&&chess_y==chess_y1+1)){
                if(go_sign||go_sign1)//相邻跳后则不能继续走棋，也同时消除了相邻跳后走两个棋子的bug。
                 {/*chess_x=chess_x1;chess_y=chess_y1;*/
                    return;}
                qDebug()<<"x1"<<chess_x1<<"y1"<<chess_y1;
                book[chess_x1][chess_y1]=10;
                book[chess_x][chess_y]=chess_sign;
                update();//更新画面（调用绘画函数）
                biaoji=0;
                before_chess_sign=chess_sign;
                if(!sum){ sum++;first_x=chess_x1;first_y=chess_y1;}//悔棋
                go_sign++;//相邻跳后不能再相邻跳  
                after_chess_x=chess_x;after_chess_y=chess_y;
                go_times++;
                winner_score();

            }
           //以上为相邻跳跳法
           //以下为间距跳跳法
            else if(chess_x1==chess_x&&chess_y1!=chess_y){ //列同行不同的间距跳跳法
                if((chess_y1+chess_y)%2!=0||go_sign)//当起走点和终走点不同的下标相加余2等于0才能间距跳  ||  相邻跳后不能间距跳
                    return;
                for(int i=qMin(chess_y1,chess_y)+1;i<qMax(chess_y1,chess_y);i++){
                    if(book[chess_x][i]!=10){
                        sum2++;
                        if(sum2>1)  return;
                    }
                }
                if(book[chess_x1][(chess_y1+chess_y)/2]!=10){  //终走点需是可走棋盘，不然跳过
                    qDebug()<<"x1"<<chess_x1<<"y1"<<chess_y1;
                    go_sign1++;//间距跳后不能相邻跳
                    biaoji=0;//取消选中
                    book[chess_x1][chess_y1]=10;//棋子起走位置转为可走位置
                    book[chess_x][chess_y]=chess_sign;//可走位置转为棋子起走位置
                    before_chess_sign=chess_sign;//保存走棋玩家号数，消除悔棋悔到上个玩家的棋子的bug
                    if(!sum){ sum++;first_x=chess_x1;first_y=chess_y1;}//悔棋用
                    after_chess_x=chess_x;after_chess_y=chess_y;//保存棋子终走点，用来消除走棋后还能走另一个棋子的bug及悔棋用
                    go_times++;//走棋一次，走棋数则加一
                    winner_score();//调用胜利函数判断是否胜利
                    update();//更新画面（调用绘画函数）
                }
            }
            else if(chess_y==chess_y1&&chess_x1!=chess_x){  //行同列不同的间距跳跳法               
                if((chess_x1+chess_x)%2!=0||go_sign)
                    return;
                for(int i=qMin(chess_x1,chess_x)+1;i<qMax(chess_x1,chess_x);i++){
                    if(book[i][chess_y]!=10){
                        sum2++;
                        if(sum2>1)   return;
                    }
                }
                if(book[(chess_x1+chess_x)/2][chess_y1]!=10){
                    qDebug()<<"x1"<<chess_x1<<"y1"<<chess_y1;
                    go_sign1++;
                    biaoji=0;
                    book[chess_x1][chess_y1]=10;

                    book[chess_x][chess_y]=chess_sign;
                    if(!sum){ sum++;first_x=chess_x1;first_y=chess_y1;}//用作悔棋
                    before_chess_sign=chess_sign;
                    after_chess_x=chess_x;after_chess_y=chess_y;
                    go_times++;
                    winner_score();
                    update();
                  }
             }
             else if(chess_y!=chess_y1&&chess_x!=chess_x1){  //行列都不同的的间距跳跳法
                int j=qMin(chess_y,chess_y1)+1;
                if(go_sign||(chess_y1+chess_y)%2!=0||(chess_x1+chess_x)%2!=0)
                    return;
                for(int i=qMin(chess_x1,chess_x)+1;i<qMax(chess_x1,chess_x);i++){
                    if(book[i][j]!=10){
                        sum2++;
                        if(sum2>1)    return;

                    }
                    j++;
                }
                if(book[(chess_x+chess_x1)/2][(chess_y+chess_y1)/2]!=10){
                     qDebug()<<"x1"<<chess_x1<<"y1"<<chess_y1;
                    go_sign1++;
                    biaoji=0;
                    book[chess_x1][chess_y1]=10;
                    book[chess_x][chess_y]=chess_sign;
                    before_chess_sign=chess_sign;
                    if(!sum){ sum++;first_x=chess_x1;first_y=chess_y1;}//用作悔棋
                    after_chess_x=chess_x;after_chess_y=chess_y;
                    go_times++;
                    winner_score();
                    update();
                 }
             }


            }
        }
    }
//悔棋函数
void human_game_vs::regret_chess()
{
    if(chess_sign==before_chess_sign){  //防止出现现出棋玩家没走棋却悔棋导致上一玩家已出的棋子被悔的bug
       //重置该重置的
       go_times=0;
       go_sign=0;
       go_sign1=0;
       sum=0;
       biaoji=0;
       qDebug()<<"x和y"<<chess_x<<chess_y;
       book[after_chess_x][after_chess_y]=10;//把所走的棋的坐标还原为待走游戏棋盘
       book[first_x][first_y]=chess_sign;//所走棋子起点赋值为棋子值
       update();
   }
}
//胜利函数;
void human_game_vs::winner_score()
{
    int sum1=0,sum2=0,sum3=0,sum4=0,sum5=0,sum6=0;
    for(int i=0;i<17;i++)
        for(int j=0;j<17;j++){
    if(book[j][i]==100||book[j][i]==10||space[j][i]==10)
        continue;
    if(i<4&&j>3&&j<9&&book[j][i]==4){
             sum4++;
             if(sum4==10){
                QMessageBox::information(this,"游戏结束","红棋胜利");
                ret1();
             }
    }
    else if(i>3&&j<4&&book[j][i]==5){
        sum5++;
        if(sum5==10){
            QMessageBox::information(this,"游戏结束","灰棋胜利");
            ret1();
        }
    }
    else if(i>8&&i<13&&j>3&&j<8&&book[j][i]==6){
        sum6++;
        if(sum6==10){
             QMessageBox::information(this,"游戏结束","绿棋胜利");
             ret1();
        }
    }
    else if(i>12&&j>8&&book[j][i]==1){
        sum1++;
        if(sum1==10){
             QMessageBox::information(this,"游戏结束","黄棋胜利");
             ret1();
        }
   }
    else if(i>8&&i<13&&j>12&& book[j][i]==2){
        sum2++;
        if(sum2==10){
            QMessageBox::information(this,"游戏结束","蓝棋胜利");
            ret1();
        }
    }
    else if(i>3&&i<8&&j>8&&j<13&&book[j][i]==3){
        sum3++;
        if(sum3==10){
            QMessageBox::information(this,"游戏结束","黑棋胜利");
            ret1();
     }
    }
        }
}
