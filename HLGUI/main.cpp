#include "HLQTData/HL_GameSystem.h"
#include<QApplication>
#include<HLDataWidget.h>
#include<LGWidget.h>
#include<LHWidget.h>
#include<BuffWidget.h>
#include<ButtonWidget.h>
#include<DataWidget.h>
#include<HLWidget.h>
#include<ItemWidget.h>

#include<MapButtonWidget.h>
#include<MessageWidget.h>
#include<TaskMsgWidget.h>
#include<TaskWidget.h>
#include<TimeWidget.h>
#include<UseItemWidget.h>
#include<FightWidget.h>
#include<MapHLWidget.h>
#include<MapNPCWidget.h>
#include<MapWidget.h>
#include<MainWidget.h>
#include<BeginWidget.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BeginWidget b;
    b.show();

    return a.exec();
}







