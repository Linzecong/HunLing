/*开始界面*/
#ifndef BEGINWIDGET
#define BEGINWIDGET
#include<QSound>
#include<QString>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include<MainWidget.h>
#include<QDialog>






class BeginWidget :public QWidget{
	public:
	QLabel Title;
	QLabel Text;
    PushButton Begin;
    PushButton Quit;
    QVBoxLayout MainLayout;
    MainWidget Main_W;
	public:
	BeginWidget();
	~BeginWidget(){}
	void Begin_Click();


};

BeginWidget::BeginWidget(){


this->setObjectName("Widget");
this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setFixedSize(QSize(1000,480));
    Title.setText("魂灵师");
    Text.setText("这就是魂灵师……");
    Begin.setText("开始游戏");
    Quit.setText("退出");
    MainLayout.addWidget(&Title);
    MainLayout.addWidget(&Text);
    MainLayout.addWidget(&Begin);
    MainLayout.addWidget(&Quit);
    this->setLayout(&MainLayout);
    connect(&Begin,&QPushButton::clicked,this,&BeginWidget::Begin_Click);

    connect(&Quit,&QPushButton::clicked,this,&BeginWidget::close);
}

void BeginWidget::Begin_Click(){
   // QSound::play(DATAPATH+"6112.wav");
     QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
     animation->setDuration(1000);
     animation->setStartValue(1);
     animation->setEndValue(0);
     animation->start();


    //Main_W.setGeometry(this->geometry());

    QPropertyAnimation *animation1 = new QPropertyAnimation(&Main_W, "windowOpacity");
     animation1->setDuration(1000);
     animation1->setStartValue(0);
     animation1->setEndValue(1);
     animation1->start();
    Main_W.show();

}

#endif
