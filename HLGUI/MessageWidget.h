#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>

class MessageWidget: public QWidget
{
	public:
    QLabel Text;
    QVBoxLayout* MainLayout;
	public:
    MessageWidget(QString a);
	~MessageWidget(){}

	
};

MessageWidget::MessageWidget(QString a)
{
   MainLayout=new QVBoxLayout;
    Text.setText(a);
    MainLayout->addWidget(&Text);
    this->setLayout(MainLayout);
}
