/*用于显示魂灵简要信息*/

#ifndef HLWIDGET
#define HLWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPushButton>
#include<../HLBase/HL_HunLing.h>
#include<HLDataWidget.h>

class HLWidget: public QWidget{
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
    HLWidget();
	~HLWidget(){}
	void Data_Click();
    void setData(HunLing a);
	
};
HLWidget::HLWidget(){
//  Head.setPixmap(QPixmap::load(""));
    Name.setText("名字");
    LV.setText("等级：");
    ATK.setText("攻击力：");
    DEF.setText("防御力：");
    VIT.setText("生命力：");
    LV.setText("等级：");
    ATK.setText("攻击力：");
    DEF.setText("防御力：");
    VIT.setText("生命力：");
    Data.setText("详细");
    MainLayout.addWidget(&Head);
    MainLayout.addWidget(&Name);
    MainLayout.addWidget(&LV);
    MainLayout.addWidget(&ATK);
    MainLayout.addWidget(&DEF);
    MainLayout.addWidget(&VIT);
    MainLayout.addWidget(&Data);
    this->setLayout(&MainLayout);
    connect(&Data,&QPushButton::clicked,this,&HLWidget::Data_Click);
}

void HLWidget::Data_Click(){
    tempData=new HLDataWidget(tempHL);
    tempData->exec();
    delete tempData;
}

void HLWidget::setData(HunLing a){
    tempHL=a;
    Name.setText(a.Name);
    LV.setText("等级："+QString::number(a.LV));
    ATK.setText("攻击力："+QString::number(a.ATK));
    DEF.setText("防御力："+QString::number(a.DEF));
    VIT.setText("生命力："+QString::number(a.VITNOW)+"/"+QString::number(a.VIT));
}

#endif
