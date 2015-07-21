/*显示灵环*/

#ifndef LHWIDGET
#define LHWIDGET

#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
#include<../HLBase/HL_LingHuan.h>
#include<../HLBase/HL_RenWu.h>


class LHWidget: public QDialog{
	public:
    RenWu* Me;
    LingHuan tempLH;
	QListWidget Bag;
	QListWidget Wear;
	QLabel Title;
	QLabel Text;
	QLabel LV;
	QLabel Name;
	QLabel Des;
	QLabel Col;
	QLabel Value;
	QLabel Strength;
	QLabel Agility;
QPushButton Close;
    QPushButton Data;
    HLDataWidget* HLData;
    QVBoxLayout* Layout1;
    QVBoxLayout* Layout2;

    QHBoxLayout* Layout3;
    QVBoxLayout* MainLayout;
    QHBoxLayout* LMainLayout;
    QVBoxLayout* LabelLayout;
	QPushButton WearButton;
	QPushButton Putoff;	
	public:
    LHWidget(RenWu* a);
    void Data_Click();
    void Putoff_Click();
    void WearButton_Click();
    void Wear_Click();
    void Bag_Click();
    void UpDate();
    void SetData(LingHuan a);
	~LHWidget(){}

	
};


LHWidget::LHWidget(RenWu* a){
    Bag.setFocusPolicy(Qt::NoFocus);
    Wear.setFocusPolicy(Qt::NoFocus);
    this->setObjectName("Widget");
    this->setFixedSize(410,320);
this->setWindowFlags (Qt::CustomizeWindowHint);

    Layout1=new QVBoxLayout;
    Layout2=new QVBoxLayout;
    Layout3=new QHBoxLayout;
    LabelLayout=new QVBoxLayout;
    LMainLayout=new QHBoxLayout;
    MainLayout=new QVBoxLayout;
    Me=a;
    for(int i=0;i<Me->LHBag.size();i++)
      Bag.addItem(Me->LHBag[i].Name);
    for(int i=0;i<Me->LH.size();i++)
      Wear.addItem(Me->LH[i].Name);
    WearButton.setText("带上");
    Putoff.setText("取下");
    WearButton.setFixedSize(92,30);
    Putoff.setFixedSize(92,30);
    WearButton.setEnabled(false);
    Putoff.setEnabled(false);
    connect(&Bag,&QListWidget::clicked,this,&LHWidget::Bag_Click);
    connect(&Wear,&QListWidget::clicked,this,&LHWidget::Wear_Click);
    connect(&WearButton,&QPushButton::clicked,this,&LHWidget::WearButton_Click);
    connect(&Putoff,&QPushButton::clicked,this,&LHWidget::Putoff_Click);
    connect(&Data,&QPushButton::clicked,this,&LHWidget::Data_Click);
    connect(&Close,&QPushButton::clicked,this,&LHWidget::close);
    Title.setText("身上灵环：");
    Text.setText("背包灵环：");
    Data.setText("详细");
    Data.setFixedSize(92,30);
    Close.setText("关闭");
    Close.setFixedSize(92,30);
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
    LabelLayout->addWidget(&Col);
    LabelLayout->addWidget(&WearButton);
    LabelLayout->addWidget(&Putoff);
    LabelLayout->addWidget(&Data);
    LabelLayout->addWidget(&Close);

    Name.setText("名字：");
    Des.setText("介绍：");

    Des.setWordWrap(true);
    Des.setAlignment(Qt::AlignTop);

    LV.setText("等级：");
    Col.setText("品质：");
    Strength.setText("所需力量：");
    Agility.setText("所需敏捷：");
    Value.setText("价值：");
    MainLayout->addLayout(Layout3);
    MainLayout->addWidget(&Des);
    LMainLayout->addLayout(MainLayout);
    LMainLayout->addLayout(LabelLayout);
    this->setLayout(LMainLayout);

}

void LHWidget::Data_Click(){
    HLData=new HLDataWidget(GameSystem::CreatHL(*Me,tempLH));
    HLData->exec();
    delete HLData;
}

void LHWidget::Putoff_Click(){
    Me->TakeoffLH(tempLH);
    QMessageBox::about(this,"成功！","成功脱下！");
    UpDate();
}

void LHWidget::WearButton_Click(){
    switch(Me->WearLH(tempLH))
    {
    case -1:
        QMessageBox::about(this,"提示","等级不足！");
        break;
    case 0:
        QMessageBox::about(this,"提示","需求不足！！");
        break;
    case 2:
        QMessageBox::about(this,"提示","不能携带相同的灵环！");
        break;
    case 1:
        QMessageBox::about(this,"提示","成功！");
        Me->LHBag.removeAt(Bag.currentRow());
        break;

    }
    UpDate();
}

void LHWidget::Wear_Click(){
    WearButton.setEnabled(false);
    Putoff.setEnabled(true);
    int a=Wear.currentRow();
    tempLH=Me->LH[a];
    SetData(tempLH);
}

void LHWidget::Bag_Click(){
    WearButton.setEnabled(true);
    Putoff.setEnabled(false);
    int a=Bag.currentRow();
    tempLH=Me->LHBag[a];
    SetData(tempLH);
}

void LHWidget::SetData(LingHuan a){
    tempLH=a;
    Name.setText("名字："+a.Name);
    Des.setText("介绍："+a.Des);
    LV.setText("等级："+QString::number(a.LV));
    Col.setText("品质："+a.Col);
    Strength.setText("所需力量："+QString::number(a.Strength));
    Agility.setText("所需敏捷："+QString::number(a.Agility));
    Value.setText("价值："+QString::number(a.Value));
}

void LHWidget::UpDate(){
    Wear.clear();
    Bag.clear();
    for(int i=0;i<Me->LHBag.size();i++)
      Bag.addItem(Me->LHBag[i].Name);
    for(int i=0;i<Me->LH.size();i++)
      Wear.addItem(Me->LH[i].Name);
}

#endif



