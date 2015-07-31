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
    QString UseItem(HunLing * a, HunLing *b, int c);//用道具，道具编号。
    QString UseItem( HunLing * a, QList<HunLing*> b,int c);//用道具，道具编号。全体，注意replace
    template<class T>
    void UsedSkill(T* a,HunJi* b){
        b->NowTurn += b->Turn;
        a->Energy-=b->Energy;
        a->Sour-=b->Sour;
    }

    double ATKPoint(HunLing a,HunLing b,int type,double per){
        double Point = 0;
        switch(type){
        case 0:
            Point = (a.ATK*per*10-b.DEF*5)/30;
            break;
        case 1:
            Point = (((a.G_Fire)/100+1)*a.ATK*per*10-(b.DEF*((b.K_Fire)/100+1))*5)/30;
            break;
        case 2:
            Point = (((a.G_Ice)/100+1)*a.ATK*per*10-(b.DEF*((b.K_Ice)/100+1))*5)/30;
            break;
        case 3:
            Point = (((a.G_Lig)/100+1)*a.ATK*per*10-(b.DEF*((b.K_Lig)/100+1))*5)/30;
            break;
        case 4:
            Point = (((a.G_Tox)/100+1)*a.ATK*per*10-(b.DEF*((b.K_Tox)/100+1))*5)/30;
            break;
        default:
            Point = (a.ATK*per*10-b.DEF*5)/30;
            break;
        }

        if(Point<0)
            Point=GetNumber(1,5);
        return Point;


    }

    int CanGoOn();				// 判断能否继续
    void UpdateVIT();//每轮前调用，更新体力
};



FightSystem::FightSystem(RenWu* a, NPC *b, QList<HunLing *> a1, QList<HunLing *> b1){
    Me = a;
    Enemy= b;
    MyHL=a1;
    EnemyHL=b1;
    Turn = 1;
    for (int i = 0; i < MyHL.size(); i++)
        MyHL[i]->ATK_Ski.NowTurn=0;

    for (int i = 0; i < EnemyHL.size(); i++)
        EnemyHL[i]->ATK_Ski.NowTurn=0;

    Me->LG.Head.ATK_Ski.NowTurn=0;
    Me->LG.Body.ATK_Ski.NowTurn=0;
    Me->LG.LHand.ATK_Ski.NowTurn=0;
    Me->LG.RHand.ATK_Ski.NowTurn=0;
    Me->LG.LLeg.ATK_Ski.NowTurn=0;
    Me->LG.RLeg.ATK_Ski.NowTurn=0;
    Enemy->LG.Head.ATK_Ski.NowTurn=0;
    Enemy->LG.Body.ATK_Ski.NowTurn=0;
    Enemy->LG.LHand.ATK_Ski.NowTurn=0;
    Enemy->LG.RHand.ATK_Ski.NowTurn=0;
    Enemy->LG.LLeg.ATK_Ski.NowTurn=0;
    Enemy->LG.RLeg.ATK_Ski.NowTurn=0;

    EB=new EnergyBar(MyHL,EnemyHL);
    SetBuff();
}


void FightSystem::UpdateVIT(){
    for(int i=0;i<MyHL.size();i++){
        MyHL[i]->VIT =(((MyHL[i]->LV+MyHL[i]->VIT_Vit) * MyHL[i]->LV*Me->Vitality)+(Me->Vitality+MyHL[i]->Strength)*Me->Vitality)/(10+MyHL[i]->LV/10);
        if(MyHL[i]->VIT<MyHL[i]->VITNOW)
            MyHL[i]->VITNOW=MyHL[i]->VIT;
        if(MyHL[i]->Agility==0)
            MyHL[i]->VITNOW=0;
    }
    for(int i=0;i<EnemyHL.size();i++){
        EnemyHL[i]->VIT =(((EnemyHL[i]->LV+EnemyHL[i]->VIT_Vit) * EnemyHL[i]->LV*Enemy->Vitality)+(Enemy->Vitality+EnemyHL[i]->Strength)*Enemy->Vitality)/(10+EnemyHL[i]->LV/10);
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
    if(Me->LG.Head.ATK_Ski.NowTurn>0)
        Me->LG.Head.ATK_Ski.NowTurn--;
    if(Me->LG.Body.ATK_Ski.NowTurn>0)
        Me->LG.Body.ATK_Ski.NowTurn--;
    if(Me->LG.LHand.ATK_Ski.NowTurn>0)
        Me->LG.LHand.ATK_Ski.NowTurn--;
    if(Me->LG.RHand.ATK_Ski.NowTurn>0)
        Me->LG.RHand.ATK_Ski.NowTurn--;
    if(Me->LG.LLeg.ATK_Ski.NowTurn>0)
        Me->LG.LLeg.ATK_Ski.NowTurn--;
    if(Me->LG.RLeg.ATK_Ski.NowTurn>0)
        Me->LG.RLeg.ATK_Ski.NowTurn--;
    if(Enemy->LG.Head.ATK_Ski.NowTurn>0)
        Enemy->LG.Head.ATK_Ski.NowTurn--;
    if(Enemy->LG.Body.ATK_Ski.NowTurn>0)
        Enemy->LG.Body.ATK_Ski.NowTurn--;
    if(Enemy->LG.LHand.ATK_Ski.NowTurn>0)
        Enemy->LG.LHand.ATK_Ski.NowTurn--;
    if(Enemy->LG.RHand.ATK_Ski.NowTurn>0)
        Enemy->LG.RHand.ATK_Ski.NowTurn--;
    if(Enemy->LG.LLeg.ATK_Ski.NowTurn>0)
        Enemy->LG.LLeg.ATK_Ski.NowTurn--;
    if(Enemy->LG.RLeg.ATK_Ski.NowTurn>0)
        Enemy->LG.RLeg.ATK_Ski.NowTurn--;
    UpdateVIT();
}

int FightSystem::CanGoOn(){// 判断能否继续。0我输，1继续，-1赢了,-2平局
    if(Turn>=500)
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
    int Point=int(ATKPoint(*a,*b,0,1));
    b->VITNOW -= Point;//important
    if (b->VITNOW <= 0){
        b->VITNOW = 0;
        b->Agility=0;
    }
    return a->Name+"对对方"+b->Name+"造成"+QString::number(Point)+"点伤害！";

}

QString FightSystem::Skill(HunLing * a, HunLing * b, HunJi * skill){//注意技能类型！和体力小于0(敏捷制0)
    QString Description;

    switch (skill->ID){
    case 1:{
        int Point=int(ATKPoint(*a,*b,1,1.5));
        Point+=int(ATKPoint(*a,*b,2,1.5));
        Point+=int(ATKPoint(*a,*b,3,1.5));
        Point+=int(ATKPoint(*a,*b,4,1.5));
        Point/=4;
        b->VITNOW -= Point;//important

        Description=a->Name+"对"+b->Name+"使用技能"+skill->Name+"，"+b->Name+"对对方造成"+QString::number(Point)+"点伤害";
        break;
    }
    case 5:{
        int Point=int(ATKPoint(*a,*b,0,2));
        b->VITNOW -= Point;
        Description=a->Name+"对"+b->Name+"使用技能"+skill->Name+"，"+"对对方"+b->Name+"造成"+QString::number(Point)+"点伤害！";
    }
        break;
    case 6:{
        b->VITNOW *= 0.1;
        Description=a->Name+"对"+b->Name+"使用技能"+skill->Name+"，"+"体力将至10%";
        break;
    }
    case 8:{
        int Point=int(ATKPoint(*a,*b,1,1.5));
        b->VITNOW -= Point;
        Description=a->Name+"对"+b->Name+"使用技能"+skill->Name+"，"+"对对方"+b->Name+"造成"+QString::number(Point)+"点伤害！";
    }


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

    switch (skill->ID){

    case 2:
        foreach (HunLing* hl, b) {
            hl->DEF*=0.8;
        }
        Description=a->Name+"使用技能"+skill->Name+","+"对方全体防御降至80%";
        break;
    case 3:{

        foreach (HunLing* hl, b) {
            int Point=int(ATKPoint(*a,*hl,1,3));
            hl->VITNOW-=Point;

        }
        Description=a->Name+"使用技能"+skill->Name+","+"对对方全体造成300%火焰伤害";
        break;
    }
    case 4:{

        foreach (HunLing* hl, b) {
            hl->Agility*=0.95;
        }
        Description=a->Name+"使用技能"+skill->Name+","+"对方全体敏捷降低至95%";
        break;
    }

    case 7:{

        foreach (HunLing* hl, b) {
            hl->Agility*=0.8;
        }
        Description=a->Name+"使用技能"+skill->Name+","+"对方全体敏捷降低至80%";

        int count=0;
        for(int i=0;i<9;i++){
            int id=Enemy->LH[i].ID;
            if(id==1||id==2||id==3||id==4||id==5||id==6||id==7||id==8)
                count++;
        }
        if(count==8){
            foreach (HunLing* hl, b) {
                hl->Agility*=0.9;
            }
            Description=a->Name+"使用技能"+skill->Name+","+"对方全体敏捷降低至80%，因为控制着暗影魔龙家族！对方全体敏捷再降低至90%！！";
        }


        break;
    }

    case 9:{

        foreach (HunLing* hl, b) {
            hl->ATK*=1.1;
        }
        Description=a->Name+"使用技能"+skill->Name+","+"全体提高10%的攻击力";



        break;
    }

    case 10:{

        foreach (HunLing* hl, b) {
            int Point=int(ATKPoint(*a,*hl,1,2));
            hl->VITNOW-=Point;

        }
        Description=a->Name+"使用技能"+skill->Name+","+"对对方全体造成200%火焰伤害";
        break;
    }

    case 11:{

        foreach (HunLing* hl, b) {
            int Point=int(ATKPoint(*a,*hl,0,1.5));
            hl->VITNOW-=Point;
            hl->Agility-=30;

        }
        Description=a->Name+"使用技能"+skill->Name+","+"对对方全体造成150%伤害，并降低30点敏捷！";
        break;
    }

    case 12:{

        foreach (HunLing* hl, b) {
            int Point=int(ATKPoint(*a,*hl,1,3));
            hl->VITNOW-=Point;

        }
        Description=a->Name+"使用技能"+skill->Name+","+"对对方全体造成300%火焰伤害";
        break;
    }

    case 13:{

        foreach (HunLing* hl, b) {
            hl->Agility*=0.9;

        }
        Description=a->Name+"使用技能"+skill->Name+","+"对方全体敏捷降至90%";
        break;
    }

    case 14:{

        foreach (HunLing* hl, b) {
            hl->VITNOW=hl->VIT;
            hl->Agility=a->Agility;
        }
        Description=a->Name+"使用技能"+skill->Name+","+"牺牲自我，友方其他魂灵复活和生命值补满!!!拥有上古凤凰的敏捷值！";

        int count=0;
        for(int i=0;i<9;i++){
            int id=Me->LH[i].ID;
            if(id==10||id==11||id==12||id==13||id==14||id==15||id==16||id==17)
                count++;
        }
        if(count==8){
            foreach (HunLing* hl, b) {
                hl->Agility*=1.3;
            }
            Description=a->Name+"使用技能"+skill->Name+","+"牺牲自我，友方其他魂灵复活和生命值补满!!!拥有上古凤凰的敏捷值！因为控制着凤凰8大魂灵，敏捷值也增加30%";
        }

        a->VITNOW=0;
        break;
    }

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


QString FightSystem::UseItem(HunLing *a, HunLing * b, int c){
    QString Description;
    switch (c)
    {
    case 2:
    {
        int Point=int(ATKPoint(*a,*b,1,1.2));

        b->VITNOW -= Point;
        Description=a->Name+"对"+b->Name+"使用道具"+"，"+"对对方"+b->Name+"造成"+QString::number(Point)+"点伤害！";

        break;
    }
    case 4:
    {
        b->VITNOW+=50;
        Description=a->Name+"对"+b->Name+"使用道具"+"，"+"恢复了50点生命！";

        break;
    }

    }


    if (b->VITNOW <= 0){
        b->VITNOW = 0;
        b->Agility=0;
    }
    if (a->VITNOW <= 0){
        a->VITNOW = 0;
        a->Agility=0;
    }

    for(int i=0;i<Me->Bag.size();i++)
        if(c==Me->Bag[i].ID){
            if(Me->Bag[i].Count>1)
                Me->Bag[i].Count--;
            else
                Me->Bag.removeAt(i);
        }
    Me->UseItem(SystemItem[c]);
    return Description;

}


QString FightSystem::UseItem(HunLing *a, QList<HunLing *> b, int c){
    QString Description;
    switch (c)
    {
    case 3:
    {
        for(int i=0;i<b.size();i++){
            int Point=int(ATKPoint(*a,*b[i],3,1.5));


            b[i]->VITNOW -= Point;
        }
        Description=a->Name+"对对方全体使用道具"+"，"+"对对方全体造成大量伤害！";

        break;
    }
    case 5:
    {
        for(int i=0;i<b.size();i++)
            b[i]->ATK += 100;

        Description=a->Name+"使用道具"+"，"+"我方全体增加100点攻击！";

        break;
    }
    }

    Me->UseItem(SystemItem[c]);


    for(int i=0;i<b.size();i++)
        if (b[i]->VITNOW <= 0){
            b[i]->VITNOW = 0;
            b[i]->Agility=0;
        }

    if (a->VITNOW <= 0){
        a->VITNOW = 0;
        a->Agility=0;
    }
    return Description;
}



void FightSystem::SetBuff(){
    int stop=0;
    QList<HunLing*> MyHLtemp=MyHL;
    QList<HunLing*> EnemyHLtemp=EnemyHL;
    QList<Buff> Bufftemp=Me->myBuffList;

    while(stop<=1){
    for (int i = 0; i < Bufftemp.size(); i++){//注意！通过人物的BuffList来更新
        int a = Bufftemp[i].ID;
        switch (a){
        case 1:
            for(int i=0;i<MyHLtemp.size();i++)
                MyHLtemp[i]->DEF*=1.05;
            break;
        case 2:
            for(int i=0;i<MyHLtemp.size();i++)
                MyHLtemp[i]->ATK*=1.05;
            break;
        case 4:
            for(int i=0;i<EnemyHLtemp.size();i++)
                EnemyHLtemp[i]->ATK*=0.95;
            break;
        case 5:
            for(int i=0;i<EnemyHLtemp.size();i++)
                EnemyHLtemp[i]->DEF*=0.95;
            break;
        case 7:
            for(int i=0;i<MyHLtemp.size();i++)
                MyHLtemp[i]->ATK*=1.1;
            break;
        case 8:
            for(int i=0;i<MyHLtemp.size();i++)
                MyHLtemp[i]->K_Fire+=10;
            break;
        case 12:
            for(int i=0;i<MyHLtemp.size();i++)
                MyHLtemp[i]->G_Fire+=20;
            break;

        }
    }
    stop++;
    MyHLtemp.clear();
    EnemyHLtemp.clear();
    QList<HunLing*> temp=MyHLtemp;
    MyHLtemp=EnemyHLtemp;
    EnemyHLtemp=temp;
    }
    UpdateVIT();

}

#endif









