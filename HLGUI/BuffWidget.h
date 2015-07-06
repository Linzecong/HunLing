#include<QString>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>

class BuffWidget: public QWidget
{
	public:
	BuffList List;
    QLabel Buff1;
    QLabel Buff2;
    QVBoxLayout MainLayout;
	public:
    void UpDate(BuffList a);
    BuffWidget(BuffList a);
	~BuffWidget(){}
	
};

BuffWidget::BuffWidget(BuffList a)
{
    List=a;
    Buff1.setText("战前Buff：<br>");
    for(int i=1;i<=a.Count();i++)
        if(a.GetData(i).type==1)
            Buff1.setText(Buff1.text()+a.GetData(i).Name+"："+a.GetData(i).Des+"<br>");
    Buff2.setText("战中Buff：<br>");
    for(int i=1;i<=a.Count();i++)
        if(a.GetData(i).type==2)
            Buff1.setText(Buff1.text()+a.GetData(i).Name+"："+a.GetData(i).Des+"<br>");
    MainLayout.addWidget(&Buff1);
    MainLayout.addWidget(&Buff2);
    this->setLayout(&MainLayout);

}
void BuffWidget::UpDate(BuffList a)
{
    List=a;
    Buff1.setText("战前Buff：<br>");
    for(int i=1;i<=a.Count();i++)
        if(a.GetData(i).type==1)
            Buff1.setText(Buff1.text()+a.GetData(i).Name+"："+a.GetData(i).Des+"<br>");
    Buff2.setText("战中Buff：<br>");
    for(int i=1;i<=a.Count();i++)
        if(a.GetData(i).type==2)
            Buff1.setText(Buff1.text()+a.GetData(i).Name+"："+a.GetData(i).Des+"<br>");
}
