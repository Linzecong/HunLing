/*主界面显示地图详情，包括魂灵，NPC*/

#ifndef MAPWIDGET
#define MAPWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<../HLBase/HL_DiTu.h>
#include<../HLBase/HL_RenWu.h>
#include<../HLBase/HL_NPC.h>
#include<MapHLWidget.h>
#include<MapNPCWidget.h>
#include<QList>

class MapWidget: public QWidget{
	public:
    RenWu* Me;
    DiTu Map;

    QList<NPC> NPC_List;//NPC列表
    QList<QList<LingHuan> > Enemy_List;//列表内含有很多魂灵列表

    MapHLWidget MapHL[10];
    MapNPCWidget MapNPC[10];
	QLabel Title;
    QHBoxLayout* Layout1;
    QHBoxLayout* Layout2;
    QVBoxLayout* MainLayout;
	public:
    MapWidget(DiTu a,RenWu* b);
    ~MapWidget(){}
    void UpDate(DiTu a);//跳转地图后，更新当前界面
    void UpDateNPC(DiTu a);//完成任务后更新地图NPC
};

MapWidget::MapWidget(DiTu a,RenWu* b){
    Layout1=new QHBoxLayout;
    Layout2=new QHBoxLayout;
    MainLayout=new QVBoxLayout;
    Map=a;
    Me=b;

    NPC_List=GameSystem::CanShowList(Map);//初始化NPC列表

    for(int i=0;i<9;i++)
    Enemy_List.append(GameSystem::CreateLHList(Map));//初始化魂灵列表的列表

    for(int i=0;i<NPC_List.size();i++)//加载魂灵和NPC窗口
        MapNPC[i].UpDateAll(Me,NPC_List[i]);

    for(int i=0;i<Enemy_List.size();i++)
        MapHL[i].UpDateAll(Me,Enemy_List[i]);

    for(int i=0;i<9;i++){//清除
        MapHL[i].Clear();
        MapNPC[i].Clear();
    }

    for(int i=0;i<NPC_List.size();i++)//加载
        MapNPC[i].UpDateAll(Me,NPC_List[i]);

    for(int i=0;i<Enemy_List.size();i++)
        MapHL[i].UpDateAll(Me,Enemy_List[i]);


    Title.setText(Map.Name+"<br>"+Map.Des);
    for(int i=0;i<9;i++)
    Layout1->addWidget(&MapHL[i]);
    for(int i=0;i<9;i++)
    Layout2->addWidget(&MapNPC[i]);

    MainLayout->addLayout(Layout1);

    MainLayout->addWidget(&Title);

    MainLayout->addLayout(Layout2);
    this->setLayout(MainLayout);
}

void MapWidget::UpDate(DiTu a){
    Map=a;
    NPC_List=GameSystem::CanShowList(Map);//重新生成NPC列表

    Enemy_List.clear();

    for(int i=0;i<GetNumber(0,9);i++)//重新生成魂灵列表
    Enemy_List.append(GameSystem::CreateLHList(Map));

    for(int i=0;i<9;i++){//清除
        MapHL[i].Clear();
        MapNPC[i].Clear();
    }

    for(int i=0;i<NPC_List.size();i++)//加载
        MapNPC[i].UpDateAll(Me,NPC_List[i]);

    for(int i=0;i<Enemy_List.size();i++)
        MapHL[i].UpDateAll(Me,Enemy_List[i]);



    Title.setText(Map.Name+"<br>"+Map.Des);
}

void MapWidget::UpDateNPC(DiTu a){//专门用于只更新NPC
    Map=a;
    NPC_List=GameSystem::CanShowList(Map);

    for(int i=0;i<9;i++)
        MapNPC[i].Clear();

    for(int i=0;i<NPC_List.size();i++)
        MapNPC[i].UpDateAll(Me,NPC_List[i]);

}


#endif













