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
    PushButton Close;
    PushButton WearButton;
    PushButton Putoff;
    QVBoxLayout* Layout1;
    QVBoxLayout* Layout2;

    QHBoxLayout* Layout3;
    QVBoxLayout* MainLayout;
    QHBoxLayout* LMainLayout;
    QVBoxLayout* LabelLayout;
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
    this->setObjectName("linggu");
    WearButton.setObjectName("function");
    Putoff.setObjectName("function");
    Close.setObjectName("close");

    Bag.setFocusPolicy(Qt::NoFocus);
    Wear.setFocusPolicy(Qt::NoFocus);
    this->setFixedSize(410,320);
    this->setWindowFlags (Qt::CustomizeWindowHint);
     Layout1=new QVBoxLayout;
     Layout2=new QVBoxLayout;
     Layout3=new QHBoxLayout;
     LabelLayout=new QVBoxLayout;
     LMainLayout=new QHBoxLayout;
     MainLayout=new QVBoxLayout;
     Me=a;
     for(int i=0;i<Me->LGBag.size();i++)
       Bag.addItem(Me->LGBag[i].Name);
     Wear.addItem(Me->LG.Head.Name);
     Wear.addItem(Me->LG.Body.Name);
     Wear.addItem(Me->LG.LHand.Name);
     Wear.addItem(Me->LG.RHand.Name);
     Wear.addItem(Me->LG.LLeg.Name);
     Wear.addItem(Me->LG.RLeg.Name);
    Close.setText("关闭");
    Close.setFixedSize(92,30);
    WearButton.setText("穿上");
    WearButton.setFixedSize(92,30);
    Putoff.setText("脱下");
    Putoff.setFixedSize(92,30);
    WearButton.setEnabled(false);
    Putoff.setEnabled(false);
    connect(&Bag,&QListWidget::clicked,this,&LGWidget::Bag_Click);
    connect(&Wear,&QListWidget::clicked,this,&LGWidget::Wear_Click);
    connect(&WearButton,&QPushButton::clicked,this,&LGWidget::WearButton_Click);
    connect(&Putoff,&QPushButton::clicked,this,&LGWidget::Putoff_Click);
    connect(&Close,&QPushButton::clicked,this,&LGWidget::close);
    Title.setText("身上灵骨：");
    Text.setText("背包灵骨：");
    Layout1->addWidget(&Title);
    Layout1->addWidget(&Wear);
    Layout2->addWidget(&Text);
    Layout2->addWidget(&Bag);
    Layout3->addLayout(Layout1);
    Layout3->addLayout(Layout2);

    LabelLayout->addWidget(&Name);
    LabelLayout->addWidget(&LV);
    LabelLayout->addWidget(&Value);
    LabelLayout->addWidget(&Strength);
    LabelLayout->addWidget(&Agility);

    LabelLayout->addWidget(&Add_Str);
    LabelLayout->addWidget(&Add_Agi);
    LabelLayout->addWidget(&WearButton);
    LabelLayout->addWidget(&Putoff);
    LabelLayout->addWidget(&Close);

    Name.setText("名字：");
    LV.setText("等级：");
    Value.setText("价值：");
    Strength.setText("所需力量：");
    Agility.setText("所需敏捷：");
    DEF_Ski.setText("防御技能：<br>");
    ATK_Ski.setText("攻击技能：<br>");
    Add_Str.setText("增加力量：");
    Add_Agi.setText("增加敏捷：");

    MainLayout->addLayout(Layout3);
    MainLayout->addWidget(&ATK_Ski);
    MainLayout->addWidget(&DEF_Ski);
    LMainLayout->addLayout(MainLayout);
    LMainLayout->addLayout(LabelLayout);

    this->setLayout(LMainLayout);
}

void LGWidget::Putoff_Click(){
    QString temp=Wear.item(Wear.currentRow())->text();
    if(temp!="空"){
       if(Me->LG.Head.Name==temp)
        Me->TakeoffLG(Me->LG.Head);
       if(Me->LG.Body.Name==temp)
        Me->TakeoffLG(Me->LG.Body);
       if(Me->LG.LHand.Name==temp)
        Me->TakeoffLG(Me->LG.LHand);
       if(Me->LG.RHand.Name==temp)
        Me->TakeoffLG(Me->LG.RHand);
       if(Me->LG.LLeg.Name==temp)
        Me->TakeoffLG(Me->LG.LLeg);
       if(Me->LG.RLeg.Name==temp)
        Me->TakeoffLG(Me->LG.RLeg);

           UpDate();
           MessageBox::about(this,"提示","成功脱下！");
    }

}

void LGWidget::WearButton_Click(){
    int a=Bag.currentRow();

    switch(Me->WearLG(Me->LGBag[a]))
    {
    case -1:
        MessageBox::about(this,"提示","请先脱下该位置的灵骨！");
        break;
    case 0:
        MessageBox::about(this,"提示","需求不足！！");
        break;
    case 1:
        MessageBox::about(this,"提示","穿着成功！");
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
    WearButton.setEnabled(false);
    Putoff.setEnabled(false);
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




