/*时间，用于显示当前时间*/

#ifndef TIMEWIDGET
#define TIMEWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QTime>
#include<QTimer>

class TimeWidget: public QWidget{
	public:
	QTimer timer;
	QLabel Text;
    QVBoxLayout* MainLayout;
	public:
    void UpDate();
    TimeWidget();
    ~TimeWidget(){}
};

TimeWidget::TimeWidget(){
        MainLayout=new QVBoxLayout;
        connect(&timer, &QTimer::timeout,this,&TimeWidget::UpDate);
        timer.start(1000);//每一秒更新一次
        MainLayout->addWidget(&Text);
        this->setLayout(MainLayout);
}

 void TimeWidget::UpDate(){
     Text.setText(QTime::currentTime().toString());
}

#endif
