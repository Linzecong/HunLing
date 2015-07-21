/*时间，用于显示当前时间*/

#ifndef TIMEWIDGET
#define TIMEWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QTime>
#include<QTimer>
#include<QMessageBox>





class MessageBox :public QDialog{
public:
    static void about(QWidget* a,QString title,QString text){
        QMessageBox msgBox;
        msgBox.setWindowTitle(title);
        msgBox.setText(text);
        msgBox.setStandardButtons(QMessageBox::Yes);
        msgBox.buttons()[0]->setFixedSize(100,30);
        msgBox.buttons()[0]->setText("OK");
        msgBox.exec();
    }

};

class PushButton:public QPushButton{

public:
    void enterEvent(QEvent *e){
        if(this->isEnabled()==true)
        QSound::play(DATAPATH+"鼠标.wav");
    }
};

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
