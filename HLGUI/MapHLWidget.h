/*野生魂灵窗口*/

#ifndef MAPHLWIDGET
#define MAPHLWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPushButton>
#include<QMessageBox>
#include<../HLBase/HL_LingHuan.h>
#include<../HLBase/HL_RenWu.h>
#include<../HLBase/HL_NPC.h>
#include<FightWidget.h>

class MapHLWidget: public QWidget{
	public:
    RenWu* Me;
    QList<LingHuan> EnemyList;
    QLabel Head;
	QLabel Name;
	QLabel LV;
	QLabel Count;
	QPushButton Attack;
    QVBoxLayout* MainLayout;
	public:
    void Attack_Click();
    MapHLWidget(){
        this->setFixedSize(QSize(80,200));
        this->setEnabled(false);
        MainLayout=new QVBoxLayout;
      //Head.setPixmap(QPixmap::load(""));
        LV.setText("等级：");
        Count.setText("数量：");
        Attack.setText("攻击");
        MainLayout->addWidget(&Head);
        MainLayout->addWidget(&Name);
        MainLayout->addWidget(&LV);
        MainLayout->addWidget(&Count);
        MainLayout->addWidget(&Attack);
        connect(&Attack,QPushButton::clicked,this,MapHLWidget::Attack_Click);
        this->setLayout(MainLayout);
    }
    ~MapHLWidget(){}
    void UpDateAll(RenWu* temp,QList<LingHuan> tempList);
    void Clear();

};

void MapHLWidget::Clear(){
    Name.setText("");
    LV.setText("等级：");
    Count.setText("数量：");
    this->setEnabled(false);
    this->setVisible(false);
}

void MapHLWidget::UpDateAll(RenWu* temp, QList<LingHuan> tempList){
    if(tempList.isEmpty()==true)
        return;
    this->setVisible(true);
    this->setEnabled(true);
    Me=temp;
    EnemyList=tempList;
    Name.setText(tempList[0].Name);
    LV.setText("等级："+QString::number(tempList[0].LV));
    Count.setText("数量："+QString::number(EnemyList.size()));

    if(EnemyList.isEmpty()==true){
        this->setVisible(false);
        this->setEnabled(false);
        Name.setText("");
        LV.setText("等级：");
        Count.setText("数量：");

    }
}

void MapHLWidget::Attack_Click(){
    NPC tempNPC=GameSystem::CreateNPC(EnemyList);

    if(Me->LH.isEmpty()==true||tempNPC.LH.isEmpty()==true){
        QMessageBox::about(this,"你没有灵环啊！","你该怎么打架？");
        return;
    }
    if(tempNPC.LH.isEmpty()==true){
        QMessageBox::about(this,"你的对手没有灵环啊！","别欺负人家！");
        return;
    }
    FightWidget* Battle=new FightWidget(Me,tempNPC);
  //Battle->setWindowFlags(Qt::FramelessWindowHint);
    Battle->exec();
    if(Battle->WinOrLose==1){
        Me->UpDateTask(tempNPC.ID,KILLNPC);
        SystemNPC[tempNPC.ID].CanATK=0;
        Me->ExceptReward(Battle->Reward);

    this->setEnabled(false);

    }
    delete Battle;
}

#endif
