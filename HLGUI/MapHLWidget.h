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
        MainLayout=new QVBoxLayout;
      //Head.setPixmap(QPixmap::load(""));
        Name.setText("空");
        LV.setText("等级：0");
        Count.setText("数量：0");
        Attack.setText("攻击");
        MainLayout->addWidget(&Head);
        MainLayout->addWidget(&Name);
        MainLayout->addWidget(&LV);
        MainLayout->addWidget(&Count);
        MainLayout->addWidget(&Attack);
        connect(&Attack,QPushButton::clicked,this,MapHLWidget::Attack_Click);
        this->setLayout(MainLayout);
        this->setEnabled(false);
    }
    ~MapHLWidget(){}
    void UpDateAll(RenWu* temp,QList<LingHuan> tempList);

};

void MapHLWidget::UpDateAll(RenWu* temp, QList<LingHuan> tempList){
    this->setEnabled(true);
    Me=temp;
    EnemyList=tempList;
    Name.setText(tempList[0].Name);
    LV.setText("等级："+QString::number(tempList[0].LV));
    Count.setText("数量："+QString::number(EnemyList.size()));

    if(EnemyList[0].Name=="空"){
        this->setEnabled(false);
        LV.setText("等级：0");
        Count.setText("数量：0");

    }
}

void MapHLWidget::Attack_Click(){
    NPC tempNPC=GameSystem::CreateNPC(EnemyList);
    FightWidget* Battle=new FightWidget(Me,tempNPC);
  //Battle->setWindowFlags(Qt::FramelessWindowHint);
    Battle->exec();
    if(Battle->WinOrLose==1){
       Me->Exp_Now+=Battle->Reward.Exp;
       Me->Coin+=Battle->Reward.Coin;

       for(int i=0;i<Battle->Reward.Item.size();i++){
           int stop=0;
          for(int j=0;j<Me->Bag.size();j++)
             if(Me->Bag[j].ID==Battle->Reward.Item[i].ID){
                 Me->Bag[j].Count++;
                 stop=1;
                 break;
             }
          if(stop==0){
          Me->Bag.append(Battle->Reward.Item[i]);
          Me->Bag.last().Count=1;
          }
       }
    for(int i=0;i<Battle->Reward.LG.size();i++)
       Me->LGBag.append(Battle->Reward.LG[i]);

    for(int i=0;i<Battle->Reward.LH.size();i++)
       Me->LHBag.append(Battle->Reward.LH[i]);

    int UL=Me->UpdateLV();
    if(UL>0)
       QMessageBox::about(this,"提示","恭喜！你升级了！");

    this->setEnabled(false);

    }
    delete Battle;
}

#endif
