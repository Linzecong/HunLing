/*主窗口*/

#ifndef MAINWIDGET
#define MAINWIDGET

#include<QString>
#include<QWidget>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QKeyEvent>
#include<QMessageBox>
#include<../HLBase/HL_GameSystem.h>
#include<TimeWidget.h>
#include<MapWidget.h>
#include<ItemWidget.h>
#include<LGWidget.h>
#include<LHWidget.h>
#include<TaskWidget.h>
#include<QApplication>
class BuffWidget: public QDialog{
    public:
    TimeWidget* Time_Widget;
    QList<Buff> List;
    QLabel Buff1;
    QLabel Buff2;
    QVBoxLayout MainLayout;
    public:
    BuffWidget(QList<Buff> a);

    ~BuffWidget(){}

};


BuffWidget::BuffWidget(QList<Buff> a){
    this->setFixedWidth(200);
    this->setWindowTitle("被动列表");
    this->setObjectName("main");
        Time_Widget=new TimeWidget;
    List=a;
    Buff1.setText("战前Buff：<br>");
    for(int i=0;i<a.size();i++)
        if(a[i].type==1&&a[i].ID!=0)
            Buff1.setText(Buff1.text()+a[i].Name+"："+a[i].Des+"<br>");

    Buff2.setText("战中Buff：<br>");
    for(int i=0;i<a.size();i++)
        if(a[i].type==2&&a[i].ID!=0)
            Buff1.setText(Buff1.text()+a[i].Name+"："+a[i].Des+"<br>");
    MainLayout.addWidget(&Buff1);
    MainLayout.addWidget(&Buff2);
    this->setLayout(&MainLayout);

}


class DataWidget: public QWidget{
    public:
    RenWu* Me;
    QLabel Title;
    QLabel Name;
    QLabel Level;
    QLabel Exp;
    QLabel Coin;
    QLabel LingHuan;//颜色
    QLabel Strength;
    QLabel Agility;
    QLabel Vitality;
    QLabel Energy;
    QLabel Sour;
    QVBoxLayout* MainLayout;


public:
DataWidget(RenWu* a);
~DataWidget(){}
void UpDate();

};

DataWidget::DataWidget(RenWu* a){

    this->setObjectName("main");
    this->setFixedSize(150,470);
     MainLayout=new QVBoxLayout;
    Me=a;
    Title.setText("人物信息：");
    Name.setText("名字："+Me->Name);
    Level.setText("等级："+QString::number(Me->LV)+"级");
    Exp.setText("经验："+QString::number(Me->Exp_Now)+"/"+QString::number(Me->Exp_Need));
    Coin.setText("金币："+QString::number(Me->Coin));
    for(int i=0;i<Me->LH.size();i++)
    LingHuan.setText(LingHuan.text()+Me->LH[i].Col);
    LingHuan.setText("灵环："+LingHuan.text());
    Strength.setText("力量："+QString::number(Me->Strength)+"("+QString::number(Me->Ori_Strength)+")");
    Agility.setText("敏捷："+QString::number(Me->Agility)+"("+QString::number(Me->Ori_Agility)+")");
    Vitality.setText("体力："+QString::number(Me->Vitality)+"("+QString::number(Me->Ori_Vitality)+")");
    Energy.setText("魂力："+QString::number(Me->Energy)+"("+QString::number(Me->Ori_Energy)+")");
    Sour.setText("灵力："+QString::number(Me->Sour)+"("+QString::number(Me->Ori_Sour)+")");

    MainLayout->addWidget(&Title);
    MainLayout->addWidget(&Name);
    MainLayout->addWidget(&Level);
    MainLayout->addWidget(&Exp);
    MainLayout->addWidget(&Coin);
    MainLayout->addWidget(&LingHuan);
    MainLayout->addWidget(&Strength);
    MainLayout->addWidget(&Agility);
    MainLayout->addWidget(&Vitality);
    MainLayout->addWidget(&Energy);
    MainLayout->addWidget(&Sour);



    this->setLayout(MainLayout);

}

void DataWidget::UpDate(){
    Title.setText("人物信息：");
    Name.setText("名字："+Me->Name);
    Level.setText("等级："+QString::number(Me->LV)+"级");
    Coin.setText("金币："+QString::number(Me->Coin));
    Exp.setText("经验："+QString::number(Me->Exp_Now)+"/"+QString::number(Me->Exp_Need));
    LingHuan.setText("");
    for(int i=0;i<Me->LH.size();i++)
    LingHuan.setText(LingHuan.text()+Me->LH[i].Col);
    LingHuan.setText("灵环："+LingHuan.text());
    Strength.setText("力量："+QString::number(Me->Strength)+"("+QString::number(Me->Ori_Strength)+")");
    Agility.setText("敏捷："+QString::number(Me->Agility)+"("+QString::number(Me->Ori_Agility)+")");
    Vitality.setText("体力："+QString::number(Me->Vitality)+"("+QString::number(Me->Ori_Vitality)+")");
    Energy.setText("魂力："+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Ori_Sour));
    Me->UpdateBuff();

}



class MapButtonWidget: public QWidget{
    public:
    PushButton BuffButton;
    PushButton BagButton;
    PushButton TaskButton;
    PushButton LGButton;
    PushButton LHButton;
    PushButton SaveButton;
    PushButton HelpButton;
    PushButton QuitButton;
    QVBoxLayout* MainLayout;
    MapButtonWidget();

    ~MapButtonWidget(){}

};

MapButtonWidget::MapButtonWidget(){

    this->setObjectName("main");
    QuitButton.setObjectName("close");

    this->setFixedSize(150,470);

    MainLayout=new QVBoxLayout;
    BagButton.setText("背包");
    TaskButton.setText("任务");
    LGButton.setText("灵骨");
    LHButton.setText("灵环");
    BuffButton.setText("被动");
    SaveButton.setText("保存");
    HelpButton.setText("帮助");
    QuitButton.setText("退出");

    BagButton.setFixedSize(130,45);
    TaskButton.setFixedSize(130,45);
    LGButton.setFixedSize(130,45);
    LHButton.setFixedSize(130,45);
    BuffButton.setFixedSize(130,45);
    SaveButton.setFixedSize(130,45);
    HelpButton.setFixedSize(130,45);
    QuitButton.setFixedSize(130,45);

    MainLayout->addWidget(&BagButton);
    MainLayout->addWidget(&TaskButton);
    MainLayout->addWidget(&LGButton);
    MainLayout->addWidget(&LHButton);
    MainLayout->addWidget(&BuffButton);
    MainLayout->addWidget(&SaveButton);
    MainLayout->addWidget(&HelpButton);
    MainLayout->addWidget(&QuitButton);
    this->setLayout(MainLayout);



}

class MainWidget:public QWidget{
	public:
    GameSystem* Game;
	DataWidget* Data_Widget;
    BuffWidget* Buff_Widget;
	MapWidget* Map_Widget;
	ItemWidget* Item_Widget;
	LGWidget* LG_Widget;
	LHWidget* LH_Widget;
    TaskWidget* Task_Widget;
	MapButtonWidget* MapButton_Widget;

    QVBoxLayout* Layout1;
    QHBoxLayout* MainLayout;

	public:
    MainWidget();
    ~MainWidget(){}

    void Quit();
	void Save();
    void Help();
	void ShowItem();
    void ShowTask();
	void ShowLG();
	void ShowLH();
    void ShowBuff();
    void xia();
    void shang();
    void zuo();
    void you();


protected:
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *e);


};
void MainWidget::closeEvent(QCloseEvent *e){
    QApplication::closeAllWindows();

}



MainWidget::MainWidget(){
    QSound::play(DATAPATH+"背景.wav");
    this->setWindowFlags (Qt::CustomizeWindowHint);

this->setObjectName("main");



   this->setFixedSize(QSize(1000,480));
    Layout1=new QVBoxLayout;
    MainLayout=new QHBoxLayout;
Game=new GameSystem;
Data_Widget=new DataWidget(&Game->Me);


MapButton_Widget=new MapButtonWidget;
Map_Widget=new MapWidget(SystemMap[Game->Me.PosX][Game->Me.PosY],&Game->Me);
Buff_Widget=new BuffWidget(Game->Me.myBuffList);
Layout1->addWidget(Map_Widget);
MainLayout->addWidget(Data_Widget);
MainLayout->addLayout(Layout1);
MainLayout->addWidget(MapButton_Widget);

connect(&MapButton_Widget->QuitButton,&QPushButton::clicked,this,&MainWidget::Quit);
connect(&MapButton_Widget->SaveButton,&QPushButton::clicked,this,&MainWidget::Save);
connect(&MapButton_Widget->HelpButton,&QPushButton::clicked,this,&MainWidget::Help);
connect(&MapButton_Widget->BagButton,&QPushButton::clicked,this,&MainWidget::ShowItem);
connect(&MapButton_Widget->TaskButton,&QPushButton::clicked,this,&MainWidget::ShowTask);
connect(&MapButton_Widget->LGButton,&QPushButton::clicked,this,&MainWidget::ShowLG);
connect(&MapButton_Widget->LHButton,&QPushButton::clicked,this,&MainWidget::ShowLH);
connect(&Buff_Widget->Time_Widget->timer,&QTimer::timeout,Data_Widget,&DataWidget::UpDate);
connect(&MapButton_Widget->BuffButton,&QPushButton::clicked,this,&MainWidget::ShowBuff);

this->setLayout(MainLayout);

}

void MainWidget::Quit(){
    this->close();
}

void MainWidget::Save(){
    Game->Me.Save();
    SystemNPC[0].Save();
    SystemTask[0].Save();
    MessageBox::about(this,"提示","保存成功");
}

void MainWidget::Help(){
    MessageBox::about(this,"帮助","Help");
}

void MainWidget::ShowItem(){
QSound::play(DATAPATH+"6112.wav");
    Item_Widget=new ItemWidget(&Game->Me);
    QPropertyAnimation *animation = new QPropertyAnimation(Item_Widget, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->geometry().left(),this->geometry().top(),Item_Widget->geometry().top(),Item_Widget->geometry().left()));
    animation->setEndValue(QRect(this->geometry().left(),this->geometry().top()+100,Item_Widget->geometry().top(),Item_Widget->geometry().left()));

    animation->start();
    Item_Widget->exec();
    delete Item_Widget;

}

void MainWidget::ShowTask(){
    Task_Widget=new TaskWidget(&Game->Me);
    QSound::play(DATAPATH+"6112.wav");
    QPropertyAnimation *animation = new QPropertyAnimation(Task_Widget, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->geometry().left(),this->geometry().top(),Task_Widget->geometry().top(),Task_Widget->geometry().left()));
    animation->setEndValue(QRect(this->geometry().left(),this->geometry().top()+100,Task_Widget->geometry().top(),Task_Widget->geometry().left()));

    animation->start();
    Task_Widget->exec();
    delete Task_Widget;
    Map_Widget->UpDateNPC(SystemMap[Game->Me.PosX][Game->Me.PosY]);
}

void MainWidget::ShowLG(){
    LG_Widget=new LGWidget(&Game->Me);
    QSound::play(DATAPATH+"6112.wav");
    QPropertyAnimation *animation = new QPropertyAnimation(LG_Widget, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->geometry().left(),this->geometry().top(),LG_Widget->geometry().top(),LG_Widget->geometry().left()));
    animation->setEndValue(QRect(this->geometry().left(),this->geometry().top()+100,LG_Widget->geometry().top(),LG_Widget->geometry().left()));

    animation->start();

    LG_Widget->exec();
    delete LG_Widget;


}

void MainWidget::ShowLH(){
    QSound::play(DATAPATH+"6112.wav");
    LH_Widget=new LHWidget(&Game->Me);
    QPropertyAnimation *animation = new QPropertyAnimation(LH_Widget, "geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->geometry().left(),this->geometry().top(),LH_Widget->geometry().top(),LH_Widget->geometry().left()));
    animation->setEndValue(QRect(this->geometry().left(),this->geometry().top()+100,LH_Widget->geometry().top(),LH_Widget->geometry().left()));

    animation->start();
    LH_Widget->exec();

    delete LH_Widget;

}
void MainWidget::ShowBuff(){
Buff_Widget=new BuffWidget(Game->Me.myBuffList);
Buff_Widget->exec();
delete Buff_Widget;
}

void MainWidget::keyPressEvent(QKeyEvent *e){

                int key = e->key();
                if (Qt::Key_S == key)
                xia();
                if (Qt::Key_W == key)
                shang();
                if (Qt::Key_A == key)
                zuo();
                if (Qt::Key_D == key)
                you();

}


void MainWidget::xia(){
    if(Game->Me.PosY==25){
        MessageBox::about(this,"提示","这已经是世界的尽头！");
    return;
}
    if(Game->CanGoTo(SystemMap[Game->Me.PosX][(Game->Me.PosY)+1])){
  Game->Me.PosY++;
  Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
    }
    else
        MessageBox::about(this,"提示","你还不能去那里！");
}
void MainWidget::shang(){
    if(Game->Me.PosY==0){
        MessageBox::about(this,"提示","这已经是世界的尽头！");
    return;
}
    if(Game->CanGoTo(SystemMap[Game->Me.PosX][(Game->Me.PosY)-1])){
    Game->Me.PosY--;
    Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
    }
    else
        MessageBox::about(this,"提示","你还不能去那里！");
}
void MainWidget::zuo(){
    if(Game->Me.PosX==0){
        MessageBox::about(this,"提示","这已经是世界的尽头！");
    return;
}
     if(Game->CanGoTo(SystemMap[(Game->Me.PosX)-1][(Game->Me.PosY)])){
    Game->Me.PosX--;
    Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
}
else
    MessageBox::about(this,"提示","你还不能去那里！");
}
void MainWidget::you(){
    if(Game->Me.PosX==25){
        MessageBox::about(this,"提示","这已经是世界的尽头！");
    return;
}
     if(Game->CanGoTo(SystemMap[(Game->Me.PosX)+1][(Game->Me.PosY)])){
    Game->Me.PosX++;
    Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
     }
     else
         MessageBox::about(this,"提示","你还不能去那里！");
}

#endif






