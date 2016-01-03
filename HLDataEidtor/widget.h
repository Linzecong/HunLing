#ifndef WIDGET_H
#define WIDGET_H
#define DATAPATH QString("./Data/")
#include <QString>
#include<QFile>
#include<QLineEdit>
#include<QLabel>
#include<QSpinBox>
#include<QWidget>
#include<QListWidget>
#include<QPushButton>
#include<QTextStream>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QComboBox>
#include "Edit_DiTu.h"
#include "Edit_HunJi&Buff.h"
#include "Edit_HunLing.h"
#include "Edit_Item.h"
#include "Edit_Message.h"
#include "Edit_NPC.h"
#include "Edit_Task.h"

#include "NewTask.h"

class Widget : public QWidget
{
public:
    Widget(QWidget *parent = 0);
    ~Widget();
public:
    TaskWidget Task_W;
    NPCWidget NPC_W;
    MsgWidget Msg_W;
    ItemWidget Item_W;
    HLWidget HL_W;
    SkillWidget Skill_W;
    MapWidget Map_W;

    NewTask* New_TaskWidget;

    QLabel Name;

    QPushButton Button[7];
    QPushButton NewButton[7];

    QVBoxLayout MainLayout;

public:
    void NewTaskClick();


};



Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    SystemBuff[0].Init();
    SystemHJ[0].Init();
    SystemHL[0].Init();
    SystemItem[0].Init();
    SystemMap[0][0].Init();
    SystemMessage[0].Init();
    SystemNPC[0].Init();
    SystemTask[0].Init();



    Name.setText("HL Editor");
    MainLayout.addWidget(&Name);
    for(int i=0;i<7;i++)
        MainLayout.addWidget(&Button[i]);
    for(int i=0;i<7;i++)
        MainLayout.addWidget(&NewButton[i]);


    Button[0].setText("TaskWidget");
    Button[1].setText("NPCWidget");
    Button[2].setText("MsgWidget");
    Button[3].setText("ItemWidget");
    Button[4].setText("HLWidget");
    Button[5].setText("SkillWidget");
    Button[6].setText("MapWidget");

    NewButton[0].setText("NewTaskWidget");
    NewButton[1].setText("NewNPCWidget");
    NewButton[2].setText("NewMsgWidget");
    NewButton[3].setText("NewItemWidget");
    NewButton[4].setText("NewHLWidget");
    NewButton[5].setText("NewSkillWidget");
    NewButton[6].setText("NewMapWidget");

    connect(&Button[0],&QPushButton::clicked,&Task_W,&TaskWidget::show);
    connect(&Button[1],&QPushButton::clicked,&NPC_W,&NPCWidget::show);
    connect(&Button[2],&QPushButton::clicked,&Msg_W,&MsgWidget::show);
    connect(&Button[3],&QPushButton::clicked,&Item_W,&ItemWidget::show);
    connect(&Button[4],&QPushButton::clicked,&HL_W,&HLWidget::show);
    connect(&Button[5],&QPushButton::clicked,&Skill_W,&SkillWidget::show);
    connect(&Button[6],&QPushButton::clicked,&Map_W,&MapWidget::show);

    connect(&NewButton[0],&QPushButton::clicked,this,&Widget::NewTaskClick);

    this->setLayout(&MainLayout);
}

Widget::~Widget()
{

}

void Widget::NewTaskClick(){
    New_TaskWidget=new NewTask;
int temp=New_TaskWidget->exec();

if(temp==QDialog::Accepted){
    New_TaskWidget->Save();
    SystemTask[New_TaskWidget->tempTask.ID]=New_TaskWidget->tempTask;
}

delete New_TaskWidget;


}
#endif // WIDGET_H
