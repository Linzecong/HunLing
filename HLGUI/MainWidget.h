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
class BuffWidget: public QWidget{
    public:
    TimeWidget* Time_Widget;
    QList<Buff> List;
    QLabel Buff1;
    QLabel Buff2;
    QVBoxLayout MainLayout;
    public:
    void UpDate(QList<Buff> a);
    BuffWidget(QList<Buff> a);
    ~BuffWidget(){}

};

BuffWidget::BuffWidget(QList<Buff> a){
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
    MainLayout.addWidget(Time_Widget);
    this->setLayout(&MainLayout);

}
void BuffWidget::UpDate(QList<Buff> a){
    List=a;
    Buff1.setText("战前Buff：<br>");
    for(int i=0;i<a.size();i++)
        if(a[i].type==1&&a[i].ID!=0)
            Buff1.setText(Buff1.text()+a[i].Name+"："+a[i].Des+"<br>");

    Buff2.setText("战中Buff：<br>");
    for(int i=0;i<a.size();i++)
        if(a[i].type==2&&a[i].ID!=0)
            Buff2.setText(Buff2.text()+a[i].Name+"："+a[i].Des+"<br>");
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
    BuffWidget* myBuff;
    QVBoxLayout* MainLayout;
public:
DataWidget(RenWu* a);
~DataWidget(){}
void UpDate();
};

DataWidget::DataWidget(RenWu* a){
    this->setFixedSize(QSize(180,640));
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
    myBuff=new BuffWidget(Me->myBuffList);
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
    MainLayout->addStretch();
    MainLayout->addWidget(myBuff);

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
    myBuff->UpDate(Me->myBuffList);
}


class MapButtonWidget: public QWidget{
    public:

    QPushButton BagButton;
    QPushButton TaskButton;
    QPushButton LGButton;
    QPushButton LHButton;
    QPushButton SaveButton;
    QPushButton HelpButton;
    QPushButton QuitButton;
    QVBoxLayout* MainLayout;
    MapButtonWidget();
    ~MapButtonWidget(){}
};

MapButtonWidget::MapButtonWidget(){
    this->setFixedSize(QSize(180,640));

    MainLayout=new QVBoxLayout;
    BagButton.setText("背包");
    TaskButton.setText("任务");
    LGButton.setText("灵骨");
    LHButton.setText("灵环");
    SaveButton.setText("保存");
    HelpButton.setText("帮助");
    QuitButton.setText("退出");
    MainLayout->addWidget(&BagButton);
    MainLayout->addWidget(&TaskButton);
    MainLayout->addWidget(&LGButton);
    MainLayout->addWidget(&LHButton);
    MainLayout->addWidget(&SaveButton);
    MainLayout->addWidget(&HelpButton);
    MainLayout->addWidget(&QuitButton);


    this->setLayout(MainLayout);

}

class MainWidget:public QWidget{
	public:
    GameSystem* Game;
	DataWidget* Data_Widget;

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
    void xia();
    void shang();
    void zuo();
    void you();


protected:
    void keyPressEvent(QKeyEvent *e);
    void closeEvent(QCloseEvent *e);


};
void MainWidget::closeEvent(QCloseEvent *e){
    QMessageBox::about(this,"关闭","关闭");
    QApplication::closeAllWindows();

}


MainWidget::MainWidget(){

   //this->setFixedSize(QSize(1080,640));
    Layout1=new QVBoxLayout;
    MainLayout=new QHBoxLayout;
Game=new GameSystem;
Data_Widget=new DataWidget(&Game->Me);


MapButton_Widget=new MapButtonWidget;
Map_Widget=new MapWidget(SystemMap[Game->Me.PosX][Game->Me.PosY],&Game->Me);

Layout1->addWidget(Map_Widget);
MainLayout->addWidget(Data_Widget);
MainLayout->addLayout(Layout1);
MainLayout->addWidget(MapButton_Widget);

connect(&MapButton_Widget->QuitButton,QPushButton::clicked,this,MainWidget::Quit);
connect(&MapButton_Widget->SaveButton,QPushButton::clicked,this,MainWidget::Save);
connect(&MapButton_Widget->HelpButton,QPushButton::clicked,this,MainWidget::Help);
connect(&MapButton_Widget->BagButton,QPushButton::clicked,this,MainWidget::ShowItem);
connect(&MapButton_Widget->TaskButton,QPushButton::clicked,this,MainWidget::ShowTask);
connect(&MapButton_Widget->LGButton,QPushButton::clicked,this,MainWidget::ShowLG);
connect(&MapButton_Widget->LHButton,QPushButton::clicked,this,MainWidget::ShowLH);
connect(&Data_Widget->myBuff->Time_Widget->timer,&QTimer::timeout,Data_Widget,&DataWidget::UpDate);

this->setLayout(MainLayout);

}

void MainWidget::Quit(){
    this->close();
}

void MainWidget::Save(){
    Game->Me.Save();
    SystemNPC[0].Save();
    SystemTask[0].Save();
    QMessageBox::about(this,"提示","保存成功");
}

void MainWidget::Help(){
    QMessageBox::about(this,"帮助","Help");
}

void MainWidget::ShowItem(){
    Item_Widget=new ItemWidget(&Game->Me);
    Item_Widget->exec();
    delete Item_Widget;

}

void MainWidget::ShowTask(){
    Task_Widget=new TaskWidget(&Game->Me);
    Task_Widget->exec();
    delete Task_Widget;
    Map_Widget->UpDateNPC(SystemMap[Game->Me.PosX][Game->Me.PosY]);
}

void MainWidget::ShowLG(){
    LG_Widget=new LGWidget(&Game->Me);
    LG_Widget->exec();
    delete LG_Widget;


}

void MainWidget::ShowLH(){
    QSound::play(DATAPATH+"6112.wav");
    LH_Widget=new LHWidget(&Game->Me);
    QPropertyAnimation *animation = new QPropertyAnimation(LH_Widget, "geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(this->geometry().left(),this->geometry().top(),LH_Widget->geometry().top(),LH_Widget->geometry().left()));
    animation->setEndValue(QRect(this->geometry().left(),this->geometry().top()+100,LH_Widget->geometry().top(),LH_Widget->geometry().left()));

    animation->start();
    LH_Widget->exec();

    delete LH_Widget;

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
        QMessageBox::about(this,"提示","这已经是世界的尽头！");
    return;
}
    if(Game->CanGoTo(SystemMap[Game->Me.PosX][(Game->Me.PosY)+1])){
  Game->Me.PosY++;
  Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
    }
    else
        QMessageBox::about(this,"提示","你还不能去那里！");
}
void MainWidget::shang(){
    if(Game->Me.PosY==0){
        QMessageBox::about(this,"提示","这已经是世界的尽头！");
    return;
}
    if(Game->CanGoTo(SystemMap[Game->Me.PosX][(Game->Me.PosY)-1])){
    Game->Me.PosY--;
    Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
    }
    else
        QMessageBox::about(this,"提示","你还不能去那里！");
}
void MainWidget::zuo(){
    if(Game->Me.PosX==0){
        QMessageBox::about(this,"提示","这已经是世界的尽头！");
    return;
}
     if(Game->CanGoTo(SystemMap[(Game->Me.PosX)-1][(Game->Me.PosY)])){
    Game->Me.PosX--;
    Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
}
else
    QMessageBox::about(this,"提示","你还不能去那里！");
}
void MainWidget::you(){
    if(Game->Me.PosX==25){
        QMessageBox::about(this,"提示","这已经是世界的尽头！");
    return;
}
     if(Game->CanGoTo(SystemMap[(Game->Me.PosX)+1][(Game->Me.PosY)])){
    Game->Me.PosX++;
    Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
     }
     else
         QMessageBox::about(this,"提示","你还不能去那里！");
}

#endif






