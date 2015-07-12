/*战斗场景*/

#ifndef FIGHTWIDGET
#define FIGHTWIDGET

#include<QString>
#include<QWidget>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
#include<HLWidget.h>
#include<../HLBase/HL_FightSystem.h>
#include<../HLBase/HL_NPC.h>
#include<../HLBase/HL_HunLing.h>
#include<../HLBase/HL_RenWu.h>
#include<../HLBase/HL_GameSystem.h>

class ChooseDialog: public QDialog{
	public:
	int num;
    QListWidget List;
    QPushButton OK;
    QVBoxLayout* MainLayout;
    ChooseDialog(HLList a){
        for(int i=0;i<a.Count();i++)
            List.addItem(a.GetData(i).Name+"   生命值："+QString::number(a.GetData(i).VITNOW));
        MainLayout=new QVBoxLayout;
        List.setCurrentRow(0);
        MainLayout->addWidget(&List);
        OK.setText("确定");
        MainLayout->addWidget(&OK);
        this->setLayout(MainLayout);
        connect(&OK,&QPushButton::clicked,this,&ChooseDialog::OKClick);
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setWindowTitle("请选择魂灵");
    }
    ~ChooseDialog(){}
    void OKClick(){
        num=List.currentRow();
        this->close();
    }
};

class SkillChooseDialog: public QDialog{
public:
    int Energy;
    int Sour;
    HunJi Skill;
    LGList LG;
    QListWidget List;
    QPushButton OK;
    QPushButton Close;
    QVBoxLayout* MainLayout;
    SkillChooseDialog(LGList a,int b,int c){
        Skill.ID=0;
        Energy=b;
        Sour=c;
        Close.setText("关闭");
        if(a.Head.ID!=0)
        List.addItem(a.Head.Name+"   技能："+a.Head.ATK_Ski.Des+"   所需魂力："+QString::number(a.Head.ATK_Ski.Energy)+"   所需灵力："+QString::number(a.Head.ATK_Ski.Sour)+"   剩余冷却时间："+QString::number(a.Head.ATK_Ski.NowTurn));
        else
        List.addItem("此位置无灵骨");
        if(a.Body.ID!=0)
        List.addItem(a.Body.Name+"   技能："+a.Body.ATK_Ski.Des+"   所需魂力："+QString::number(a.Body.ATK_Ski.Energy)+"   所需灵力："+QString::number(a.Body.ATK_Ski.Sour)+"   剩余冷却时间："+QString::number(a.Body.ATK_Ski.NowTurn));
        else
        List.addItem("此位置无灵骨");
        if(a.LHand.ID!=0)
        List.addItem(a.LHand.Name+"   技能："+a.LHand.ATK_Ski.Des+"   所需魂力："+QString::number(a.LHand.ATK_Ski.Energy)+"   所需灵力："+QString::number(a.LHand.ATK_Ski.Sour)+"   剩余冷却时间："+QString::number(a.LHand.ATK_Ski.NowTurn));
        else
        List.addItem("此位置无灵骨");
        if(a.RHand.ID!=0)
        List.addItem(a.RHand.Name+"   技能："+a.RHand.ATK_Ski.Des+"   所需魂力："+QString::number(a.RHand.ATK_Ski.Energy)+"   所需灵力："+QString::number(a.RHand.ATK_Ski.Sour)+"   剩余冷却时间："+QString::number(a.RHand.ATK_Ski.NowTurn));
        else
        List.addItem("此位置无灵骨");
        if(a.LLeg.ID!=0)
        List.addItem(a.LLeg.Name+"   技能："+a.LLeg.ATK_Ski.Des+"   所需魂力："+QString::number(a.LLeg.ATK_Ski.Energy)+"   所需灵力："+QString::number(a.LLeg.ATK_Ski.Sour)+"   剩余冷却时间："+QString::number(a.LLeg.ATK_Ski.NowTurn));
        else
        List.addItem("此位置无灵骨");
        if(a.RLeg.ID!=0)
        List.addItem(a.RLeg.Name+"   技能："+a.RLeg.ATK_Ski.Des+"   所需魂力："+QString::number(a.RLeg.ATK_Ski.Energy)+"   所需灵力："+QString::number(a.RLeg.ATK_Ski.Sour)+"   剩余冷却时间："+QString::number(a.RLeg.ATK_Ski.NowTurn));
        else
        List.addItem("此位置无灵骨");
        OK.setText("确定");
        MainLayout=new QVBoxLayout;
        List.setCurrentRow(0);
        MainLayout->addWidget(&List);
        MainLayout->addWidget(&OK);
        MainLayout->addWidget(&Close);
        this->setLayout(MainLayout);
        connect(&OK,&QPushButton::clicked,this,&SkillChooseDialog::OKClick);
        connect(&Close,&QPushButton::clicked,this,&SkillChooseDialog::close);
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setWindowTitle("请选择灵骨技能");

    }
    ~SkillChooseDialog(){}
    void OKClick(){
        if(List.item(List.currentRow())->text()=="此位置无灵骨"){
            QMessageBox::about(this,"提示","此位置无灵骨");
            return;
        }
        switch(List.currentRow()){
        case 0:
            if(LG.Head.ATK_Ski.NowTurn>0&&LG.Head.ATK_Ski.Energy>=Energy&&LG.Head.ATK_Ski.Sour>=Sour){
                QMessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.Head.ATK_Ski;
            break;
        case 1:
            if(LG.Body.ATK_Ski.NowTurn>0&&LG.Body.ATK_Ski.Energy>=Energy&&LG.Body.ATK_Ski.Sour>=Sour){
                QMessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.Body.ATK_Ski;
            break;
        case 2:
            if(LG.LHand.ATK_Ski.NowTurn>0&&LG.LHand.ATK_Ski.Energy>=Energy&&LG.LHand.ATK_Ski.Sour>=Sour){
                QMessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.LHand.ATK_Ski;
            break;
        case 3:
            if(LG.RHand.ATK_Ski.NowTurn>0&&LG.RHand.ATK_Ski.Energy>=Energy&&LG.RHand.ATK_Ski.Sour>=Sour){
                QMessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.RHand.ATK_Ski;
            break;
        case 4:
            if(LG.LLeg.ATK_Ski.NowTurn>0&&LG.LLeg.ATK_Ski.Energy>=Energy&&LG.LLeg.ATK_Ski.Sour>=Sour){
                QMessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.LLeg.ATK_Ski;
            break;
        case 5:
            if(LG.RLeg.ATK_Ski.NowTurn>0&&LG.RLeg.ATK_Ski.Energy>=Energy&&LG.RLeg.ATK_Ski.Sour>=Sour){
                QMessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.RLeg.ATK_Ski;
            break;
        }
        this->close();

    }
};


class FightItemWidget:public QDialog{
public:
    int UseIndex;
    ItemList Item;
    QListWidget List;
    QPushButton OK;
    QPushButton Close;
    QVBoxLayout* MainLayout;
    FightItemWidget(ItemList a){
        Item=a;
        OK.setText("确定");
        UseIndex=0;
        Close.setText("关闭");
        for(int i=0;i<a.Count();i++)
        List.addItem(Item.GetData(i).Name+"作用："+Item.GetData(i).Des);

        MainLayout=new QVBoxLayout;
        List.setCurrentRow(0);
        MainLayout->addWidget(&List);
        MainLayout->addWidget(&OK);
        MainLayout->addWidget(&Close);
        this->setLayout(MainLayout);
        connect(&OK,&QPushButton::clicked,this,&FightItemWidget::OKClick);
        connect(&Close,&QPushButton::clicked,this,&FightItemWidget::close);
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setWindowTitle("请选择道具");
    }
    ~FightItemWidget(){}

    void OKClick(){
        if(Item.GetData(List.currentRow()+1).Type!=2){
            QMessageBox::about(this,"提示","此道具无法在战斗中使用 ");
            return;
        }
        UseIndex=List.currentRow();
        this->close();
    }
};

class FightWidget: public QDialog{
	public:
    FightSystem* System;
    RenWu* Me;
	NPC Enemy;
    HLList MyHL;
    HLList EnemyHL;
    QListWidget EnemyHLList;
    QListWidget MyHLList;
    QListWidget MessageList;
    HLWidget HLData;
    QLabel Energy;
    QLabel Sour;

	QLabel Title;

	QPushButton GoOn;

    QPushButton ATkButton;
    QPushButton SkillButton;
    QPushButton LGSkillButton;
    QPushButton ItemButton;
    QPushButton SkipButton;

    QHBoxLayout* Layout1;
    QHBoxLayout* Layout2;
    QVBoxLayout* MainLayout;


    DropData Reward;
    int WinOrLose;//记录0输了还是1赢了-1打平

	public:
    FightWidget(RenWu* a,NPC b);
    ~FightWidget(){}
    void Attack();//记得replace魂灵
    void Skill();
    void EnemyLGSkill(HunJi *Skill);
    void LGSkill();
    void UseItem();
    void Skip();
    void GoOn_Ckick();
    void EnemyClick();
    void MeClick();
    void SetButtonEnable(bool a){
        ATkButton.setEnabled(a);
        SkillButton.setEnabled(a);
        LGSkillButton.setEnabled(a);
        ItemButton.setEnabled(a);
        SkipButton.setEnabled(a);
    }
};

FightWidget::FightWidget(RenWu *a, NPC b){
    Me=a;
    Enemy=b;
    Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));
    WinOrLose=0;
    for (int i = 0; i < a->LH.Count(); i++)//灵环初始化成魂灵
        if(a->LH.GetData(i).ID!=0)
        MyHL.Insert(GameSystem::CreatHL(*a,a->LH.GetData(i)));

    for (int i = 0; i < b.LH.Count(); i++)
        if(b.LH.GetData(i).ID!=0)
        EnemyHL.Insert(GameSystem::CreatHL(b,b.LH.GetData(i)));


    System=new FightSystem(Me,&Enemy,&MyHL,&EnemyHL);

    for(int i=0;i<MyHL.Count();i++)
        MyHLList.addItem(MyHL.GetData(i).Name);
    for(int i=0;i<EnemyHL.Count();i++)
        EnemyHLList.addItem(EnemyHL.GetData(i).Name);

    MessageList.addItem("战斗开始！");
    HLData.setData(MyHL.GetData(1));
    Title.setText("战斗中");
    GoOn.setText("继续");
    ATkButton.setText("攻击");
    SkillButton.setText("魂灵技能");
    LGSkillButton.setText("灵骨技能");
    ItemButton.setText("背包");
    SkipButton.setText("跳过");

    ATkButton.setEnabled(false);
    SkillButton.setEnabled(false);
    LGSkillButton.setEnabled(false);
    ItemButton.setEnabled(false);
    SkipButton.setEnabled(false);

    Layout1=new QHBoxLayout;
    Layout2=new QHBoxLayout;
    MainLayout=new QVBoxLayout;

    Reward.Exp=0;
    Reward.Coin=0;

    Layout1->addWidget(&EnemyHLList);
    Layout1->addWidget(&HLData);
    Layout1->addWidget(&MyHLList);

    Layout2->addWidget(&ATkButton);
    Layout2->addWidget(&SkillButton);
    Layout2->addWidget(&LGSkillButton);
    Layout2->addWidget(&ItemButton);
    Layout2->addWidget(&SkipButton);

    MainLayout->addWidget(&Title);
    MainLayout->addLayout(Layout1);
    MainLayout->addWidget(&Energy);
    MainLayout->addWidget(&Sour);
    MainLayout->addLayout(Layout1);
    MainLayout->addWidget(&GoOn);
    MainLayout->addLayout(Layout2);
    MainLayout->addWidget(&MessageList);
    this->setLayout(MainLayout);

    connect(&ATkButton,&QPushButton::clicked,this,&FightWidget::Attack);
    connect(&SkillButton,&QPushButton::clicked,this,&FightWidget::Skill);
    connect(&LGSkillButton,&QPushButton::clicked,this,&FightWidget::LGSkill);
    connect(&ItemButton,&QPushButton::clicked,this,&FightWidget::UseItem);
    connect(&SkipButton,&QPushButton::clicked,this,&FightWidget::Skip);
    connect(&GoOn,&QPushButton::clicked,this,&FightWidget::GoOn_Ckick);




}


void FightWidget::Attack(){
    if(System->EB->type==0){
        HunLing tempEnemy=EnemyHL.GetData(System->EB->index);
        int a=GetNumber(1,MyHL.Count());
        HunLing tempMe=MyHL.GetData(a);//以后要优化
        QString msg=System->Attack(&tempEnemy,&tempMe);
        msg="（敌方）"+msg;
        QMessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);
        EnemyHL.Replace(tempEnemy,System->EB->index);
        MyHL.Replace(tempMe,a);
        GoOn.setEnabled(true);
    }
    if(System->EB->type==1){
        ChooseDialog* temp=new ChooseDialog(EnemyHL);
        temp->exec();
        HunLing tempEnemy=EnemyHL.GetData(temp->num);
        HunLing tempMe=MyHL.GetData(System->EB->index);
        QString msg=System->Attack(&tempMe,&tempEnemy);
        msg="（我方）"+msg;
        QMessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);
        EnemyHL.Replace(tempEnemy,temp->num);
        MyHL.Replace(tempMe,System->EB->index);
        delete temp;
        GoOn.setEnabled(true);
    }
    this->SetButtonEnable(false);
}

void FightWidget::Skill(){
    if(System->EB->type==0){
        HunLing tempEnemy=EnemyHL.GetData(System->EB->index);
        QString msg="";
        switch(tempEnemy.ATK_Ski.Type){
        case 0:{
        int a=GetNumber(1,MyHL.Count());
        HunLing tempMe=MyHL.GetData(a);//以后要优化
        msg=System->Skill(&tempEnemy,&tempMe,&tempEnemy.ATK_Ski);
        MyHL.Replace(tempMe,a);
        break;
        }
        case 1:{
        msg=System->Skill(&tempEnemy,&MyHL,&tempEnemy.ATK_Ski);
        break;
        }
        case 2:{
        int b=GetNumber(1,EnemyHL.Count());
        HunLing b1=EnemyHL.GetData(b);//以后要优化
        msg=System->Skill(&tempEnemy,&b1,&tempEnemy.ATK_Ski);
        EnemyHL.Replace(b1,b);
        break;
        }
        case 3:{
        msg=System->Skill(&tempEnemy,&EnemyHL,&tempEnemy.ATK_Ski);
        break;
        }
        }
        msg="（敌方）"+msg;
        QMessageBox::about(this,"提示",msg);

        Enemy.Energy-=tempEnemy.ATK_Ski.Energy;
        Enemy.Sour-=tempEnemy.ATK_Ski.Sour;

        MessageList.addItem(msg);
        EnemyHL.Replace(tempEnemy,System->EB->index);
        GoOn.setEnabled(true);
    }
    if(System->EB->type==1){
        HunLing tempMe=MyHL.GetData(System->EB->index);
        QString msg="";
        if(tempMe.ATK_Ski.NowTurn>0){
            QMessageBox::about(this,"提示","技能还有"+QString::number(tempMe.ATK_Ski.NowTurn)+"回合冷却时间！");
            return;
        }
        else{
             if(tempMe.ATK_Ski.Energy>Me->Energy||tempMe.ATK_Ski.Sour<=Me->Sour){
                 QMessageBox::about(this,"提示","魂力或灵力不足");
                 return;
             }
        }


        switch(tempMe.ATK_Ski.Type){
        case 0:{
            ChooseDialog* temp=new ChooseDialog(EnemyHL);
            temp->exec();
            HunLing tempEnemy1=EnemyHL.GetData(temp->num);
            msg=System->Skill(&tempMe,&tempEnemy1,&tempMe.ATK_Ski);
            EnemyHL.Replace(tempEnemy1,temp->num);
            delete temp;
            break;
        }
        case 1:
            msg=System->Skill(&tempMe,&EnemyHL,&tempMe.ATK_Ski);
            break;
        case 2:{
            ChooseDialog* temp1=new ChooseDialog(MyHL);
            temp1->exec();
            HunLing tempEnemy=MyHL.GetData(temp1->num);
            msg=System->Skill(&tempMe,&tempEnemy,&tempMe.ATK_Ski);
            MyHL.Replace(tempEnemy,temp1->num);
            delete temp1;
            break;
        }
        case 3:
            msg=System->Skill(&tempMe,&MyHL,&tempMe.ATK_Ski);
            break;
        }

        msg="（我方）"+msg;
        QMessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);

        Me->Energy-=tempMe.ATK_Ski.Energy;
        Me->Sour-=tempMe.ATK_Ski.Sour;

        MyHL.Replace(tempMe,System->EB->index);

        GoOn.setEnabled(true);

    }
    this->SetButtonEnable(false);
}

void FightWidget::EnemyLGSkill(HunJi* Skill){
        HunLing tempEnemy=EnemyHL.GetData(System->EB->index);
        QString msg="";
        switch(Skill->Type){
        case 0:{
        int a=GetNumber(1,MyHL.Count());
        HunLing tempMe=MyHL.GetData(a);//以后要优化
        msg=System->Skill(&tempEnemy,&tempMe,Skill);
        msg=msg+"（灵骨技能）";
        MyHL.Replace(tempMe,a);
        break;
        }
        case 1:
        msg=System->Skill(&tempEnemy,&MyHL,Skill);
        msg=msg+"（灵骨技能）";
        break;
        case 2:{
        int b=GetNumber(1,EnemyHL.Count());
        HunLing b1=EnemyHL.GetData(b);//以后要优化
        msg=System->Skill(&tempEnemy,&b1,Skill);
        msg=msg+"（灵骨技能）";
        EnemyHL.Replace(b1,b);
        break;
        }
        case 3:
        msg=System->Skill(&tempEnemy,&EnemyHL,Skill);
        msg=msg+"（灵骨技能）";
        break;
        }
        msg="（敌方）"+msg;
        QMessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);
        EnemyHL.Replace(tempEnemy,System->EB->index);

        Enemy.Energy-=tempEnemy.ATK_Ski.Energy;
        Enemy.Sour-=tempEnemy.ATK_Ski.Sour;

        GoOn.setEnabled(true);


}
void FightWidget::LGSkill(){
        HunLing tempMe=MyHL.GetData(System->EB->index);
        QString msg="";
        SkillChooseDialog* temp2=new SkillChooseDialog(Me->LG,Me->Energy,Me->Sour);
        temp2->exec();
        if(temp2->Skill.ID==0){
            delete temp2;
            return;
        }
        switch(temp2->Skill.Type){
        case 0:{
            ChooseDialog* temp=new ChooseDialog(EnemyHL);
            temp->exec();
            HunLing tempEnemy1=EnemyHL.GetData(temp->num);
            msg=System->Skill(&tempMe,&tempEnemy1,&tempMe.ATK_Ski);
            EnemyHL.Replace(tempEnemy1,temp->num);
            msg=msg+"（灵骨技能）";
            delete temp;
            break;
        }
        case 1:
            msg=System->Skill(&tempMe,&EnemyHL,&tempMe.ATK_Ski);
            msg=msg+"（灵骨技能）";
            break;
        case 2:{
            ChooseDialog* temp1=new ChooseDialog(MyHL);
            temp1->exec();
            HunLing tempEnemy=MyHL.GetData(temp1->num);
            msg=System->Skill(&tempMe,&tempEnemy,&tempMe.ATK_Ski);
            MyHL.Replace(tempEnemy,temp1->num);
            msg=msg+"（灵骨技能）";
            delete temp1;
            break;
        }
        case 3:
            msg=System->Skill(&tempMe,&MyHL,&tempMe.ATK_Ski);
            msg=msg+"（灵骨技能）";
            break;
        }

        switch(temp2->Skill.Type){
        case 0:
            Me->LG.Head.ATK_Ski=temp2->Skill;
            break;
        case 1:
            Me->LG.Body.ATK_Ski=temp2->Skill;
            break;
        case 2:
            Me->LG.RHand.ATK_Ski=temp2->Skill;
            break;
        case 3:
            Me->LG.LHand.ATK_Ski=temp2->Skill;
            break;
        case 4:
            Me->LG.RLeg.ATK_Ski=temp2->Skill;
            break;
        case 5:
            Me->LG.LLeg.ATK_Ski=temp2->Skill;
            break;
        }
        msg="（我方）"+msg;
        QMessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);

        Me->Energy-=tempMe.ATK_Ski.Energy;
        Me->Sour-=tempMe.ATK_Ski.Sour;

        MyHL.Replace(tempMe,System->EB->index);
        GoOn.setEnabled(true);
        this->SetButtonEnable(false);

}


void FightWidget::UseItem(){
    HunLing tempMe=MyHL.GetData(System->EB->index);
    QString msg="";
    FightItemWidget* tempItemList=new FightItemWidget(Me->Bag);
    tempItemList->exec();
    if(tempItemList->UseIndex==0){
        delete tempItemList;
        return;
    }

    switch(Me->Bag.GetData(tempItemList->UseIndex).ATKType){
    case 0:{
        ChooseDialog* temp=new ChooseDialog(EnemyHL);
        temp->exec();
        HunLing tempEnemy1=EnemyHL.GetData(temp->num);
        msg=System->UseItem(tempItemList->UseIndex,&tempMe,&tempEnemy1);
        EnemyHL.Replace(tempEnemy1,temp->num);
        delete temp;
        break;
    }
    case 1:
        msg=System->UseItem(tempItemList->UseIndex,&tempMe,&EnemyHL);
        break;
    case 2:{
        ChooseDialog* temp1=new ChooseDialog(MyHL);
        temp1->exec();
        HunLing tempEnemy=MyHL.GetData(temp1->num);
        msg=System->UseItem(tempItemList->UseIndex,&tempMe,&tempEnemy);
        MyHL.Replace(tempEnemy,temp1->num);
        delete temp1;
        break;
    }
    case 3:
        msg=System->UseItem(tempItemList->UseIndex,&tempMe,&MyHL);
        break;
    }

    msg="（我方）"+msg;
    QMessageBox::about(this,"提示",msg);
    MessageList.addItem(msg);
    Me->Bag.Remove(tempItemList->UseIndex);

    MyHL.Replace(tempMe,System->EB->index);
    delete tempItemList;

    GoOn.setEnabled(true);


this->SetButtonEnable(false);
}

void FightWidget::Skip(){
    QMessageBox msgBox;
    msgBox.setText("你确定要跳过吗？？？");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    if(ret==QMessageBox::Yes){
    MessageList.addItem("（敌方）"+MyHL.GetData(System->EB->index).Name+"无所事事！跳过了回合！");
    GoOn.setEnabled(true);
    this->SetButtonEnable(false);
    }
}

void FightWidget::EnemyClick(){
     int a=EnemyHLList.currentRow();
     HLData.setData(EnemyHL.GetData(a));

}

void FightWidget::MeClick(){
    int a=MyHLList.currentRow();
    HLData.setData(MyHL.GetData(a));

}

void FightWidget::GoOn_Ckick(){
     GoOn.setEnabled(false);
     System->TurnOut();
     if(System->CanGoOn()==1){
         System->EB->next();
         if(System->EB->type==0){
             if(Enemy.Des=="魂灵"){
             if(Enemy.CanUseHJList(EnemyHL.GetData(System->EB->index).ID).isEmpty()==true){
                 Attack();
             }
             else{
                 if(GetNumber(0,10)>=7)
                     Attack();
                 else
                     Skill();
             }
             }
             else{
                 if(Enemy.CanUseHJList(EnemyHL.GetData(System->EB->index).ID).isEmpty()==true){
                         Attack();
                 }
                 else{
                     if(GetNumber(0,10)>=5)
                         Attack();
                     else{
                         QList<int> temphj=Enemy.CanUseHJList(EnemyHL.GetData(System->EB->index).ID);
                         int hj=GetNumber(1,temphj.size());
                             switch(temphj[hj-1]){
                             case 0:
                                 Skill();
                                 break;
                             case 1:
                                 EnemyLGSkill(&Enemy.LG.Head.ATK_Ski);
                                 break;
                             case 2:
                                 EnemyLGSkill(&Enemy.LG.Body.ATK_Ski);
                                 break;
                             case 3:
                                 EnemyLGSkill(&Enemy.LG.LHand.ATK_Ski);
                                 break;
                             case 4:
                                 EnemyLGSkill(&Enemy.LG.RHand.ATK_Ski);
                                 break;
                             case 5:
                                 EnemyLGSkill(&Enemy.LG.LLeg.ATK_Ski);
                                 break;
                             case 6:
                                 EnemyLGSkill(&Enemy.LG.RLeg.ATK_Ski);
                                 break;
                             }

                     }

                 }
             }
             GoOn.setEnabled(false);

         }
         else{
             this->SetButtonEnable(true);

         }
     }
     Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
     Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));
     if(System->CanGoOn()==0){
         QMessageBox::about(this,"提示","你输了！");
         WinOrLose=0;
         this->close();
         return;
     }
     if(System->CanGoOn()==-1){
         QMessageBox::about(this,"提示","你获得了胜利！");
         WinOrLose=1;
         Reward=GameSystem::DropItem(EnemyHL);
         this->close();
         return;
     }
     if(System->CanGoOn()==-2){
         QMessageBox::about(this,"提示","分不出胜负！");
         WinOrLose=-1;
         return;
     }

}


#endif
















