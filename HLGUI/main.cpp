#include "../HLBase/HL_GameSystem.h"
#include<QApplication>
#include<BeginWidget.h>
#include<QTextCodec>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    //设置随机数种子
    QTime rankt= QTime::currentTime();
    qsrand(rankt.msecsSinceStartOfDay());
    //设置编码
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    BeginWidget b;//开始界面
    b.show();
    return a.exec();
}







