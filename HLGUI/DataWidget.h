/*用于显示人物信息*/
#ifndef DATAWIDGET
#define DATAWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include<../HLBase/HL_RenWu.h>
#include<../HLBase/HL_HunJi.h>


class BuffWidget: public QWidget{
    public:
    QList<Buff> List;
    QLabel Buff1;
    QLabel Buff2;
    QVBoxLayout MainLayout;
    public:
    void UpDate(QList<Buff> a);
    BuffWidget(QList<Buff> a);
    ~BuffWidget(){}

};

BuffWidget::BuffWidget(QList<Buff> a){
    List=a;
    Buff1.setText("战前Buff：<br>");
    for(int i=0;i<a.size();i++)
        if(a[i].type==1&&a[i].ID!=0)
            Buff1.setText(Buff1.text()+a[i].Name+"："+a[i].Des+"<br>");

    Buff2.setText("战中Buff：<br>");
    for(int i=0;i<a.size();i++)
        if(a[i].type==2&&a[i].ID!=0)
            Buff1.setText(Buff1.text()+a[i].Name+"："+a[i].Des+"<br>");
    MainLayout.addWidget(&Buff1);
    MainLayout.addWidget(&Buff2);
    this->setLayout(&MainLayout);

}
void BuffWidget::UpDate(QList<Buff> a){
    List=a;
    Buff1.setText("战前Buff：<br>");
    for(int i=0;i<a.size();i++)
        if(a[i].type==1&&a[i].ID!=0)
            Buff1.setText(Buff1.text()+a[i].Name+"："+a[i].Des+"<br>");
    Buff2.setText("战中Buff：<br>");
    for(int i=0;i<a.size();i++)
        if(a[i].type==2&&a[i].ID!=0)
            Buff1.setText(Buff1.text()+a[i].Name+"："+a[i].Des+"<br>");
}

class DataWidget: public QWidget{
	public:
    RenWu* Me;
	QLabel Title;
    QLabel Name;
	QLabel Level;
	QLabel Exp;
	QLabel LingHuan;//颜色
	QLabel Strength;
	QLabel Agility;
	QLabel Vitality;
	QLabel Energy;
	QLabel Sour;
    BuffWidget* myBuff;
    QVBoxLayout* MainLayout;
public:
DataWidget(RenWu* a);
~DataWidget(){}
void UpDate();
};

DataWidget::DataWidget(RenWu* a){
     MainLayout=new QVBoxLayout;
    Me=a;
    Title.setText("人物信息：");
    Name.setText("名字："+Me->Name);
    Level.setText("等级："+QString::number(Me->LV)+"级");
    Exp.setText("经验："+QString::number(Me->Exp_Now)+"/"+QString::number(Me->Exp_Need));
    for(int i=0;i<Me->LH.size();i++)
    LingHuan.setText(LingHuan.text()+Me->LH[i].Col);
    LingHuan.setText("灵环："+LingHuan.text());
    Strength.setText("力量："+QString::number(Me->Strength)+"("+QString::number(Me->Ori_Strength)+")");
    Agility.setText("敏捷："+QString::number(Me->Agility)+"("+QString::number(Me->Ori_Agility)+")");
    Vitality.setText("体力："+QString::number(Me->Vitality)+"("+QString::number(Me->Ori_Vitality)+")");
    Energy.setText("魂力："+QString::number(Me->Energy)+"("+QString::number(Me->Ori_Energy)+")");
    Sour.setText("灵力："+QString::number(Me->Sour)+"("+QString::number(Me->Ori_Sour)+")");
    myBuff=new BuffWidget(Me->myBuffList);
    MainLayout->addWidget(&Title);
    MainLayout->addWidget(&Name);
    MainLayout->addWidget(&Level);
    MainLayout->addWidget(&Exp);
    MainLayout->addWidget(&LingHuan);
    MainLayout->addWidget(&Strength);
    MainLayout->addWidget(&Agility);
    MainLayout->addWidget(&Vitality);
    MainLayout->addWidget(&Energy);
    MainLayout->addWidget(&Sour);
    MainLayout->addWidget(myBuff);
    this->setLayout(MainLayout);

}

void DataWidget::UpDate(){
    Title.setText("人物信息：");
    Name.setText("名字："+Me->Name);
    Level.setText("等级："+QString::number(Me->LV)+"级");
    Exp.setText("经验："+QString::number(Me->Exp_Now)+"/"+QString::number(Me->Exp_Need));
    LingHuan.setText("");
    for(int i=0;i<Me->LH.size();i++)
    LingHuan.setText(LingHuan.text()+Me->LH[i].Col);
    LingHuan.setText("灵环："+LingHuan.text());
    Strength.setText("力量："+QString::number(Me->Strength)+"("+QString::number(Me->Ori_Strength)+")");
    Agility.setText("敏捷："+QString::number(Me->Agility)+"("+QString::number(Me->Ori_Agility)+")");
    Vitality.setText("体力："+QString::number(Me->Vitality)+"("+QString::number(Me->Ori_Vitality)+")");
    Energy.setText("魂力："+QString::number(Me->Energy)+"("+QString::number(Me->Ori_Energy)+")");
    Sour.setText("灵力："+QString::number(Me->Sour)+"("+QString::number(Me->Ori_Sour)+")");
    Me->UpdateBuff();
    myBuff->UpDate(Me->myBuffList);
}

#endif






