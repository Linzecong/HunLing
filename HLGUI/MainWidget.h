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
#include<DataWidget.h>
#include<TimeWidget.h>
#include<MapWidget.h>
#include<ItemWidget.h>
#include<LGWidget.h>
#include<LHWidget.h>
#include<TaskWidget.h>


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
	TimeWidget* Time_Widget;
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

};

MainWidget::MainWidget(){
    Layout1=new QVBoxLayout;
    MainLayout=new QHBoxLayout;
Game=new GameSystem;
Data_Widget=new DataWidget(&Game->Me);
Time_Widget=new TimeWidget;

MapButton_Widget=new MapButtonWidget;
Map_Widget=new MapWidget(SystemMap[Game->Me.PosX][Game->Me.PosY],&Game->Me);

Layout1->addWidget(Map_Widget);
Layout1->addWidget(Time_Widget);
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
connect(&Time_Widget->timer,&QTimer::timeout,Data_Widget,&DataWidget::UpDate);

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
    LH_Widget=new LHWidget(&Game->Me);
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
  Game->Me.PosY++;
  Map_Widget->UpDate(SystemMap[Game->Me.PosX][Game->Me.PosY]);
}
void MainWidget::shang(){}
void MainWidget::zuo(){}
void MainWidget::you(){}

#endif






