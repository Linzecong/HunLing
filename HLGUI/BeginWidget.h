/*开始界面*/
#ifndef BEGINWIDGET
#define BEGINWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include<MainWidget.h>

class BeginWidget :public QWidget{
	public:
	QLabel Title;
	QLabel Text;
	QPushButton Begin;
	QPushButton Quit;
    QVBoxLayout MainLayout;
    MainWidget Main_W;
	public:
	BeginWidget();
	~BeginWidget(){}
	void Begin_Click();
};

BeginWidget::BeginWidget(){
    this->setFixedSize(QSize(640,480));
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
    Main_W.show();
}

#endif
