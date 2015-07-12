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
    LHList EnemyList;
    QLabel Head;
	QLabel Name;
	QLabel LV;
	QLabel Count;
	QPushButton Attack;
    QVBoxLayout* MainLayout;
	public:
    void Attack_Click();
    MapHLWidget(){
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
    void UpDateAll(RenWu* temp,LHList tempList);

};

void MapHLWidget::UpDateAll(RenWu* temp, LHList tempList){
    Me=temp;
    EnemyList=tempList;
    Name.setText(tempList.GetData(0).Name);
    LV.setText("等级："+QString::number(tempList.GetData(1).LV));
    Count.setText("数量："+QString::number(EnemyList.Count()));
}

void MapHLWidget::Attack_Click(){
    NPC tempNPC=GameSystem::CreateNPC(EnemyList);
    FightWidget* Battle=new FightWidget(Me,tempNPC);
  //Battle->setWindowFlags(Qt::FramelessWindowHint);
    Battle->exec();
    if(Battle->WinOrLose==1){
       Me->Exp_Now+=Battle->Reward.Exp;
       Me->Coin+=Battle->Reward.Coin;

       for(int i=0;i<Battle->Reward.Item.Count();i++)
          for(int j=0;j<Battle->Reward.Item.GetCount(i);j++)
             Me->Bag.Insert(Battle->Reward.Item.GetData(i));

    for(int i=0;i<Battle->Reward.LG.Count();i++)
       Me->LGBag.Insert(Battle->Reward.LG.GetData(i));

    for(int i=0;i<Battle->Reward.LH.Count();i++)
       Me->LHBag.Insert(Battle->Reward.LH.GetData(i));

    int UL=Me->UpdateLV();
    if(UL>0)
       QMessageBox::about(this,"提示","恭喜！你升级了！");

    this->setEnabled(false);

    }
    delete Battle;
}

#endif
