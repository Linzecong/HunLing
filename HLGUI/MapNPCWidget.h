/*NPC窗口*/

#ifndef MAPNPCWIDGET
#define MAPNPCWIDGET

#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPushButton>
#include<QMessageBox>
#include<../HLBase/HL_NPC.h>
#include<../HLBase/HL_RenWu.h>
#include<TaskMsgWidget.h>
#include<FightWidget.h>

class MapNPCWidget: public QWidget{
	public:
	NPC tempNPC;
    RenWu* Me;
    QLabel Head;
	QLabel Name;
	QLabel LV;
	QPushButton Task;
	QPushButton Talk;
    QPushButton Attack;//注意设置不能再显示
    QVBoxLayout* MainLayout;
    TaskMsgWidget* TaskMsg;

	public:
    void Attack_Click();
    void Task_Click();
    void Talk_Click();
    MapNPCWidget(){
        MainLayout=new QVBoxLayout;
      //Head.setPixmap(QPixmap::load(""));
        LV.setText("等级：");
        Task.setText("任务");
        Talk.setText("交谈");
        Attack.setText("攻击");
        MainLayout->addWidget(&Head);
        MainLayout->addWidget(&Name);
        MainLayout->addWidget(&LV);
        MainLayout->addWidget(&Task);
        MainLayout->addWidget(&Talk);
        MainLayout->addWidget(&Attack);
        this->setLayout(MainLayout);
        this->setEnabled(false);
        connect(&Attack,QPushButton::clicked,this,MapNPCWidget::Attack_Click);
        connect(&Task,QPushButton::clicked,this,MapNPCWidget::Task_Click);
        connect(&Talk,QPushButton::clicked,this,MapNPCWidget::Talk_Click);
    }
    ~MapNPCWidget(){}
    void UpDateAll(RenWu* temp,NPC a);
    void Clear();
	
	
};

void MapNPCWidget::Clear(){
    Name.setText("");
    LV.setText("等级：");
    Task.setText("任务");
    Talk.setText("交谈");
    Attack.setText("攻击");
    this->setEnabled(false);
}

void MapNPCWidget::UpDateAll(RenWu* temp,NPC a){
    this->setEnabled(true);
    Attack.setEnabled(true);

    Me=temp;
    tempNPC=a;
  //Head.setPixmap(QPixmap::load(""));
    Name.setText(tempNPC.Name);
    LV.setText("等级："+QString::number(tempNPC.LV));
    Task.setText("任务");
    Talk.setText("交谈");
    if(tempNPC.CanATK==0)
        Attack.setEnabled(false);
    Attack.setText("攻击");

    if(tempNPC.Name=="空")
        this->setEnabled(false);
}

void MapNPCWidget::Attack_Click(){
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
                if(Me->myTaskList[i].NKillNPC==tempNPC.ID){
                    Me->myTaskList[i].FMB++;
                    SystemNPC[tempNPC.ID].CanATK=0;
                }

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

    Attack.setEnabled(false);

    }
    delete Battle;
}

void MapNPCWidget::Task_Click(){
    TaskMsg=new TaskMsgWidget(Me,GameSystem::CanExceptList(tempNPC,Me));
    if(TaskMsg->tempTask.isEmpty()==true){
        QMessageBox::about(this,"没有任务","没有任务");
        return;
    }
    TaskMsg->exec();
    delete TaskMsg;

}

void MapNPCWidget::Talk_Click(){
    for(int i=0;i<Me->myTaskList.size();i++)//完成任务
            if(Me->myTaskList[i].NTalkNPC==tempNPC.ID)
                Me->myTaskList[i].FMB++;

   QList<Message> temp=GameSystem::CanTalkList(tempNPC,Me);
   if(temp.isEmpty()==true)
       QMessageBox::about(this,"你好！","你好！");
   for(int i=0;i<temp.size();i++)
       QMessageBox::about(this,"对话中",temp[i].Msg);


}


#endif







