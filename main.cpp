#include "widget.h"
#include <QApplication>
int people=0;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    w.setWindowTitle("跳棋");
    w.show();


    return a.exec();
}
