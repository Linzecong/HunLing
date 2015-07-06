#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPushButton>
//#include"HLQTData/HL_HunLing.h"
//#include<HLDataWidget.h>
class HLWidget: public QWidget
{
	public:
	HunLing tempHL;
    QLabel Head;
	QLabel Name;
	QLabel LV;
	QLabel ATK;
	QLabel DEF;
	QLabel VIT;
	QPushButton Data;
    QVBoxLayout MainLayout;
    HLDataWidget* tempData;
	public:
    HLWidget(HunLing a);
    HLWidget(){}
	~HLWidget(){}
	void Data_Click();
    void setData(HunLing a);
	
};
HLWidget::HLWidget(HunLing a)
{
    tempHL=a;
//    Head.setPixmap(QPixmap::load(""));
    Name.setText(a.Name);
    LV.setText("等级："+QString::number(a.LV));
    ATK.setText("攻击力："+QString::number(a.ATK));
    DEF.setText("防御力："+QString::number(a.DEF));
    VIT.setText("生命力："+QString::number(a.VITNOW)+"/"+QString::number(a.VIT));
    Data.setText("详细");
    MainLayout.addWidget(&Head);
    MainLayout.addWidget(&Name);
    MainLayout.addWidget(&LV);
    MainLayout.addWidget(&ATK);
    MainLayout.addWidget(&DEF);
    MainLayout.addWidget(&VIT);
    MainLayout.addWidget(&Data);
    tempData=new HLDataWidget(a);
    this->setLayout(&MainLayout);
    connect(&Data,&QPushButton::clicked,this,&HLWidget::Data_Click);
}

void HLWidget::Data_Click()
{
    tempData->show();
}
void HLWidget::setData(HunLing a)
{
    tempHL=a;
    Name.setText(a.Name);
    LV.setText("等级："+QString::number(a.LV));
    ATK.setText("攻击力："+QString::number(a.ATK));
    DEF.setText("防御力："+QString::number(a.DEF));
    VIT.setText("生命力："+QString::number(a.VITNOW)+"/"+QString::number(a.VIT));
}
