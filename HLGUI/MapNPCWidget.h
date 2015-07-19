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
#include<FightWidget.h>
class TaskMsgWidget: public QDialog{
    public:
    RenWu* Me;//自己的任务列表
    QList<Task> tempTask;//能接受的任务列表
    QListWidget List;
    QLabel Title;
    QLabel Name;
    QLabel Des;
    QLabel MB_FMB;
    QLabel Reward;
    QPushButton Except;
    QVBoxLayout* Layout1;
    QVBoxLayout* Layout2;
    QVBoxLayout* MainLayout;

    public:
    TaskMsgWidget(RenWu* a,QList<Task> b);
    void Except_Click();
    void List_Click();
    ~TaskMsgWidget(){}
};

TaskMsgWidget::TaskMsgWidget(RenWu* a, QList<Task> b){
    Layout1=new QVBoxLayout;
    Layout2=new QVBoxLayout;
    MainLayout=new QVBoxLayout;
    tempTask=b;
    Me=a;

    for(int i=0;i<tempTask.size();i++)
        List.addItem(tempTask[i].Name);

    Title.setText("任务列表：");
    Name.setText("任务名称：");
    Des.setText("任务简介：");
    MB_FMB.setText("任务进度：");
    Reward.setText("任务奖励：<br>");
    Except.setText("接受！");
    Layout1->addWidget(&Title);
    Layout1->addWidget(&List);
    Layout2->addWidget(&Name);
    Layout2->addWidget(&Des);
    Layout2->addWidget(&MB_FMB);
    Layout2->addWidget(&Reward);
    MainLayout->addLayout(Layout1);
    MainLayout->addLayout(Layout2);
    MainLayout->addWidget(&Except);
    connect(&Except,&QPushButton::clicked,this,&Except_Click);
    connect(&List,&QListWidget::clicked,this,&List_Click);
    this->setLayout(MainLayout);
}

void TaskMsgWidget::Except_Click(){
    int a=List.currentRow();
    if(a<0)
        return;

    if(Me->ExceptTask(tempTask[a])==1){
    Except.setEnabled(false);
    QMessageBox::about(this,"提示","接受成功！");
    }
    else
        QMessageBox::about(this,"提示","Error");
    List.takeItem(a);
    tempTask.takeAt(a);
}

void TaskMsgWidget::List_Click(){
    Except.setEnabled(true);
    int a=List.currentRow();
    Task b=tempTask[a];
    Name.setText("任务名称："+b.Name);
    Des.setText("任务简介："+b.Des);
    MB_FMB.setText("任务进度："+QString::number(b.FMB)+"/"+QString::number(b.MB));
    Reward.setText("任务奖励：<br>金钱："+QString::number(b.A_Coin)+"<br>经验："+QString::number(b.A_Exp)+"<br>道具："+SystemItem[b.A_Item].Name+" * "+QString::number(b.A_Count)+"个");
}

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
        Me->UpDateTask(tempNPC.ID,KILLNPC);
        SystemNPC[tempNPC.ID].CanATK=0;
        Me->ExceptReward(Battle->Reward);
        Attack.setEnabled(false);
        SystemNPC[tempNPC.ID].TaskShow=199;
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
    Me->UpDateTask(tempNPC.ID,TALKNPC);

   QList<Message> temp=GameSystem::CanTalkList(tempNPC,Me);

   if(temp.isEmpty()==true)
       QMessageBox::about(this,"你好！","你好！");
   for(int i=0;i<temp.size();i++)
       QMessageBox::about(this,"对话中",temp[i].Msg);


}


#endif







