/*战斗系统*/
#ifndef HL_FIGHTWIDGET
#define HL_FIGHTWIDGET

#include <QString>
#include <QList>
#include "HL_NPC.h"
#include "HL_HunLing.h"
#include "HL_RenWu.h"
#include "HL_GameSystem.h"

class EnergyBar{
public:
    QList<HunLing*> Me;
    QList<HunLing*> Enemy;
    QList<double> List;//敌人再自己
    double totle;//能量最大值
    int type;// 敌人还是自己,0敌人1自己
    int index;
public:
    EnergyBar(QList<HunLing*> a,QList<HunLing*> b);
    ~EnergyBar(){}
    void next();

};
EnergyBar::EnergyBar(QList<HunLing*> a, QList<HunLing*> b){
    Enemy=b;
    Me=a;
    totle=0;
    for(int i=0;i<Enemy.size();i++){//统计能量最大值
        totle+=Enemy[i]->Agility*500;
        List.append(Enemy[i]->Agility);
    }
    for(int i=0;i<Me.size();i++){
        totle+=Me[i]->Agility*500;
        List.append(Me[i]->Agility);
    }
    type=0;
    index=0;
}

void EnergyBar::next(){
    int stop=0;
    while(stop!=1){
        for(int i=0;i<List.size();i++){
            if(i<Enemy.size())//判断是加敌人还是自己的敏捷值
            List[i]+=Enemy[i]->Agility;
            else
            List[i]+=Me[i-Enemy.size()]->Agility;
        }
   for(int i=0;i<List.size();i++){
   if(List[i]>=totle){//如果大于能量最大值
       List[i]-=totle;//循环
       if(i>=Enemy.size()){
           type=1;
           index=i-Enemy.size();
       }
       else{
           type=0;
           index=i;
       }

       stop=1;
       break;

   }
   }
    }

}





class FightSystem{
  public:
	RenWu * Me;
    NPC* Enemy;
    QList<HunLing*> MyHL;
    QList<HunLing*> EnemyHL;
    EnergyBar* EB;
	int Turn;
  public:
	void SetBuff();//初始化后自动调用，设置Buff效果
    FightSystem(RenWu* a, NPC* b,QList<HunLing*> a1,QList<HunLing*> b1);
	void TurnOut();				// 技能-1
	QString Attack(HunLing * a, HunLing * b);//攻击
    QString Skill(HunLing * a, HunLing* b, HunJi * skill);//技能，直接传入技能。单体。
    QString Skill(HunLing * a, QList<HunLing*> b, HunJi * skill);//技能，直接传入技能。全体。注意replace
    QString UseItem(int a, HunLing * b, HunLing *c);//用道具，道具编号。
    QString UseItem(int a, HunLing * b, QList<HunLing*> c);//用道具，道具编号。全体，注意replace

	int CanGoOn();				// 判断能否继续
    void UpdateVIT();//每轮前调用，更新体力
};



FightSystem::FightSystem(RenWu* a, NPC *b, QList<HunLing *> a1, QList<HunLing *> b1){
    Me = a;
    Enemy= b;

    MyHL=a1;
    EnemyHL=b1;
	Turn = 1;
    EB=new EnergyBar(MyHL,EnemyHL);
	SetBuff();
}


void FightSystem::UpdateVIT(){

    for(int i=0;i<MyHL.size();i++){
        MyHL[i]->VIT = (Me->Vitality+MyHL[i]->Strength) * MyHL[i]->VIT_Vit * MyHL[i]->LV;
        if(MyHL[i]->VIT<MyHL[i]->VITNOW)
            MyHL[i]->VITNOW=MyHL[i]->VIT;
        if(MyHL[i]->Agility==0)
            MyHL[i]->VITNOW=0;
    }
        for(int i=0;i<EnemyHL.size();i++){
         EnemyHL[i]->VIT = (Enemy->Vitality+EnemyHL[i]->Strength) * EnemyHL[i]->VIT_Vit * EnemyHL[i]->LV;
         if(EnemyHL[i]->VIT<EnemyHL[i]->VITNOW)
             EnemyHL[i]->VITNOW=EnemyHL[i]->VIT;
         if(EnemyHL[i]->Agility==0)
             EnemyHL[i]->VITNOW=0;
        }

}

void FightSystem::TurnOut(){// 技能冷却-1
    Turn++;
    for (int i = 0; i < MyHL.size(); i++){
        MyHL[i]->ATK_Ski.NowTurn--;
        if (MyHL[i]->ATK_Ski.NowTurn < 0)
            MyHL[i]->ATK_Ski.NowTurn = 0;
	}
    for (int i = 0; i < EnemyHL.size(); i++){
        EnemyHL[i]->ATK_Ski.NowTurn--;
        if (EnemyHL[i]->ATK_Ski.NowTurn < 0)
            EnemyHL[i]->ATK_Ski.NowTurn = 0;
	}
    UpdateVIT();
}

int FightSystem::CanGoOn(){// 判断能否继续。0我输，1继续，-1赢了,-2平局
    if(Turn>=100)
        return -2;
	int n = 0;
    for (int i = 0; i < MyHL.size(); i++)
        if (MyHL[i]->VITNOW != 0)
			n = 1;

	if (n == 1){
		n = -1;
        for (int i = 0; i < EnemyHL.size(); i++)
            if (EnemyHL[i]->VITNOW != 0)
				n = 1;
	}
    return n;//注意初始化掉落
}

QString FightSystem::Attack(HunLing * a, HunLing * b){
    double ATKPoint = a->ATK - b->DEF;//以后要优化
	if (ATKPoint < 0)
		return a->Name+"的攻击太低了！起不了作用！";
    else{
        b->VITNOW -= ATKPoint;//important
        if (b->VITNOW <= 0){
            b->VITNOW = 0;
            b->Agility=0;
        }
		return a->Name+"对对方"+b->Name+"造成"+QString::number(ATKPoint)+"点伤害！";
	}
}

QString FightSystem::Skill(HunLing * a, HunLing * b, HunJi * skill){//注意技能类型！和体力小于0(敏捷制0)
	QString Description;
	skill->NowTurn += skill->Turn;
	switch (skill->ID){
	case 1:
        b->DEF=b->DEF*0.9;
        Description=a->Name+"对"+b->Name+"使用技能"+skill->Name+"，"+b->Name+"的防御变成了"+QString::number(b->DEF);
			break;
    case 2:{
        double ATKPoint=0;
        ATKPoint=((a->G_Lig)/100+1)*(a->ATK)-((b->K_Lig)/100+1)*(b->DEF);
        if (ATKPoint < 0)
            return a->Name+"的攻击太低了！起不了作用！";
        b->VITNOW -= ATKPoint*2.00;
        Description=a->Name+"对"+b->Name+"使用技能"+skill->Name+"，"+"对对方"+b->Name+"造成"+QString::number(ATKPoint)+"点伤害！";
}
            break;
    case 3:
        b->VITNOW+=100;
        Description=a->Name+"对"+b->Name+"使用技能"+skill->Name+"，"+b->Name+"的生命值增加了100点！";
            break;
	}



    if (b->VITNOW <= 0){
        b->VITNOW = 0;
        b->Agility=0;
    }
    if (a->VITNOW <= 0){
        a->VITNOW = 0;
        a->Agility=0;
    }
    if(a->VITNOW>a->VIT)
        a->VITNOW =a->VIT;
    if(b->VITNOW>b->VIT)
        b->VITNOW =b->VIT;
	return Description;
}

QString FightSystem::Skill(HunLing * a, QList<HunLing *> b, HunJi * skill){
    QString Description;
    skill->NowTurn += skill->Turn;
    switch (skill->ID){

    case 4:
        for(int i=0;i<b.size();i++)
            b[i]->VITNOW+=50;
        Description=a->Name+"使用技能"+skill->Name+","+"全体回复50点生命！";
    }


    for(int i=0;i<b.size();i++)
        if (b[i]->VITNOW <= 0){
            b[i]->VITNOW = 0;
            b[i]->Agility=0;
            if(b[i]->VITNOW>b[i]->VIT)
                b[i]->VITNOW = b[i]->VIT;
        }


    if (a->VITNOW <= 0){
        a->VITNOW = 0;
        a->Agility=0;
    }
    if(a->VITNOW>a->VIT)
        a->VITNOW =a->VIT;
    return Description;
}


QString FightSystem::UseItem(int a, HunLing * b,HunLing* c){
	QString Description;
	switch (a)
	{
    case 2:
		{
        double ATKPoint=0;
        ATKPoint=((b->G_Fire)/100+1)*(b->ATK)-(c->K_Fire/100+1)*(c->DEF);
        if (ATKPoint < 0)
            return b->Name+"的攻击太低了！起不了作用！";
        c->VITNOW -= ATKPoint*1.20;
        Description=b->Name+"对"+c->Name+"使用道具"+"，"+"对对方"+c->Name+"造成"+QString::number(ATKPoint)+"点伤害！";

			break;
		}
    case 4:
        {
        c->VITNOW+=500;
        Description=b->Name+"对"+c->Name+"使用道具"+"，"+"恢复了500点生命！";

            break;
        }

	}


    if (b->VITNOW <= 0){
        b->VITNOW = 0;
        b->Agility=0;
    }
    if (c->VITNOW <= 0){
        c->VITNOW = 0;
        c->Agility=0;
    }
	return Description;

}


QString FightSystem::UseItem(int a, HunLing * b, QList<HunLing *> c){
    QString Description;
    switch (a)
    {
    case 3:
        {
        double ATKPoint=0;
        for(int i=0;i<c.size();i++){
        ATKPoint=((b->G_Lig)/100+1)*(b->ATK)-(c[i]->K_Fire/100+1)*(c[i]->DEF);
        if (ATKPoint < 0)
            continue;
        c[i]->VITNOW -= ATKPoint*1.50;
        }
        Description=b->Name+"对对方全体使用道具"+"，"+"对对方全体造成大量伤害！";

            break;
        }
    case 5:
        {
        for(int i=0;i<c.size();i++)
        c[i]->ATK += 100;

        Description=b->Name+"使用道具"+"，"+"我方全体增加100点攻击！";

            break;
        }
    }


    for(int i=0;i<c.size();i++)
        if (c[i]->VITNOW <= 0){
            c[i]->VITNOW = 0;
            c[i]->Agility=0;
        }

    if (b->VITNOW <= 0){
        b->VITNOW = 0;
        b->Agility=0;
    }
    return Description;
}



void FightSystem::SetBuff(){
    for (int i = 0; i < Me->myBuffList.size(); i++){//注意！通过人物的BuffList来更新
        int a = Me->myBuffList[i].ID;
        switch (a){
        case 3:
            for(int i=0;i<EnemyHL.size();i++)
                EnemyHL[i]->DEF-=50;
                break;
        case 4:
            for(int i=0;i<MyHL.size();i++)
                MyHL[i]->ATK+=200;
                break;
        }
    }

    for (int i = 0; i < Enemy->myBuffList.size(); i++){
        int a = Enemy->myBuffList[i].ID;
        switch (a){
        case 3:
            for(int i=0;i<MyHL.size();i++)
                MyHL[i]->DEF-=50;
                break;
        case 4:
            for(int i=0;i<EnemyHL.size();i++)
                EnemyHL[i]->ATK+=200;
                break;
        }
    }

    for(int i=0;i<MyHL.size();i++){
        MyHL[i]->VIT = (Me->Vitality+MyHL[i]->Strength) * MyHL[i]->VIT_Vit * MyHL[i]->LV;
            MyHL[i]->VITNOW=MyHL[i]->VIT;
    }
        for(int i=0;i<EnemyHL.size();i++){
         EnemyHL[i]->VIT = (Enemy->Vitality+EnemyHL[i]->Strength) * EnemyHL[i]->VIT_Vit * EnemyHL[i]->LV;
             EnemyHL[i]->VITNOW=EnemyHL[i]->VIT;
        }


}

#endif









