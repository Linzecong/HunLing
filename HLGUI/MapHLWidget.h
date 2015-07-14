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
}

void MapHLWidget::UpDateAll(RenWu* temp, QList<LingHuan> tempList){
    if(tempList.isEmpty()==true)
        return;
    this->setEnabled(true);
    Me=temp;
    EnemyList=tempList;
    Name.setText(tempList[0].Name);
    LV.setText("等级："+QString::number(tempList[0].LV));
    Count.setText("数量："+QString::number(EnemyList.size()));

    if(EnemyList.isEmpty()==true){
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

        for(int i=0;i<Me->myTaskList.size();i++)//完成任务
            for(int j=0;j<EnemyList.size();j++)
                if(Me->myTaskList[i].NKillHL==EnemyList[j].ID)
                    Me->myTaskList[i].FMB++;

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
