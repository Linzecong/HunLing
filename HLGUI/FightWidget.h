#include<QString>
#include<QWidget>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
class ChooseDialog: public QDialog
{
	public:
	int num;

    QListWidget List;
    QPushButton OK;
    QVBoxLayout* MainLayout;
    ChooseDialog(HLList a)
    {
        for(int i=1;i<=a.Count();i++)
            List.addItem(a.GetData(i).Name+"   生命值："+QString::number(a.GetData(i).VITNOW));
        MainLayout=new QVBoxLayout;
        List.setCurrentRow(0);
        MainLayout->addWidget(&List);
        MainLayout->addWidget(&OK);
        this->setLayout(MainLayout);
        connect(&OK,&QPushButton::clicked,this,&ChooseDialog::OKClick);
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setWindowTitle("请选择魂灵");

    }
    ~ChooseDialog(){}
    void OKClick()
    {
        num=List.currentRow()+1;
        this->close();
    }

};

class SkillChooseDialog: public QDialog
{
public:
    HunJi Skill;
    LGList LG;
    QListWidget List;
    QPushButton OK;
    QVBoxLayout* MainLayout;
    SkillChooseDialog(LGList a)
    {

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

        MainLayout=new QVBoxLayout;
        List.setCurrentRow(0);
        MainLayout->addWidget(&List);
        MainLayout->addWidget(&OK);
        this->setLayout(MainLayout);
        connect(&OK,&QPushButton::clicked,this,&SkillChooseDialog::OKClick);
        this->setWindowFlags(Qt::FramelessWindowHint);
        this->setWindowTitle("请选择灵骨技能");

    }
    ~SkillChooseDialog(){}


    void OKClick()
    {
        if(List.item(List.currentRow())->text()=="此位置无灵骨")
        {
            QMessageBox::about(this,"提示","此位置无灵骨");
            return;
        }
        switch(List.currentRow())
        {
        case 0:
            if(LG.Head.ATK_Ski.NowTurn>0)
            {
                QMessageBox::about(this,"提示","此技能冷却中");
                return;
            }
            Skill=LG.Head.ATK_Ski;
            break;
        case 1:
            if(LG.Body.ATK_Ski.NowTurn>0)
            {
                QMessageBox::about(this,"提示","此技能冷却中");
                return;
            }
            Skill=LG.Body.ATK_Ski;
            break;
        case 2:
            if(LG.LHand.ATK_Ski.NowTurn>0)
            {
                QMessageBox::about(this,"提示","此技能冷却中");
                return;
            }
            Skill=LG.LHand.ATK_Ski;
            break;
        case 3:
            if(LG.RHand.ATK_Ski.NowTurn>0)
            {
                QMessageBox::about(this,"提示","此技能冷却中");
                return;
            }
            Skill=LG.RHand.ATK_Ski;
            break;
        case 4:
            if(LG.LLeg.ATK_Ski.NowTurn>0)
            {
                QMessageBox::about(this,"提示","此技能冷却中");
                return;
            }
            Skill=LG.LLeg.ATK_Ski;
            break;
        case 5:
            if(LG.RLeg.ATK_Ski.NowTurn>0)
            {
                QMessageBox::about(this,"提示","此技能冷却中");
                return;
            }
            Skill=LG.RLeg.ATK_Ski;
            break;
        }
        this->close();

    }



};


class FightItemWidget:public QDialog
{

};

class FightWidget: public QDialog
{
	public:
    FightSystem* System;
    RenWu Me;
	NPC Enemy;
    HLList MyHL;
    HLList EnemyHL;
    QListWidget EnemyHLList;
    QListWidget MyHLList;
    QListWidget MessageList;
    HLWidget HLData;

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
    FightWidget(RenWu a,NPC b);
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
};

FightWidget::FightWidget(RenWu a,NPC b)
{
    Me=a;
    Enemy=b;
    WinOrLose=0;
    for (int i = 1; i <= a.LH.Count(); i++)//灵环初始化成魂灵
    {
        LingHuan tempLH = a.LH.GetData(i);
        HunLing tempHL = SystemHL[tempLH.ID];
        tempHL.LV = tempLH.LV;
        tempHL.Strength += a.Strength;
        tempHL.Agility += a.Agility;
        tempHL.ATK =
            (1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.ATK_Str +
                                     tempHL.Agility * tempHL.ATK_Agi);
        tempHL.DEF =
            (1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.DEF_Str +
                                     tempHL.Agility * tempHL.DEF_Agi);
        tempHL.VIT = a.Vitality * tempHL.VIT_Vit * tempHL.LV;
        tempHL.VITNOW=tempHL.VIT;
        MyHL.Insert(tempHL);
    }
    for (int i = 1; i <= b.LH.Count(); i++)
    {
        LingHuan tempLH = b.LH.GetData(i);
        HunLing tempHL = SystemHL[tempLH.ID];
        tempHL.LV = tempLH.LV;
        tempHL.Strength += b.Strength;
        tempHL.Agility += b.Agility;
        tempHL.ATK =
            (1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.ATK_Str +
                                     tempHL.Agility * tempHL.ATK_Agi);
        tempHL.DEF =
            (1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.DEF_Str +
                                     tempHL.Agility * tempHL.DEF_Agi);
        tempHL.VIT = b.Vitality * tempHL.VIT_Vit * tempHL.LV;
        tempHL.VITNOW=tempHL.VIT;
        EnemyHL.Insert(tempHL);
    }

    System=new FightSystem(&Me,Enemy,&MyHL,&EnemyHL);

    for(int i=1;i<=MyHL.Count();i++)
        MyHLList.addItem(MyHL.GetData(i).Name);
    for(int i=1;i<=EnemyHL.Count();i++)
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

    Layout1=new QHBoxLayout;
    Layout2=new QHBoxLayout;
    MainLayout=new QVBoxLayout;

    Reward.Exp=0;
    Reward.Coin=0;

    Layout1->addWidget(&MyHLList);
    Layout1->addWidget(&HLData);
    Layout1->addWidget(&EnemyHLList);

    Layout2->addWidget(&ATkButton);
    Layout2->addWidget(&SkillButton);
    Layout2->addWidget(&LGSkillButton);
    Layout2->addWidget(&ItemButton);
    Layout2->addWidget(&SkipButton);

    MainLayout->addWidget(&Title);
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




}

void FightWidget::Attack()
{
    if(System->EB->type==0)
    {
        HunLing tempEnemy=EnemyHL.GetData(System->EB->index);
        int a=GetNumber(1,MyHL.Count());
        HunLing tempMe=MyHL.GetData(a);//以后要优化
        QString msg=System->Attack(&tempEnemy,&tempMe);
        QMessageBox::about(this,"提示",msg);
     MessageList.addItem(msg);
     EnemyHL.Replace(tempEnemy,System->EB->index);
     MyHL.Replace(tempMe,a);
     GoOn.setEnabled(true);
    }
    if(System->EB->type==1)
    {
        ChooseDialog* temp=new ChooseDialog(EnemyHL);
        temp->exec();
        HunLing tempEnemy=EnemyHL.GetData(temp->num);
        HunLing tempMe=MyHL.GetData(System->EB->index);
        QString msg=System->Attack(&tempMe,&tempEnemy);
        QMessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);
        EnemyHL.Replace(tempEnemy,temp->num);
        MyHL.Replace(tempMe,System->EB->index);
        delete temp;
        GoOn.setEnabled(true);

    }
    Layout2->setEnabled(false);

}

void FightWidget::Skill()
{
    if(System->EB->type==0)
    {
        HunLing tempEnemy=EnemyHL.GetData(System->EB->index);
        QString msg="";
        switch(tempEnemy.ATK_Ski.Type)
        {
        case 0:
        {
        int a=GetNumber(1,MyHL.Count());
        HunLing tempMe=MyHL.GetData(a);//以后要优化
        msg=System->Skill(&tempEnemy,&tempMe,&tempEnemy.ATK_Ski);
        MyHL.Replace(tempMe,a);
        break;
        }
        case 1:
        {
        msg=System->Skill(&tempEnemy,MyHL,&tempEnemy.ATK_Ski);
        break;
        }
        case 2:
        {
        int b=GetNumber(1,EnemyHL.Count());
        HunLing b1=EnemyHL.GetData(b);//以后要优化
        msg=System->Skill(&tempEnemy,&b1,&tempEnemy.ATK_Ski);
        EnemyHL.Replace(b1,b);
        break;
        }
        case 3:
        {
        msg=System->Skill(&tempEnemy,EnemyHL,&tempEnemy.ATK_Ski);
        break;
        }
        }
        QMessageBox::about(this,"提示",msg);
     MessageList.addItem(msg);
     EnemyHL.Replace(tempEnemy,System->EB->index);

     GoOn.setEnabled(true);
    }
    if(System->EB->type==1)
    {
        HunLing tempMe=MyHL.GetData(System->EB->index);
        QString msg="";
        switch(tempMe.ATK_Ski.Type)
        {
        case 0:
        {
            ChooseDialog* temp=new ChooseDialog(EnemyHL);
            temp->exec();
            HunLing tempEnemy1=EnemyHL.GetData(temp->num);
            msg=System->Skill(&tempMe,&tempEnemy1,&tempMe.ATK_Ski);
            EnemyHL.Replace(tempEnemy1,temp->num);
            delete temp;
            break;
        }
        case 1:
            msg=System->Skill(&tempMe,EnemyHL,&tempMe.ATK_Ski);
            break;
        case 2:
        {
            ChooseDialog* temp1=new ChooseDialog(MyHL);
            temp1->exec();
            HunLing tempEnemy=MyHL.GetData(temp1->num);
            msg=System->Skill(&tempMe,&tempEnemy,&tempMe.ATK_Ski);
            MyHL.Replace(tempEnemy,temp1->num);
            delete temp1;
            break;
        }
        case 3:
            msg=System->Skill(&tempMe,MyHL,&tempMe.ATK_Ski);
            break;
        }


        QMessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);

        MyHL.Replace(tempMe,System->EB->index);

        GoOn.setEnabled(true);

    }
    Layout2->setEnabled(false);
}

void FightWidget::EnemyLGSkill(HunJi* Skill)
{

        HunLing tempEnemy=EnemyHL.GetData(System->EB->index);
        QString msg="";
        switch(Skill->Type)
        {
        case 0:
        {
        int a=GetNumber(1,MyHL.Count());
        HunLing tempMe=MyHL.GetData(a);//以后要优化
        msg=System->Skill(&tempEnemy,&tempMe,Skill);
        msg=msg+"（灵骨技能）";
        MyHL.Replace(tempMe,a);
        break;
        }
        case 1:
        msg=System->Skill(&tempEnemy,MyHL,Skill);
        msg=msg+"（灵骨技能）";
        break;
        case 2:
        {
        int b=GetNumber(1,EnemyHL.Count());
        HunLing b1=EnemyHL.GetData(b);//以后要优化
        msg=System->Skill(&tempEnemy,&b1,Skill);
        msg=msg+"（灵骨技能）";
        EnemyHL.Replace(b1,b);
        break;
        }
        case 3:
        msg=System->Skill(&tempEnemy,EnemyHL,Skill);
        msg=msg+"（灵骨技能）";
        break;
        }
        QMessageBox::about(this,"提示",msg);
     MessageList.addItem(msg);
     EnemyHL.Replace(tempEnemy,System->EB->index);

     GoOn.setEnabled(true);


}
void FightWidget::LGSkill()
{
        HunLing tempMe=MyHL.GetData(System->EB->index);
        QString msg="";
        SkillChooseDialog* temp2=new SkillChooseDialog(Me.LG);
        temp2->exec();
        switch(temp2->Skill.Type)
        {
        case 0:
        {
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
            msg=System->Skill(&tempMe,EnemyHL,&tempMe.ATK_Ski);
            msg=msg+"（灵骨技能）";
            break;
        case 2:
        {
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
            msg=System->Skill(&tempMe,MyHL,&tempMe.ATK_Ski);
            msg=msg+"（灵骨技能）";
            break;
        }

        switch(temp2->Skill.Type)
        {
        case 0:
            Me.LG.Head.ATK_Ski=temp2->Skill;
            break;
        case 1:
            Me.LG.Body.ATK_Ski=temp2->Skill;
            break;
        case 2:
            Me.LG.RHand.ATK_Ski=temp2->Skill;
            break;
        case 3:
            Me.LG.LHand.ATK_Ski=temp2->Skill;
            break;
        case 4:
            Me.LG.RLeg.ATK_Ski=temp2->Skill;
            break;
        case 5:
            Me.LG.LLeg.ATK_Ski=temp2->Skill;
            break;
        }
        QMessageBox::about(this,"提示",msg);
        MessageList.addItem(msg);

        MyHL.Replace(tempMe,System->EB->index);
        GoOn.setEnabled(true);


    Layout2->setEnabled(false);

}


void FightWidget::UseItem()
{

}

void FightWidget::Skip()
{

}

void FightWidget::GoOn_Ckick()//注意判断技能冷却,敌人灵骨技能的冷却
{

}

void FightWidget::EnemyClick()
{

}

void FightWidget::MeClick()
{

}



















