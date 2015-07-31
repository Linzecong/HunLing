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
#include<../HLBase/HL_FightSystem.h>
#include<../HLBase/HL_NPC.h>
#include<../HLBase/HL_HunLing.h>
#include<../HLBase/HL_RenWu.h>
#include<../HLBase/HL_GameSystem.h>

class HLDataWidget: public QDialog{
public:
    HunLing tempHL;
    QLabel Name;
    QLabel Des;
    QLabel Strength;
    QLabel Agility;
    QLabel ATK;
    QLabel DEF;
    QLabel VIT;
    QLabel K_Fire;
    QLabel K_Ice;
    QLabel K_Lig;
    QLabel K_Tox;
    QLabel G_Fire;
    QLabel G_Ice;
    QLabel G_Lig;
    QLabel G_Tox;
    QLabel DEF_Ski;
    QLabel ATK_Ski;
    QVBoxLayout MainLayout;
public:
    void setData(HunLing a);
    HLDataWidget(HunLing a);
    ~HLDataWidget(){}
};

HLDataWidget::HLDataWidget(HunLing a){
    this->setWindowTitle("详细参数");
    this->setObjectName("fight");
    tempHL=a;
    Name.setText("名字："+a.Name);
    Des.setText("介绍："+a.Des);
    Strength.setText("力量："+QString::number(a.Strength));
    Agility.setText("敏捷："+QString::number(a.Agility));
    ATK.setText("攻击力："+QString::number(a.ATK));
    DEF.setText("防御力："+QString::number(a.DEF));
    VIT.setText("生命力："+QString::number(a.VIT));
    K_Fire.setText("火抗："+QString::number(a.K_Fire));
    K_Ice.setText("冰抗："+QString::number(a.K_Ice));
    K_Lig.setText("电抗："+QString::number(a.K_Lig));
    K_Tox.setText("毒抗："+QString::number(a.K_Tox));
    G_Fire.setText("火焰伤害："+QString::number(a.G_Fire));
    G_Ice.setText("冰冷伤害："+QString::number(a.G_Ice));
    G_Lig.setText("电击伤害："+QString::number(a.G_Lig));
    G_Tox.setText("毒素伤害："+QString::number(a.G_Tox));
    ATK_Ski.setText("攻击技能：<br>"+SystemHJ[a.ATK_Ski.ID].Name+"："+SystemHJ[a.ATK_Ski.ID].Des);
    DEF_Ski.setText("防御技能：<br>"+SystemBuff[a.DEF_Ski].Name+"："+SystemBuff[a.DEF_Ski].Des);
    MainLayout.addWidget(&Name);
    MainLayout.addWidget(&Des);
    MainLayout.addWidget(&Strength);
    MainLayout.addWidget(&Agility);
    MainLayout.addWidget(&ATK);
    MainLayout.addWidget(&DEF);
    MainLayout.addWidget(&VIT);
    MainLayout.addWidget(&K_Fire);
    MainLayout.addWidget(&K_Ice);
    MainLayout.addWidget(&K_Lig);
    MainLayout.addWidget(&K_Tox);
    MainLayout.addWidget(&G_Fire);
    MainLayout.addWidget(&G_Ice);
    MainLayout.addWidget(&G_Lig);
    MainLayout.addWidget(&G_Tox);
    MainLayout.addWidget(&ATK_Ski);
    MainLayout.addWidget(&DEF_Ski);
    this->setLayout(&MainLayout);
}

void HLDataWidget::setData(HunLing a){
    tempHL=a;
    Name.setText("名字："+a.Name);
    Des.setText("介绍："+a.Des);
    Strength.setText("力量："+QString::number(a.Strength));
    Agility.setText("敏捷："+QString::number(a.Agility));
    ATK.setText("攻击力："+QString::number(a.ATK));
    DEF.setText("防御力："+QString::number(a.DEF));
    VIT.setText("生命力："+QString::number(a.VIT));
    K_Fire.setText("火抗："+QString::number(a.K_Fire));
    K_Ice.setText("冰抗："+QString::number(a.K_Ice));
    K_Lig.setText("电抗："+QString::number(a.K_Lig));
    K_Tox.setText("毒抗："+QString::number(a.K_Tox));
    G_Fire.setText("火焰伤害："+QString::number(a.G_Fire));
    G_Ice.setText("冰冷伤害："+QString::number(a.G_Ice));
    G_Lig.setText("电击伤害："+QString::number(a.G_Lig));
    G_Tox.setText("毒素伤害："+QString::number(a.G_Tox));
    ATK_Ski.setText("攻击技能：<br>"+SystemHJ[a.ATK_Ski.ID].Name+"："+SystemHJ[a.ATK_Ski.ID].Des+"<br>所需魂力："+QString::number(a.ATK_Ski.Energy)+"<br>所需灵力："+QString::number(a.ATK_Ski.Sour)+"<br>冷却时间："+QString::number(a.ATK_Ski.NowTurn));
    DEF_Ski.setText("防御技能：<br>"+SystemBuff[a.DEF_Ski].Name+"："+SystemBuff[a.DEF_Ski].Des);
}

class HLWidget: public QWidget{
public:
    HunLing tempHL;
    QLabel Head;
    QLabel Name;
    QLabel LV;
    QLabel ATK;
    QLabel DEF;
    QLabel VIT;
    PushButton Data;
    QVBoxLayout MainLayout;
    HLDataWidget* tempData;
public:
    HLWidget();
    ~HLWidget(){}
    void Data_Click();
    void setData(HunLing a);

};
HLWidget::HLWidget(){
    this->setObjectName("fight");
    this->setObjectName("main");
    Data.setObjectName("function");

    //  Head.setPixmap(QPixmap::load(""));
    Name.setText("名字");
    LV.setText("等级：");
    ATK.setText("攻击力：");
    DEF.setText("防御力：");
    VIT.setText("生命力：");
    Data.setText("详细");
    Data.setFixedSize(150,30);
    MainLayout.addWidget(&Head);
    MainLayout.addWidget(&Name);
    MainLayout.addWidget(&LV);
    MainLayout.addWidget(&ATK);
    MainLayout.addWidget(&DEF);
    MainLayout.addWidget(&VIT);
    MainLayout.addWidget(&Data);
    this->setLayout(&MainLayout);
    connect(&Data,&QPushButton::clicked,this,&HLWidget::Data_Click);
}

void HLWidget::Data_Click(){
    tempData=new HLDataWidget(tempHL);
    tempData->exec();
    delete tempData;
}

void HLWidget::setData(HunLing a){
    tempHL=a;
    Name.setText(a.Name);
    LV.setText("等级："+QString::number(a.LV));
    ATK.setText("攻击力："+QString::number(a.ATK));
    DEF.setText("防御力："+QString::number(a.DEF));
    VIT.setText("生命力："+QString::number(a.VITNOW)+"/"+QString::number(a.VIT));
}

class ChooseDialog: public QDialog{
public:
    int num;
    QList<HunLing> temphl;
    QListWidget List;
    PushButton OK;
    PushButton Close;
    QVBoxLayout* MainLayout;
    ChooseDialog(QList<HunLing> a){
        temphl=a;
        this->setObjectName("main");
        OK.setObjectName("function");
        Close.setObjectName("close");
        this->setFixedSize(290,300);
        num=-1;
        List.setFocusPolicy(Qt::NoFocus);
        for(int i=0;i<a.size();i++)
            List.addItem(a[i].Name+"   生命值："+QString::number(a[i].VITNOW));
        MainLayout=new QVBoxLayout;
        List.setCurrentRow(0);
        MainLayout->addWidget(&List);
        OK.setText("确定");
        OK.setFixedSize(255,30);
        Close.setText("关闭");
        Close.setFixedSize(255,30);
        MainLayout->addWidget(&OK);
        MainLayout->addWidget(&Close);
        this->setLayout(MainLayout);
        connect(&OK,&QPushButton::clicked,this,&ChooseDialog::OKClick);
        connect(&Close,&QPushButton::clicked,this,&ChooseDialog::close);
        connect(&List,&QListWidget::doubleClicked,this,&ChooseDialog::ShowData);
        this->setWindowFlags(Qt::CustomizeWindowHint);
        this->setWindowTitle("请选择魂灵");
    }
    ~ChooseDialog(){}
    void OKClick(){
        if(temphl[List.currentRow()].VITNOW==0){
            QMessageBox::about(this,"提示","请不要鞭尸！");
            return;
        }
        num=List.currentRow();
        this->close();
    }
    void ShowData(){
        HLDataWidget* a=new HLDataWidget(temphl[List.currentRow()]);
        a->exec();
        delete a;
    }
};

class SkillChooseDialog: public QDialog{
public:
    int Energy;
    int Sour;
    int type;//记录选择了哪个灵骨
    HunJi Skill;
    LGList LG;
    QListWidget List;
    PushButton OK;
    PushButton Close;
    QVBoxLayout* MainLayout;
    SkillChooseDialog(LGList a,int b,int c){
        this->setObjectName("main");
        OK.setObjectName("function");
        Close.setObjectName("close");
        this->setFixedSize(290,300);
        this->setWindowFlags(Qt::CustomizeWindowHint);
        List.setFocusPolicy(Qt::NoFocus);
        Skill.ID=0;
        Energy=b;
        Sour=c;
        LG=a;
        Close.setText("关闭");
        Close.setFixedSize(255,30);
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
        OK.setFixedSize(255,30);
        MainLayout=new QVBoxLayout;
        List.setCurrentRow(0);
        MainLayout->addWidget(&List);
        MainLayout->addWidget(&OK);
        MainLayout->addWidget(&Close);
        this->setLayout(MainLayout);
        connect(&OK,&QPushButton::clicked,this,&SkillChooseDialog::OKClick);
        connect(&Close,&QPushButton::clicked,this,&SkillChooseDialog::close);
        this->setWindowTitle("请选择灵骨技能");

    }
    ~SkillChooseDialog(){}
    void OKClick(){
        if(List.item(List.currentRow())->text()=="此位置无灵骨"){
            MessageBox::about(this,"提示","此位置无灵骨");
            return;
        }
        switch(List.currentRow()){
        case 0:
            if(LG.Head.ATK_Ski.NowTurn>0&&LG.Head.ATK_Ski.Energy>=Energy&&LG.Head.ATK_Ski.Sour>=Sour){
                MessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.Head.ATK_Ski;
            type=1;
            break;
        case 1:
            if(LG.Body.ATK_Ski.NowTurn>0&&LG.Body.ATK_Ski.Energy>=Energy&&LG.Body.ATK_Ski.Sour>=Sour){
                MessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.Body.ATK_Ski;
            type=2;
            break;
        case 2:
            if(LG.LHand.ATK_Ski.NowTurn>0&&LG.LHand.ATK_Ski.Energy>=Energy&&LG.LHand.ATK_Ski.Sour>=Sour){
                MessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.LHand.ATK_Ski;
            type=3;
            break;
        case 3:
            if(LG.RHand.ATK_Ski.NowTurn>0&&LG.RHand.ATK_Ski.Energy>=Energy&&LG.RHand.ATK_Ski.Sour>=Sour){
                MessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.RHand.ATK_Ski;
            type=4;
            break;
        case 4:
            if(LG.LLeg.ATK_Ski.NowTurn>0&&LG.LLeg.ATK_Ski.Energy>=Energy&&LG.LLeg.ATK_Ski.Sour>=Sour){
                MessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.LLeg.ATK_Ski;
            type=5;
            break;
        case 5:
            if(LG.RLeg.ATK_Ski.NowTurn>0&&LG.RLeg.ATK_Ski.Energy>=Energy&&LG.RLeg.ATK_Ski.Sour>=Sour){
                MessageBox::about(this,"提示","此技能冷却中或魂力或灵力不足");
                return;
            }
            Skill=LG.RLeg.ATK_Ski;
            type=6;
            break;
        }
        this->close();

    }
};


class FightItemWidget:public QDialog{
public:
    int UseIndex;
    QList<Item> tempItem;
    QListWidget List;
    PushButton OK;
    PushButton Close;
    QVBoxLayout* MainLayout;
    FightItemWidget(QList<Item> a){
        this->setObjectName("main");
        OK.setObjectName("function");
        Close.setObjectName("close");


        this->setFixedSize(290,300);
        List.setFocusPolicy(Qt::NoFocus);
        this->setWindowFlags (Qt::CustomizeWindowHint);
        tempItem=a;
        OK.setText("确定");
        OK.setFixedSize(255,30);
        UseIndex=-1;
        Close.setText("关闭");
        Close.setFixedSize(255,30);
        for(int i=0;i<a.size();i++)
            List.addItem(tempItem[i].Name+"作用："+tempItem[i].Des);

        MainLayout=new QVBoxLayout;
        List.setCurrentRow(0);
        OK.setEnabled(false);
        MainLayout->addWidget(&List);
        MainLayout->addWidget(&OK);
        MainLayout->addWidget(&Close);
        this->setLayout(MainLayout);
        connect(&OK,&QPushButton::clicked,this,&FightItemWidget::OKClick);
        connect(&Close,&QPushButton::clicked,this,&FightItemWidget::close);
        connect(&List,&QListWidget::clicked,this,&FightItemWidget::Set);
        this->setWindowTitle("请选择道具");
    }
    ~FightItemWidget(){}

    void OKClick(){
        if(tempItem[List.currentRow()].Type!=2){
            MessageBox::about(this,"提示","此道具无法在战斗中使用 ");
            return;
        }
        UseIndex=List.currentRow();
        this->hide();
    }
    void Set(){OK.setEnabled(true);}
};

class FightWidget: public QDialog{
public:
    FightSystem* System;
    RenWu* Me;
    NPC Enemy;
    QList<HunLing> MyHL;
    QList<HunLing> EnemyHL;
    QList<HunLing*> tmpMyHL;
    QList<HunLing*> tmpEnemyHL;
    QListWidget EnemyHLList;
    QListWidget MyHLList;
    QListWidget MessageList;
    HLWidget HLData;
    QLabel Energy;
    QLabel Sour;

    QLabel Title;

    PushButton GoOn;

    PushButton ATkButton;
    PushButton SkillButton;
    PushButton LGSkillButton;
    PushButton ItemButton;
    PushButton SkipButton;



    QHBoxLayout* Layout1;
    QHBoxLayout* Layout2;
    QHBoxLayout* LabelLayout;
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
    void SetLast(){
        MessageList.setCurrentRow(MessageList.count()-1);
    }
};

FightWidget::FightWidget(RenWu *a, NPC b){
    this->setObjectName("fight");
    SkipButton.setObjectName("close");
    this->setFixedSize(670,480);
    this->setWindowFlags (Qt::CustomizeWindowHint);
    EnemyHLList.setFocusPolicy(Qt::NoFocus);
    MyHLList.setFocusPolicy(Qt::NoFocus);
    MessageList.setFocusPolicy(Qt::NoFocus);
    Me=a;
    Me->Energy=Me->Ori_Energy;
    Me->Sour=Me->Ori_Sour;
    Enemy=b;
    Enemy.Energy=Enemy.Ori_Energy;
    Enemy.Sour=Enemy.Ori_Sour;
    Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));
    Sour.setAlignment(Qt::AlignRight);
    WinOrLose=0;

    for (int i = 0; i < a->LH.size(); i++)//灵环初始化成魂灵
        if(a->LH[i].ID!=0)
            MyHL.append(GameSystem::CreatHL(*a,a->LH[i]));

    for (int i = 0; i < b.LH.size(); i++)
        if(b.LH[i].ID!=0)
            EnemyHL.append(GameSystem::CreatHL(b,b.LH[i]));



    for (int i = 0; i < MyHL.size(); i++)//灵环初始化成魂灵
        tmpMyHL.append(&MyHL[i]);

    for (int i = 0; i < EnemyHL.size(); i++)
        tmpEnemyHL.append(&EnemyHL[i]);



    System=new FightSystem(Me,&Enemy,tmpMyHL,tmpEnemyHL);

    for(int i=0;i<MyHL.size();i++)
        MyHLList.addItem(MyHL[i].Name+"   "+QString::number(MyHL[i].VITNOW)+"/"+QString::number(MyHL[i].VIT));
    for(int i=0;i<EnemyHL.size();i++)
        EnemyHLList.addItem(EnemyHL[i].Name+"   "+QString::number(EnemyHL[i].VITNOW)+"/"+QString::number(EnemyHL[i].VIT));

    MessageList.addItem("战斗开始！");
    HLData.setData(MyHL[0]);
    Title.setText("战斗中...0 Turn");
    Title.setAlignment(Qt::AlignCenter);
    GoOn.setText("继续");
    GoOn.setFixedSize(200,30);
    ATkButton.setText("攻击");
    ATkButton.setFixedSize(130,30);
    SkillButton.setText("魂灵技能");
    SkillButton.setFixedSize(130,30);
    LGSkillButton.setText("灵骨技能");
    LGSkillButton.setFixedSize(130,30);
    ItemButton.setText("背包");
    ItemButton.setFixedSize(130,30);
    SkipButton.setText("跳过");
    SkipButton.setFixedSize(130,30);

    ATkButton.setEnabled(false);
    SkillButton.setEnabled(false);
    LGSkillButton.setEnabled(false);
    ItemButton.setEnabled(false);
    SkipButton.setEnabled(false);

    Layout1=new QHBoxLayout;
    Layout2=new QHBoxLayout;
    MainLayout=new QVBoxLayout;
    LabelLayout=new QHBoxLayout;

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

    LabelLayout->addWidget(&Energy);
    LabelLayout->addWidget(&GoOn);
    LabelLayout->addWidget(&Sour);

    MainLayout->addWidget(&Title);
    MainLayout->addLayout(Layout1);
    MainLayout->addLayout(LabelLayout);
    MainLayout->addLayout(Layout2);
    MainLayout->addWidget(&MessageList);
    this->setLayout(MainLayout);

    connect(&ATkButton,&QPushButton::clicked,this,&FightWidget::Attack);
    connect(&SkillButton,&QPushButton::clicked,this,&FightWidget::Skill);
    connect(&LGSkillButton,&QPushButton::clicked,this,&FightWidget::LGSkill);
    connect(&ItemButton,&QPushButton::clicked,this,&FightWidget::UseItem);
    connect(&SkipButton,&QPushButton::clicked,this,&FightWidget::Skip);
    connect(&GoOn,&QPushButton::clicked,this,&FightWidget::GoOn_Ckick);
    connect(&EnemyHLList,&QListWidget::clicked,this,&FightWidget::EnemyClick);
    connect(&MyHLList,&QListWidget::clicked,this,&FightWidget::MeClick);




}


void FightWidget::Attack(){
    if(System->EB->type==0){
        HunLing tempEnemy=EnemyHL[System->EB->index];
        int a=GetNumber(1,MyHL.size());
        HunLing tempMe=MyHL[a-1];//以后要优化
        while(tempMe.VITNOW==0){
            a=GetNumber(1,MyHL.size());
            tempMe=MyHL[a-1];
        }
        QString msg=System->Attack(&tempEnemy,&tempMe);
        msg="（敌方）"+msg;
        //MessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);
        EnemyHL[System->EB->index]=tempEnemy;
        MyHL[a-1]=tempMe;
        GoOn.setEnabled(true);
    }
    if(System->EB->type==1){
        ChooseDialog* temp=new ChooseDialog(EnemyHL);
        temp->exec();
        if(temp->num<0){
            delete temp;
            return;
        }
        HunLing tempEnemy=EnemyHL[temp->num];
        HunLing tempMe=MyHL[System->EB->index];
        QString msg=System->Attack(&tempMe,&tempEnemy);
        msg="（我方）"+msg;
        //MessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);
        EnemyHL[temp->num]=tempEnemy;
        MyHL[System->EB->index]=tempMe;
        delete temp;
        GoOn.setEnabled(true);
    }
    this->SetButtonEnable(false);
    Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));

    MyHLList.clear();
    EnemyHLList.clear();
    for(int i=0;i<MyHL.size();i++)
        MyHLList.addItem(MyHL[i].Name+"   "+QString::number(MyHL[i].VITNOW)+"/"+QString::number(MyHL[i].VIT));
    for(int i=0;i<EnemyHL.size();i++)
        EnemyHLList.addItem(EnemyHL[i].Name+"   "+QString::number(EnemyHL[i].VITNOW)+"/"+QString::number(EnemyHL[i].VIT));
    SetLast();
}

void FightWidget::Skill(){
    if(System->EB->type==0){
        HunLing &tempEnemy=EnemyHL[System->EB->index];
        QString msg="";
        switch(tempEnemy.ATK_Ski.Type){
        case ENEMYSINGLE:{
            int a=GetNumber(1,MyHL.size());
            HunLing tempMe=MyHL[a-1];//以后要优化
            while(tempMe.VITNOW==0){
                a=GetNumber(1,MyHL.size());
                tempMe=MyHL[a-1];
            }
            msg=System->Skill(&tempEnemy,&tempMe,&tempEnemy.ATK_Ski);
            MyHL[a-1]=tempMe;
            break;
        }
        case ENEMYTEAM:{
            msg=System->Skill(&tempEnemy,tmpMyHL,&tempEnemy.ATK_Ski);
            break;
        }
        case MYSIGLE:{
            int b=GetNumber(1,EnemyHL.size());
            HunLing b1=EnemyHL[b-1];//以后要优化
            while(b1.VITNOW==0){
                b=GetNumber(1,MyHL.size());
                b1=MyHL[b-1];
            }
            msg=System->Skill(&tempEnemy,&b1,&tempEnemy.ATK_Ski);
            EnemyHL[b-1]=b1;
            break;
        }
        case MYTEAM:{
            msg=System->Skill(&tempEnemy,tmpEnemyHL,&tempEnemy.ATK_Ski);
            break;
        }
        }
        msg="（敌方）"+msg;
        //MessageBox::about(this,"提示",msg);

        System->UsedSkill(&Enemy,&tempEnemy.ATK_Ski);
        EnemyHL[System->EB->index].ATK_Ski=tempEnemy.ATK_Ski;

        MessageList.addItem(msg);

        GoOn.setEnabled(true);
    }
    if(System->EB->type==1){
        HunLing &tempMe=MyHL[System->EB->index];
        QString msg="";
        QMessageBox msgBox;
        msgBox.setWindowTitle("魂技");
        msgBox.setText(tempMe.ATK_Ski.Name+"："+tempMe.ATK_Ski.Des+"<br>所需魂力："+QString::number(tempMe.ATK_Ski.Energy)+"<br>所需灵力："+QString::number(tempMe.ATK_Ski.Sour)+"<br>冷却时间："+QString::number(tempMe.ATK_Ski.Turn));
        msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        msgBox.buttons()[0]->setFixedSize(100,30);
        msgBox.buttons()[1]->setFixedSize(100,30);
        int ret = msgBox.exec();
        if(ret==QMessageBox::No)
            return;

        if(tempMe.ATK_Ski.NowTurn>0){
            MessageBox::about(this,"提示","技能还有"+QString::number(tempMe.ATK_Ski.NowTurn)+"回合冷却时间！");
            return;
        }
        else{
            if(tempMe.ATK_Ski.Energy>Me->Energy||tempMe.ATK_Ski.Sour>Me->Sour){
                MessageBox::about(this,"提示","魂力或灵力不足");
                return;
            }
        }


        switch(tempMe.ATK_Ski.Type){
        case ENEMYSINGLE:{
            ChooseDialog* temp=new ChooseDialog(EnemyHL);
            temp->exec();
            if(temp->num<0){
                delete temp;
                return;
            }
            HunLing tempEnemy1=EnemyHL[temp->num];
            msg=System->Skill(&tempMe,&tempEnemy1,&tempMe.ATK_Ski);
            EnemyHL[temp->num]=tempEnemy1;
            delete temp;
            break;
        }
        case ENEMYTEAM:
            msg=System->Skill(&tempMe,tmpEnemyHL,&tempMe.ATK_Ski);
            break;
        case MYSIGLE:{
            ChooseDialog* temp1=new ChooseDialog(MyHL);
            temp1->exec();
            if(temp1->num<0){
                delete temp1;
                return;
            }
            HunLing tempEnemy=MyHL[temp1->num];
            msg=System->Skill(&tempMe,&tempEnemy,&tempMe.ATK_Ski);
            MyHL[temp1->num]=tempEnemy;
            delete temp1;
            break;
        }
        case MYTEAM:
            msg=System->Skill(&tempMe,tmpMyHL,&tempMe.ATK_Ski);
            break;
        }

        msg="（我方）"+msg;
        //MessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);


        System->UsedSkill(Me,&tempMe.ATK_Ski);



        GoOn.setEnabled(true);

    }
    this->SetButtonEnable(false);
    Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));

    MyHLList.clear();
    EnemyHLList.clear();
    for(int i=0;i<MyHL.size();i++)
        MyHLList.addItem(MyHL[i].Name+"   "+QString::number(MyHL[i].VITNOW)+"/"+QString::number(MyHL[i].VIT));
    for(int i=0;i<EnemyHL.size();i++)
        EnemyHLList.addItem(EnemyHL[i].Name+"   "+QString::number(EnemyHL[i].VITNOW)+"/"+QString::number(EnemyHL[i].VIT));
    SetLast();
}

void FightWidget::EnemyLGSkill(HunJi* Skill){
    HunLing &tempEnemy=EnemyHL[System->EB->index];
    QString msg="";
    switch(Skill->Type){
    case 0:{
        int a=GetNumber(1,MyHL.size());
        HunLing tempMe=MyHL[a-1];//以后要优化
        while(tempMe.VITNOW==0){
            a=GetNumber(1,MyHL.size());
            tempMe=MyHL[a-1];
        }
        msg=System->Skill(&tempEnemy,&tempMe,Skill);
        msg=msg+"（灵骨技能）";
        MyHL[a-1]=tempMe;
        break;
    }
    case 1:
        msg=System->Skill(&tempEnemy,tmpMyHL,Skill);
        msg=msg+"（灵骨技能）";
        break;
    case 2:{
        int b=GetNumber(1,EnemyHL.size());
        HunLing b1=EnemyHL[b-1];//以后要优化
        while(b1.VITNOW==0){
            b=GetNumber(1,MyHL.size());
            b1=MyHL[b-1];
        }
        msg=System->Skill(&tempEnemy,&b1,Skill);
        msg=msg+"（灵骨技能）";
        EnemyHL[b-1]=b1;
        break;
    }
    case 3:
        msg=System->Skill(&tempEnemy,tmpEnemyHL,Skill);
        msg=msg+"（灵骨技能）";
        break;
    }
    msg="（敌方）"+msg;
    //MessageBox::about(this,"提示",msg);
    MessageList.addItem(msg);


    System->UsedSkill(&Enemy,Skill);


    GoOn.setEnabled(true);
    Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));

    MyHLList.clear();
    EnemyHLList.clear();
    for(int i=0;i<MyHL.size();i++)
        MyHLList.addItem(MyHL[i].Name+"   "+QString::number(MyHL[i].VITNOW)+"/"+QString::number(MyHL[i].VIT));
    for(int i=0;i<EnemyHL.size();i++)
        EnemyHLList.addItem(EnemyHL[i].Name+"   "+QString::number(EnemyHL[i].VITNOW)+"/"+QString::number(EnemyHL[i].VIT));
    SetLast();

}
void FightWidget::LGSkill(){
    HunLing &tempMe=MyHL[System->EB->index];
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
        if(temp->num<0){
            delete temp;
            return;
        }
        HunLing tempEnemy1=EnemyHL[temp->num];
        msg=System->Skill(&tempMe,&tempEnemy1,&temp2->Skill);
        EnemyHL[temp->num]=tempEnemy1;
        msg=msg+"（灵骨技能）";
        delete temp;
        break;
    }
    case 1:
        msg=System->Skill(&tempMe,tmpEnemyHL,&temp2->Skill);
        msg=msg+"（灵骨技能）";
        break;
    case 2:{
        ChooseDialog* temp1=new ChooseDialog(MyHL);
        temp1->exec();
        if(temp1->num<0){
            delete temp1;
            return;
        }
        HunLing tempEnemy=MyHL[temp1->num];
        msg=System->Skill(&tempMe,&tempEnemy,&temp2->Skill);
        MyHL[temp1->num]=tempEnemy;
        msg=msg+"（灵骨技能）";
        delete temp1;
        break;
    }
    case 3:
        msg=System->Skill(&tempMe,tmpMyHL,&temp2->Skill);
        msg=msg+"（灵骨技能）";
        break;
    }

    System->UsedSkill(Me,&temp2->Skill);

    switch(temp2->type){
    case 1:
        Me->LG.Head.ATK_Ski=temp2->Skill;
        break;
    case 2:
        Me->LG.Body.ATK_Ski=temp2->Skill;
        break;
    case 3:
        Me->LG.RHand.ATK_Ski=temp2->Skill;
        break;
    case 4:
        Me->LG.LHand.ATK_Ski=temp2->Skill;
        break;
    case 5:
        Me->LG.RLeg.ATK_Ski=temp2->Skill;
        break;
    case 6:
        Me->LG.LLeg.ATK_Ski=temp2->Skill;
        break;
    }
    msg="（我方）"+msg;
    // MessageBox::about(this,"提示",msg);
    MessageList.addItem(msg);


    delete temp2;
    GoOn.setEnabled(true);
    this->SetButtonEnable(false);
    Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));

    MyHLList.clear();
    EnemyHLList.clear();
    for(int i=0;i<MyHL.size();i++)
        MyHLList.addItem(MyHL[i].Name+"   "+QString::number(MyHL[i].VITNOW)+"/"+QString::number(MyHL[i].VIT));
    for(int i=0;i<EnemyHL.size();i++)
        EnemyHLList.addItem(EnemyHL[i].Name+"   "+QString::number(EnemyHL[i].VITNOW)+"/"+QString::number(EnemyHL[i].VIT));

    SetLast();
}


void FightWidget::UseItem(){
    HunLing &tempMe=MyHL[System->EB->index];
    QString msg="";
    FightItemWidget* tempItemList=new FightItemWidget(Me->Bag);
    tempItemList->exec();
    if(tempItemList->UseIndex==-1){
        delete tempItemList;
        return;
    }

    switch(Me->Bag[tempItemList->UseIndex].ATKType){
    case 0:{
        ChooseDialog* temp=new ChooseDialog(EnemyHL);
        temp->exec();
        if(temp->num<0){
            delete temp;
            return;
        }
        HunLing tempEnemy1=EnemyHL[temp->num];
        msg=System->UseItem(&tempMe,&tempEnemy1,Me->Bag[tempItemList->UseIndex].ID);
        EnemyHL[temp->num]=tempEnemy1;
        delete temp;
        break;
    }
    case 1:
        msg=System->UseItem(&tempMe,tmpEnemyHL,Me->Bag[tempItemList->UseIndex].ID);
        break;
    case 2:{
        ChooseDialog* temp1=new ChooseDialog(MyHL);
        temp1->exec();
        if(temp1->num<0){
            delete temp1;
            return;
        }
        HunLing tempEnemy=MyHL[temp1->num];
        msg=System->UseItem(&tempMe,&tempEnemy,Me->Bag[tempItemList->UseIndex].ID);
        MyHL[temp1->num]=tempEnemy;
        delete temp1;
        break;
    }
    case 3:
        msg=System->UseItem(&tempMe,tmpMyHL,Me->Bag[tempItemList->UseIndex].ID);

        break;
    }

    msg="（我方）"+msg;
    //MessageBox::about(this,"提示",msg);
    MessageList.addItem(msg);



    delete tempItemList;

    GoOn.setEnabled(true);


    this->SetButtonEnable(false);
    Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));

    MyHLList.clear();
    EnemyHLList.clear();
    for(int i=0;i<MyHL.size();i++)
        MyHLList.addItem(MyHL[i].Name+"   "+QString::number(MyHL[i].VITNOW)+"/"+QString::number(MyHL[i].VIT));
    for(int i=0;i<EnemyHL.size();i++)
        EnemyHLList.addItem(EnemyHL[i].Name+"   "+QString::number(EnemyHL[i].VITNOW)+"/"+QString::number(EnemyHL[i].VIT));
    SetLast();
}

void FightWidget::Skip(){
    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("你确定要跳过吗？？？");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.buttons()[0]->setFixedSize(100,30);
    msgBox.buttons()[1]->setFixedSize(100,30);
    int ret = msgBox.exec();
    if(ret==QMessageBox::Yes){
        MessageList.addItem("（我方）"+MyHL[System->EB->index].Name+"无所事事！跳过了回合！");
        GoOn.setEnabled(true);
        this->SetButtonEnable(false);
    }
    SetLast();
}

void FightWidget::EnemyClick(){
    int a=EnemyHLList.currentRow();
    HLData.setData(EnemyHL[a]);

}

void FightWidget::MeClick(){
    int a=MyHLList.currentRow();
    HLData.setData(MyHL[a]);

}

void FightWidget::GoOn_Ckick(){
    Title.setText("战斗中..."+QString::number(System->Turn)+" Turn");
    GoOn.setEnabled(false);
    System->TurnOut();
    if(System->CanGoOn()==1){
        System->EB->next();
        if(System->EB->type==0){
            MessageList.addItem("（敌方）现在是 "+EnemyHL[System->EB->index].Name+"的回合！");
            EnemyHLList.setCurrentRow(System->EB->index);
            EnemyClick();
            if(Enemy.Des=="魂灵"){
                if(Enemy.CanUseHJList(EnemyHL[System->EB->index].ID).isEmpty()==true){
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
                if(Enemy.CanUseHJList(EnemyHL[System->EB->index].ID).isEmpty()==true){
                    Attack();
                }
                else{
                    if(GetNumber(0,10)>=9)
                        Attack();
                    else{
                        QList<int> temphj=Enemy.CanUseHJList(EnemyHL[System->EB->index].ID);
                        int hj=GetNumber(1,temphj.size());
                        if(GetNumber(1,10)>7)hj=1;
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
            GoOn.setEnabled(true);

        }
        else{
            this->SetButtonEnable(true);
            MessageList.addItem("（我方）现在是 "+MyHL[System->EB->index].Name+"的回合！");
            MyHLList.setCurrentRow(System->EB->index);
            MeClick();
        }


    }
    Energy.setText("魂力："+QString::number(Me->Energy)+"/"+QString::number(Me->Ori_Energy));
    Sour.setText("灵力："+QString::number(Me->Sour)+"/"+QString::number(Me->Ori_Sour));

    MyHLList.clear();
    EnemyHLList.clear();
    System->UpdateVIT();
    for(int i=0;i<MyHL.size();i++)
        MyHLList.addItem(MyHL[i].Name+"   "+QString::number(MyHL[i].VITNOW)+"/"+QString::number(MyHL[i].VIT));
    for(int i=0;i<EnemyHL.size();i++)
        EnemyHLList.addItem(EnemyHL[i].Name+"   "+QString::number(EnemyHL[i].VITNOW)+"/"+QString::number(EnemyHL[i].VIT));
    SetLast();
    if(System->CanGoOn()==0){
        MessageBox::about(this,"提示","你输了！");
        WinOrLose=0;
        this->close();
        return;
    }
    if(System->CanGoOn()==-1){
        MessageBox::about(this,"提示","你获得了胜利！");
        WinOrLose=1;
        Reward=GameSystem::DropItem(EnemyHL);
        this->close();
        return;
    }
    if(System->CanGoOn()==-2){
        MessageBox::about(this,"提示","分不出胜负！");
        WinOrLose=-1;
        this->close();
        return;
    }

}


#endif
















