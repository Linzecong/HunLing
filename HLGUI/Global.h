/*计时器，全局函数定义，处理各种基本东西*/

#ifndef TIMEWIDGET
#define TIMEWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QTime>
#include<QTimer>
#include<QMessageBox>
#include<QPushButton>
#include<QPainter>
#include<QPaintEvent>

//自己设计的QMessageBox
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
private:
    QPixmap map;
protected:
    void enterEvent(QEvent *e){
        //鼠标移进按钮时，发出声音
        if(this->isEnabled()==true)
            QSound::play(DATAPATH+"鼠标.wav");
        //改变图片，通过objectName判断是哪个按钮
        if(this->objectName()=="bagbutton")
                map.load("./Data/背包enter.png");
    }

    void leaveEvent(QEvent *e){
        //鼠标离开时，改变图片，通过objectName判断是哪个按钮
        if(this->objectName()=="bagbutton")
            map.load("./Data/背包.png");
    }

//    void paintEvent(QPaintEvent *e)
//    {
//         map.load("./Data/背包.png");
//        //if(map.isNull()==true)
//           // MessageBox::about(NULL,"提示","资源出错！");
//        //绘图
//       // QPainter p(this);
//       // p.drawPixmap(0,0,map);
//    }
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
