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
#include<QFrame>

class MapWidget: public QWidget{
	public:
    RenWu* Me;
    DiTu Map;

    QList<NPC> NPC_List;//NPC列表
    QList<QList<LingHuan> > Enemy_List;//列表内含有很多魂灵列表

    MapHLWidget MapHL[10];
    MapNPCWidget MapNPC[10];
	QLabel Title;
    QWidget* Layout1;
    QWidget* Layout2;
    QHBoxLayout* LLayout1;
    QHBoxLayout* LLayout2;

	public:
    MapWidget(DiTu a,RenWu* b);
    ~MapWidget(){}
    void UpDate(DiTu a);//跳转地图后，更新当前界面
    void UpDateNPC(DiTu a);//完成任务后更新地图NPC
};

MapWidget::MapWidget(DiTu a,RenWu* b){
    this->setStyleSheet("background-color:blue");
    Layout1=new QWidget;
    Layout2=new QWidget;
    LLayout1=new QHBoxLayout;
    LLayout2=new QHBoxLayout;

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


    Title.setText(Map.Name);

    for(int i=0;i<9;i++)
    LLayout1->addWidget(&MapHL[i]);
    for(int i=0;i<9;i++)
    LLayout2->addWidget(&MapNPC[i]);

    Layout1->setLayout(LLayout1);

    Layout1->setStyleSheet("background-color:grey");
    Layout2->setLayout(LLayout2);
    Layout2->setStyleSheet("background-color:grey");
    Layout1->setGeometry(3,2,660,151);
    Layout2->setGeometry(3,304,660,151);

    Layout1->setParent(this);
    Layout2->setParent(this);


    Title.setParent(this);
    Title.setAlignment(Qt::AlignCenter);
    Title.setGeometry(290,200,70,30);





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



    Title.setText(Map.Name);
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













