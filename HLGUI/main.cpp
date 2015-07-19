#include "../HLBase/HL_GameSystem.h"
#include<QApplication>
#include<QPropertyAnimation>
#include<BeginWidget.h>
#include<QTextCodec>

int main(int argc, char *argv[]){
    QTime rankt= QTime::currentTime();
    qsrand(rankt.msecsSinceStartOfDay());
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    QFile file((DATAPATH+"stylesheet.qss"));
      file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
        a.setStyleSheet(in.readAll());
         file.close();
    BeginWidget b;
    QPropertyAnimation *animation = new QPropertyAnimation(&b, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(0, 0, 100, 30));
    animation->setEndValue(QRect(250, 250, 100, 30));

    animation->start();
     b.show();
    return a.exec();
}







