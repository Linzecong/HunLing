#include "../HLBase/HL_GameSystem.h"
#include<QApplication>
#include<HLDataWidget.h>
#include<LGWidget.h>
#include<LHWidget.h>
#include<DataWidget.h>
#include<HLWidget.h>
#include<ItemWidget.h>
#include<TaskMsgWidget.h>
#include<TaskWidget.h>
#include<TimeWidget.h>
#include<FightWidget.h>
#include<MapHLWidget.h>
#include<MapNPCWidget.h>
#include<MapWidget.h>
#include<MainWidget.h>
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







