#include "../HLBase/HL_GameSystem.h"
#include<QApplication>
#include<QDesktopWidget>
#include<QPropertyAnimation>
#include<BeginWidget.h>
#include<QTextCodec>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    QTime rankt= QTime::currentTime();
    qsrand(rankt.msecsSinceStartOfDay());//设置随机数种子

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));//设置编码

    QFile file((DATAPATH+"stylesheet.qss"));//读取界面文件qss
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    a.setStyleSheet(in.readAll());
    file.close();

    BeginWidget b;//开始界面，可加动画

   /* QPropertyAnimation *animation = new QPropertyAnimation(&b, "geometry");//后期可加开始动画
    animation->setDuration(300);
    animation->setStartValue(QRect(0, 0, 1080, 640));
    animation->setEndValue(QRect((QApplication::desktop()->width()-1080)/2, (QApplication::desktop()->height()-640)/2, 1080, 640));
    animation->start();*/

    b.showFullScreen();
    return a.exec();
}







