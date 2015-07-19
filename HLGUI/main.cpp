#include "../HLBase/HL_GameSystem.h"
#include<QApplication>

#include<BeginWidget.h>
#include<QTextCodec>

int main(int argc, char *argv[]){
    QTime rankt= QTime::currentTime();
    qsrand(rankt.msecsSinceStartOfDay());
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    BeginWidget b;
    b.show();
    return a.exec();
}







