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
    HLList* Me;
    HLList* Enemy;
    QList<double> List;//敌人再自己
    double totle;//能量最大值
    int type;// 敌人还是自己,0敌人1自己
    int index;
public:
    EnergyBar(HLList* a,HLList* b);
    ~EnergyBar(){}
    void next();

};
EnergyBar::EnergyBar(HLList* a,HLList* b){
    Enemy=b;
    Me=a;
    totle=0;
    for(int i=0;i<Enemy->Count();i++){//统计能量最大值
        totle+=Enemy->GetData(i).Agility*500;
        List.append(Enemy->GetData(i).Agility);
    }
    for(int i=0;i<Me->Count();i++){
        totle+=Me->GetData(i).Agility*500;
        List.append(Me->GetData(i).Agility);
    }
    type=0;
    index=0;
}

void EnergyBar::next(){
    int stop=0;
    while(stop!=1){
        for(int i=0;i<=List.size();i++){
            if(i<Enemy->Count())//判断是加敌人还是自己的敏捷值
            List[i]+=Enemy->GetData(i).Agility;
            else
            List[i]+=Me->GetData(i-Enemy->Count()).Agility;
        }
   for(int i=0;i<=List.size();i++){
   if(List[i]>=totle){//如果大于能量最大值
       List[i]-=totle;//循环
       if(i>Me->Count()){
           type=0;
           index=i-Me->Count();
       }
       else{
           type=1;
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
    HLList* MyHL;
    HLList* EnemyHL;
    EnergyBar* EB;
	int Turn;
  public:
	void SetBuff();//初始化后自动调用，设置Buff效果
    FightSystem(RenWu* a, NPC* b,HLList* a1,HLList* b1);
	void TurnOut();				// 技能-1
	QString Attack(HunLing * a, HunLing * b);//攻击
    QString Skill(HunLing * a, HunLing* b, HunJi * skill);//技能，直接传入技能。单体。
    QString Skill(HunLing * a, HLList *b, HunJi * skill);//技能，直接传入技能。全体。注意replace
    QString UseItem(int a, HunLing * b, HunLing *c);//用道具，道具编号。
    QString UseItem(int a, HunLing * b, HLList *c);//用道具，道具编号。全体，注意replace

	int CanGoOn();				// 判断能否继续
	void UpdateATKDEF();//每轮前调用，更新攻击和防御力和体力
};



FightSystem::FightSystem(RenWu* a, NPC *b, HLList *a1, HLList *b1){
    Me = a;
    Enemy= b;
    MyHL=a1;
    EnemyHL=b1;
	Turn = 1;
    EB=new EnergyBar(MyHL,EnemyHL);
	SetBuff();
}

void FightSystem::SetBuff(){
    for (int i = 0; i < Me->myBuffList.Count(); i++){//注意！通过人物的BuffList来更新
		int a = Me->myBuffList.GetData(i).ID;
		switch (a){
		case 1:
				break;
		case 2:
				break;
		}
	}

    for (int i = 0; i < Enemy->myBuffList.Count(); i++){
        int a = Enemy->myBuffList.GetData(i).ID;
		switch (a){
		case 1:
				break;
		case 2:
				break;
		}
	}

}

void FightSystem::TurnOut(){// 技能冷却-1
    Turn++;
    for (int i = 0; i < MyHL->Count(); i++){
        HunLing temp = MyHL->GetData(i);
		temp.ATK_Ski.NowTurn--;
		if (temp.ATK_Ski.NowTurn < 0)
			temp.ATK_Ski.NowTurn = 0;
        MyHL->Replace(temp, i);
	}
    for (int i = 0; i < EnemyHL->Count(); i++){
        HunLing temp = EnemyHL->GetData(i);
		temp.ATK_Ski.NowTurn--;
		if (temp.ATK_Ski.NowTurn < 0)
			temp.ATK_Ski.NowTurn = 0;
        EnemyHL->Replace(temp, i);
	}
    UpdateATKDEF();
}

int FightSystem::CanGoOn(){// 判断能否继续。0我输，1继续，-1赢了,-2平局
    if(Turn>=30)
        return -2;
	int n = 0;
    for (int i = 1; i <= MyHL->Count(); i++)
        if (MyHL->GetData(i).VIT != 0)
			n = 1;

	if (n == 1){
		n = -1;
        for (int i = 1; i <= EnemyHL->Count(); i++)
            if (EnemyHL->GetData(i).VIT != 0)
				n = 1;
	}
    return n;//注意初始化掉落
}

QString FightSystem::Attack(HunLing * a, HunLing * b){
    double ATKPoint = a->ATK - b->DEF;//以后要优化
	if (ATKPoint < 0)
		return a->Name+"的攻击太低了！起不了作用！";
    else{
        b->VIT -= ATKPoint;//important
		if (b->VIT <= 0)
			b->VIT = 0;
		return a->Name+"对对方"+b->Name+"造成"+QString::number(ATKPoint)+"点伤害！";
	}
}

QString FightSystem::Skill(HunLing * a, HunLing * b, HunJi * skill){//注意技能类型！和体力小于0(敏捷制0)
	QString Description;
	skill->NowTurn += skill->Turn;
	switch (skill->ID){
	case 1:
			break;
	case 2:
			break;
	}



    if (b->VIT <= 0){
        b->VIT = 0;
        b->Agility=0;
    }
    if (a->VIT <= 0){
        a->VIT = 0;
        a->Agility=0;
    }
	return Description;
}

QString FightSystem::Skill(HunLing * a, HLList* b, HunJi * skill){
    QString Description;
    skill->NowTurn += skill->Turn;
    switch (skill->ID){
    case 1:
            break;
    case 2:
            break;
    }


    for(int i=0;i<b->Count();i++)
        if (b->List[i].VIT <= 0){
            b->List[i].VIT = 0;
            b->List[i].Agility=0;
        }

    if (a->VIT <= 0){
        a->VIT = 0;
        a->Agility=0;
    }
    return Description;
}


QString FightSystem::UseItem(int a, HunLing * b,HunLing* c){
	QString Description;
	switch (a)
	{
	case 1:
		{
			break;
		}
	case 2:
		{
			break;
		}
	}


    if (b->VIT <= 0){
        b->VIT = 0;
        b->Agility=0;
    }
    if (c->VIT <= 0){
        c->VIT = 0;
        c->Agility=0;
    }
	return Description;

}


QString FightSystem::UseItem(int a, HunLing * b,HLList* c){
    QString Description;
    switch (a)
    {
    case 1:
        {
            break;
        }
    case 2:
        {
            break;
        }
    }


    for(int i=0;i<c->Count();i++)
        if (c->List[i].VIT <= 0){
            c->List[i].VIT = 0;
            c->List[i].Agility=0;
        }

    if (b->VIT <= 0){
        b->VIT = 0;
        b->Agility=0;
    }
    return Description;
}


void FightSystem::UpdateATKDEF(){
    for(int i=0;i<MyHL->Count();i++){
        HunLing tempHL=MyHL->GetData(i);
        tempHL.ATK =(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.ATK_Str + tempHL.Agility * tempHL.ATK_Agi);
        tempHL.DEF =(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.DEF_Str + tempHL.Agility * tempHL.DEF_Agi);
        MyHL->Replace(tempHL,i);
	}
        for(int i=0;i<EnemyHL->Count();i++){
        HunLing tempHL=EnemyHL->GetData(i);
		tempHL.ATK =(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.ATK_Str +tempHL.Agility * tempHL.ATK_Agi);
		tempHL.DEF =(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.DEF_Str +tempHL.Agility * tempHL.DEF_Agi);
        EnemyHL->Replace(tempHL,i);
	}
}

#endif









