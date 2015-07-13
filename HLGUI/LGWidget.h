/*显示灵骨*/

#ifndef LGWIDGET
#define LGWIDGET

#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
#include<../HLBase/HL_LingGu.h>
#include<../HLBase/HL_RenWu.h>

class LGWidget: public QDialog{
	public:
    RenWu* Me;
	QListWidget Bag;
	QListWidget Wear;
	QLabel Title;
	QLabel Text;
	QLabel LV;
	QLabel Name;
	QLabel Value;
	QLabel Strength;
	QLabel Agility;
	QLabel DEF_Ski;
	QLabel ATK_Ski;
    QLabel Add_Str;
    QLabel Add_Agi;
	QPushButton WearButton;
	QPushButton Putoff;
    QVBoxLayout* Layout1;
    QVBoxLayout* Layout2;
    QVBoxLayout* Layout3;
    QHBoxLayout* MainLayout;
	public:
    void Putoff_Click();
    void WearButton_Click();
    void Wear_Click();
    void Bag_Click();
    void UpDate();
    void SetData(LingGu a);
    LGWidget(RenWu* a);
    ~LGWidget(){}
	
};
LGWidget::LGWidget(RenWu* a){
     Layout1=new QVBoxLayout;
     Layout2=new QVBoxLayout;
     Layout3=new QVBoxLayout;
     MainLayout=new QHBoxLayout;
     Me=a;
     for(int i=0;i<Me->LGBag.size();i++)
       Bag.addItem(Me->LGBag[i].Name);
     Wear.addItem(Me->LG.Head.Name);
     Wear.addItem(Me->LG.Body.Name);
     Wear.addItem(Me->LG.LHand.Name);
     Wear.addItem(Me->LG.RHand.Name);
     Wear.addItem(Me->LG.LLeg.Name);
     Wear.addItem(Me->LG.RLeg.Name);

     WearButton.setText("穿上");
    Putoff.setText("脱下");
    WearButton.setEnabled(false);
    Putoff.setEnabled(false);
    connect(&Bag,&QListWidget::clicked,this,&LGWidget::Bag_Click);
    connect(&Wear,&QListWidget::clicked,this,&LGWidget::Wear_Click);
    connect(&WearButton,&QPushButton::clicked,this,&LGWidget::WearButton_Click);
    connect(&Putoff,&QPushButton::clicked,this,&LGWidget::Putoff_Click);
    Title.setText("身上灵骨：");
    Text.setText("背包灵骨：");
    Layout1->addWidget(&Title);
    Layout1->addWidget(&Wear);
    Layout2->addWidget(&Text);
    Layout2->addWidget(&Bag);

    Layout3->addWidget(&Name);
    Layout3->addWidget(&LV);
    Layout3->addWidget(&Value);
    Layout3->addWidget(&Strength);
    Layout3->addWidget(&Agility);
    Layout3->addWidget(&DEF_Ski);
    Layout3->addWidget(&ATK_Ski);
    Layout3->addWidget(&Add_Str);
    Layout3->addWidget(&Add_Agi);
    Layout3->addWidget(&WearButton);
    Layout3->addWidget(&Putoff);
    Name.setText("名字：");
    LV.setText("等级：");
    Value.setText("价值：");
    Strength.setText("所需力量：");
    Agility.setText("所需敏捷：");
    DEF_Ski.setText("防御技能：<br>");
    ATK_Ski.setText("攻击技能：<br>");
    Add_Str.setText("增加力量：");
    Add_Agi.setText("增加敏捷：");

    MainLayout->addLayout(Layout1);
    MainLayout->addLayout(Layout2);
    MainLayout->addLayout(Layout3);
    this->setLayout(MainLayout);
}

void LGWidget::Putoff_Click(){
    QString temp=Wear.item(Wear.currentRow())->text();
    if(temp!="空"){
       if(Me->LG.Head.Name==temp){
        Me->LGBag.append(Me->LG.Head);
        Me->TakeoffLG(1);
       }
       if(Me->LG.Body.Name==temp){
        Me->LGBag.append(Me->LG.Body);
        Me->TakeoffLG(2);
       }
       if(Me->LG.LHand.Name==temp){
        Me->LGBag.append(Me->LG.LHand);
        Me->TakeoffLG(3);
       }
       if(Me->LG.RHand.Name==temp){
        Me->LGBag.append(Me->LG.RHand);
        Me->TakeoffLG(4);
       }
       if(Me->LG.LLeg.Name==temp){
        Me->LGBag.append(Me->LG.LLeg);
        Me->TakeoffLG(5);
       }
       if(Me->LG.RLeg.Name==temp){
        Me->LGBag.append(Me->LG.RLeg);
        Me->TakeoffLG(6);
       }
           UpDate();
    }

}

void LGWidget::WearButton_Click(){
    int a=Bag.currentRow();

    switch(Me->WearLG(Me->LGBag[a]))
    {
    case -1:
        QMessageBox::about(this,"提示","请先脱下该位置的灵骨！");
        break;
    case 0:
        QMessageBox::about(this,"提示","需求不足！！");
        break;
    case 1:
        QMessageBox::about(this,"提示","穿着成功！");
        Me->LGBag.removeAt(a);
        break;

    }
    UpDate();
}

void LGWidget::Wear_Click(){
    WearButton.setEnabled(false);

    QString temp=Wear.item(Wear.currentRow())->text();
    if(temp!="空"){
        Putoff.setEnabled(true);
    if(Me->LG.Head.Name==temp)
      SetData(Me->LG.Head);
    if(Me->LG.Body.Name==temp)
    SetData(Me->LG.Body);
    if(Me->LG.LHand.Name==temp)
   SetData(Me->LG.LHand);
    if(Me->LG.RHand.Name==temp)
   SetData(Me->LG.RHand);
    if(Me->LG.LLeg.Name==temp)
    SetData(Me->LG.LLeg);
    if(Me->LG.RLeg.Name==temp)
    SetData(Me->LG.RLeg);
        }
}

void LGWidget::Bag_Click(){
    WearButton.setEnabled(true);
    Putoff.setEnabled(false);
    int a=Bag.currentRow();
    SetData(Me->LGBag[a]);
}

void LGWidget::UpDate(){
    Wear.clear();
    Bag.clear();
    for(int i=0;i<Me->LGBag.size();i++)
      Bag.addItem(Me->LGBag[i].Name);
    Wear.addItem(Me->LG.Head.Name);
    Wear.addItem(Me->LG.Body.Name);
    Wear.addItem(Me->LG.LHand.Name);
    Wear.addItem(Me->LG.RHand.Name);
    Wear.addItem(Me->LG.LLeg.Name);
    Wear.addItem(Me->LG.RLeg.Name);
}

void LGWidget::SetData(LingGu a){
    Name.setText("名字："+a.Name);
    LV.setText("等级："+QString::number(a.LV));
    Value.setText("价值："+QString::number(a.Value));
    Strength.setText("所需力量："+QString::number(a.Strength));
    Agility.setText("所需敏捷："+QString::number(a.Agility));
    DEF_Ski.setText("防御技能：<br>"+SystemBuff[a.DEF_Ski].Name+"："+SystemBuff[a.DEF_Ski].Des+"<br>");
    ATK_Ski.setText("攻击技能：<br>"+a.ATK_Ski.Name+"："+a.ATK_Ski.Des+"<br>所需魂力："+QString::number(a.ATK_Ski.Energy)+"<br>所需灵力："+QString::number(a.ATK_Ski.Sour)+"<br>冷却时间："+QString::number(a.ATK_Ski.Turn));
    Add_Str.setText("增加力量："+QString::number(a.Add_Str));
    Add_Agi.setText("增加敏捷："+QString::number(a.Add_Agi));
}


#endif




