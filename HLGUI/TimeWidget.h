#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QTime>
#include<QTimer>
class TimeWidget: public QWidget
{
	public:
	QTimer timer;
	QLabel Text;
    QVBoxLayout* MainLayout;
	public:
    void UpDate();
    TimeWidget(QWidget *parent);
    ~TimeWidget(){}
};
TimeWidget::TimeWidget(QWidget *parent): QWidget(parent)
{
 MainLayout=new QVBoxLayout;
        connect(&timer, &QTimer::timeout,this,&TimeWidget::UpDate);
        timer.start(1000);
        MainLayout->addWidget(&Text);
        this->setLayout(MainLayout);
}

 void TimeWidget::UpDate()
 {
     Text.setText(QTime::currentTime().toString());
 }
