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
    }

};





class LGSkillWidget: public QDialog
{
    public:
    LGList Me;
    int Used;
    QListWidget Wear;
    QLabel Title;
    QLabel Text;
    QLabel LV;
    QLabel Name;
    QLabel Des;
    QLabel Type;
    QLabel Value;
    QLabel Strength;
    QLabel Agility;
    QLabel DEF_Ski;
    QLabel ATK_Ski;
    QLabel Add;//增加属性

    QPushButton Use;

    public:
    LGSkillWidget(LGList a);
    ~LGSkillWidget(){}
    void Use_Click();

};

LGSkillWidget::LGSkillWidget(LGList a)
{
    Me=a;

}


void LGSkillWidget::Use_Click()
{

}
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
     MessageList.addItem(System->Attack(&tempEnemy,&tempMe));
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

}

void FightWidget::Skill()
{

}

void FightWidget::LGSkill()
{

}

void FightWidget::UseItem()
{

}

void FightWidget::Skip()
{

}

void FightWidget::GoOn_Ckick()
{

}

void FightWidget::EnemyClick()
{

}

void FightWidget::MeClick()
{

}



















