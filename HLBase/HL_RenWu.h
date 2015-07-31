/*人物*/
#ifndef HL_RENWU
#define HL_RENWU

#include <QString>
#include <QList>
#include<QMessageBox>
#include "HL_DiTu.h"
#include "HL_HunJi.h"
#include "HL_HunLing.h"
#include "HL_Item.h"
#include "HL_LingGu.h"
#include "HL_LingHuan.h"
#include "HL_Task.h"
class DropData{//掉落的东西
  public:
    int Exp;
    int Coin;
    QList<Item> Item;
    QList<LingGu> LG;
    QList<LingHuan> LH;
};
enum TASKTYPE
{
    KILLHL=0,
    KILLNPC=1,
    TALKNPC=2,
    GETITEM=3
};

class RenWu{
  public:
	int LV;
	double Exp_Now;
	double Exp_Need;
	QString Name;
	double Coin;
	int PosX;
	int PosY;
    int Strength;//加了buff后的数据
    int Agility;
    int Vitality;
    int Energy;
    int Sour;
    int Ori_Strength;//原始数据
    int Ori_Agility;
    int Ori_Vitality;
    int Ori_Energy;
    int Ori_Sour;
	LGList LG;
    QList<LingHuan> LH;
    QList<Item> Bag;
    QList<Task> myTaskList;
    QList<Buff> myBuffList;
    QList<LingGu> LGBag;
    QList<LingHuan> LHBag;
  public:
    int UpdateLV();//返回升了多少级
    int ExceptTask(Task a);//1接受成功，-1异常，0不能接受
    bool IsHaveTaskFinish();//判断是否有任务已完成
    int FinishTask(Task a);//1成功完成，-1异常
    void UpDateTask(int Need,TASKTYPE type);//完成任务+1
    void UseItem(Item a);//战前使用道具只有这些效果,不负责删除
    int WearLH(LingHuan a);//穿灵环，等级不足返回-1，需求不够返回0，1返回成功,2返回相同
    int WearLG(LingGu a);//穿灵骨,-1已有灵骨，0需求不足，1成功
    void TakeoffLH(LingHuan a);
    void TakeoffLG(LingGu a);
    void ExceptReward(DropData a);//接受奖励

    void UpdateBuff();//更新战前Buff
    void Save();
    void Init();
    RenWu();
};

RenWu::RenWu(){
    LV=0;Exp_Need=0;Exp_Now=0;Name="空";Coin=0;PosX=0;PosY=0;
    Strength=0;Agility=0;Vitality=0;Energy=0;Sour=0;
    Ori_Strength=0;Ori_Agility=0;Ori_Vitality=0;Ori_Energy=0;Ori_Sour=0;
}

void RenWu::ExceptReward(DropData a){
    Exp_Now+=a.Exp;
    Coin+=a.Coin;
    for(int i=0;i<a.Item.size();i++){
        int stop=0;
       for(int j=0;j<Bag.size();j++)
          if(Bag[j].ID==a.Item[i].ID){
              Bag[j].Count++;
              stop=1;
              break;
          }
       if(stop==0){
       Bag.append(a.Item[i]);
       Bag.last().Count=1;
       }
    }
    for(int i=0;i<a.LG.size();i++)
       LGBag.append(a.LG[i]);

    for(int i=0;i<a.LH.size();i++)
       LHBag.append(a.LH[i]);
    int UL=UpdateLV();
    if(UL>0)
       QMessageBox::about(NULL,"提示","恭喜！你升级了！");
}

void RenWu::UpDateTask(int Need,TASKTYPE type){
    for(int i=0;i<myTaskList.size();i++){
        switch(type){
        case KILLHL:
            if(myTaskList[i].NKillHL==Need)
                myTaskList[i].FMB++;
            break;
        case KILLNPC:
            if(myTaskList[i].NKillNPC==Need){
                myTaskList[i].FMB++;
                }
            break;
        case TALKNPC:
            if(myTaskList[i].NTalkNPC==Need)
                myTaskList[i].FMB++;
            break;
        case GETITEM:
            if(myTaskList[i].NGetItem==Need)
                for(int j=0;j<Bag.size();j++)
                    if(Bag[i].ID==Need)
                        myTaskList[i].FMB=Bag[j].Count;
            break;
        }
    }

}

void RenWu::Save(){
        QFile file((DATAPATH+"SaveMe.str"));
        file.open(QIODevice::WriteOnly);
        QTextStream in(&file);
        in<<Name<<endl;
        in<<LG.Head.Name<<endl;
        in<<LG.Body.Name<<endl;
        in<<LG.LHand.Name<<endl;
        in<<LG.RHand.Name<<endl;
        in<<LG.LLeg.Name<<endl;
        in<<LG.RLeg.Name<<endl;

        for(int i=0;i<LH.size();i++)
        in<<LH[i].Name<<" "<<LH[i].Des<<" "<<LH[i].Col<<endl;



        for(int i=0;i<LGBag.size();i++)
        in<<LGBag[i].Name<<endl;

        for(int i=0;i<LHBag.size();i++)
        in<<LHBag[i].Name<<" "<<LHBag[i].Des<<" "<<LHBag[i].Col<<endl;

        file.close();

     QFile tmpfile( DATAPATH+"SaveMe.num" );
    tmpfile.open(QIODevice::WriteOnly);
    int a=sizeof(int);
    int b=sizeof(double);
    tmpfile.write(( char *)&LV,a);
    tmpfile.write(( char *)&Exp_Now,b);
    tmpfile.write(( char *)&Exp_Need,b);
    tmpfile.write(( char *)&Coin,b);
    tmpfile.write(( char *)&PosX,a);
    tmpfile.write(( char *)&PosY,a);
    tmpfile.write(( char *)&Strength,a);
    tmpfile.write(( char *)&Agility,a);
    tmpfile.write(( char *)&Vitality,a);
    tmpfile.write(( char *)&Energy,a);
    tmpfile.write(( char *)&Sour,a);
    tmpfile.write(( char *)&Ori_Strength,a);
    tmpfile.write(( char *)&Ori_Agility,a);
    tmpfile.write(( char *)&Ori_Vitality,a);
    tmpfile.write(( char *)&Ori_Energy,a);
    tmpfile.write(( char *)&Ori_Sour,a);

tmpfile.write(( char *)&LG.Head.LV,a);
tmpfile.write(( char *)&LG.Body.LV,a);
tmpfile.write(( char *)&LG.LHand.LV,a);
tmpfile.write(( char *)&LG.RHand.LV,a);
tmpfile.write(( char *)&LG.LLeg.LV,a);
tmpfile.write(( char *)&LG.RLeg.LV,a);

tmpfile.write(( char *)&LG.Head.ID,a);
tmpfile.write(( char *)&LG.Body.ID,a);
tmpfile.write(( char *)&LG.LHand.ID,a);
tmpfile.write(( char *)&LG.RHand.ID,a);
tmpfile.write(( char *)&LG.LLeg.ID,a);
tmpfile.write(( char *)&LG.RLeg.ID,a);

tmpfile.write(( char *)&LG.Head.Type,a);
tmpfile.write(( char *)&LG.Body.Type,a);
tmpfile.write(( char *)&LG.LHand.Type,a);
tmpfile.write(( char *)&LG.RHand.Type,a);
tmpfile.write(( char *)&LG.LLeg.Type,a);
tmpfile.write(( char *)&LG.RLeg.Type,a);

tmpfile.write(( char *)&LG.Head.Value,a);
tmpfile.write(( char *)&LG.Body.Value,a);
tmpfile.write(( char *)&LG.LHand.Value,a);
tmpfile.write(( char *)&LG.RHand.Value,a);
tmpfile.write(( char *)&LG.LLeg.Value,a);
tmpfile.write(( char *)&LG.RLeg.Value,a);

tmpfile.write(( char *)&LG.Head.Strength,a);
tmpfile.write(( char *)&LG.Body.Strength,a);
tmpfile.write(( char *)&LG.LHand.Strength,a);
tmpfile.write(( char *)&LG.RHand.Strength,a);
tmpfile.write(( char *)&LG.LLeg.Strength,a);
tmpfile.write(( char *)&LG.RLeg.Strength,a);

tmpfile.write(( char *)&LG.Head.Agility,a);
tmpfile.write(( char *)&LG.Body.Agility,a);
tmpfile.write(( char *)&LG.LHand.Agility,a);
tmpfile.write(( char *)&LG.RHand.Agility,a);
tmpfile.write(( char *)&LG.LLeg.Agility,a);
tmpfile.write(( char *)&LG.RLeg.Agility,a);

tmpfile.write(( char *)&LG.Head.DEF_Ski,a);
tmpfile.write(( char *)&LG.Body.DEF_Ski,a);
tmpfile.write(( char *)&LG.LHand.DEF_Ski,a);
tmpfile.write(( char *)&LG.RHand.DEF_Ski,a);
tmpfile.write(( char *)&LG.LLeg.DEF_Ski,a);
tmpfile.write(( char *)&LG.RLeg.DEF_Ski,a);

tmpfile.write(( char *)&LG.Head.ATK_Ski.ID,a);
tmpfile.write(( char *)&LG.Body.ATK_Ski.ID,a);
tmpfile.write(( char *)&LG.LHand.ATK_Ski.ID,a);
tmpfile.write(( char *)&LG.RHand.ATK_Ski.ID,a);
tmpfile.write(( char *)&LG.LLeg.ATK_Ski.ID,a);
tmpfile.write(( char *)&LG.RLeg.ATK_Ski.ID,a);

tmpfile.write(( char *)&LG.Head.Add_Str,a);
tmpfile.write(( char *)&LG.Body.Add_Str,a);
tmpfile.write(( char *)&LG.LHand.Add_Str,a);
tmpfile.write(( char *)&LG.RHand.Add_Str,a);
tmpfile.write(( char *)&LG.LLeg.Add_Str,a);
tmpfile.write(( char *)&LG.RLeg.Add_Str,a);

tmpfile.write(( char *)&LG.Head.Add_Agi,a);
tmpfile.write(( char *)&LG.Body.Add_Agi,a);
tmpfile.write(( char *)&LG.LHand.Add_Agi,a);
tmpfile.write(( char *)&LG.RHand.Add_Agi,a);
tmpfile.write(( char *)&LG.LLeg.Add_Agi,a);
tmpfile.write(( char *)&LG.RLeg.Add_Agi,a);

for(int i=0;i<LH.size();i++){
    LingHuan temp=LH[i];
    tmpfile.write(( char *)&temp.LV,a);
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&temp.DEF_Ski,a);
    tmpfile.write(( char *)&temp.Value,a);
    tmpfile.write(( char *)&temp.Strength,a);
    tmpfile.write(( char *)&temp.Agility,a);

}

for(int i=0;i<Bag.size();i++){
    Item temp=Bag[i];
    int abc=Bag[i].Count;
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&abc,a);
}


for(int i=0;i<myTaskList.size();i++){
    Task temp=myTaskList[i];
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&temp.FMB,a);
}

for(int i=0;i<LGBag.size();i++){
    LingGu temp=LGBag[i];
tmpfile.write(( char *)&temp.LV,a);
tmpfile.write(( char *)&temp.ID,a);
tmpfile.write(( char *)&temp.Type,a);
tmpfile.write(( char *)&temp.Value,a);
tmpfile.write(( char *)&temp.Strength,a);
tmpfile.write(( char *)&temp.Agility,a);
tmpfile.write(( char *)&temp.DEF_Ski,a);
tmpfile.write(( char *)&temp.ATK_Ski.ID,a);
tmpfile.write(( char *)&temp.Add_Str,a);
tmpfile.write(( char *)&temp.Add_Agi,a);
}

for(int i=0;i<LHBag.size();i++){
    LingHuan temp=LHBag[i];
    tmpfile.write(( char *)&temp.LV,a);
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&temp.DEF_Ski,a);
    tmpfile.write(( char *)&temp.Value,a);
    tmpfile.write(( char *)&temp.Strength,a);
    tmpfile.write(( char *)&temp.Agility,a);
}

    tmpfile.close();


    QFile file1(DATAPATH+"SaveMe.siz" );
   file1.open(QIODevice::WriteOnly);

   int s=LH.size();
   file1.write(( char *)&s,a);
   s=Bag.size();
   file1.write(( char *)&s,a);
   s=myTaskList.size();
   file1.write(( char *)&s,a);
   s=LGBag.size();
   file1.write(( char *)&s,a);
   s=LHBag.size();
   file1.write(( char *)&s,a);

}

void RenWu::Init(){
    int a=sizeof(int);
    int b=sizeof(double);
    QFile file1(DATAPATH+"SaveMe.siz" );
   file1.open(QIODevice::ReadOnly);

   int LH_SIZE;
   file1.read(( char *)&LH_SIZE,a);
   int BAG_SIZE;
   file1.read(( char *)&BAG_SIZE,a);
   int MYTASKLIST_SIZE;
   file1.read(( char *)&MYTASKLIST_SIZE,a);
   int LGBAG_SIZE;
   file1.read(( char *)&LGBAG_SIZE,a);
   int LHBAG_SIZE;
   file1.read(( char *)&LHBAG_SIZE,a);

   file1.close();

        QFile file((DATAPATH+"SaveMe.str"));
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);
        in>>Name;
        in>>LG.Head.Name;
        in>>LG.Body.Name;
        in>>LG.LHand.Name;
        in>>LG.RHand.Name;
        in>>LG.LLeg.Name;
        in>>LG.RLeg.Name;

        for(int i=0;i<LH_SIZE;i++){
            LingHuan temp;
        in>>temp.Name>>temp.Des>>temp.Col;
        LH.append(temp);
        }


        for(int i=0;i<LGBAG_SIZE;i++){
            LingGu temp;
        in>>temp.Name;
        LGBag.append(temp);
        }
        for(int i=0;i<LHBAG_SIZE;i++){
            LingHuan temp;
        in>>temp.Name>>temp.Des>>temp.Col;
        LHBag.append(temp);
        }
        file.close();

     QFile tmpfile( DATAPATH+"SaveMe.num" );
    tmpfile.open(QIODevice::ReadOnly);
    tmpfile.read(( char *)&LV,a);
    tmpfile.read(( char *)&Exp_Now,b);
    tmpfile.read(( char *)&Exp_Need,b);
    tmpfile.read(( char *)&Coin,b);
    tmpfile.read(( char *)&PosX,a);
    tmpfile.read(( char *)&PosY,a);
    tmpfile.read(( char *)&Strength,a);
    tmpfile.read(( char *)&Agility,a);
    tmpfile.read(( char *)&Vitality,a);
    tmpfile.read(( char *)&Energy,a);
    tmpfile.read(( char *)&Sour,a);
    tmpfile.read(( char *)&Ori_Strength,a);
    tmpfile.read(( char *)&Ori_Agility,a);
    tmpfile.read(( char *)&Ori_Vitality,a);
    tmpfile.read(( char *)&Ori_Energy,a);
    tmpfile.read(( char *)&Ori_Sour,a);

tmpfile.read(( char *)&LG.Head.LV,a);
tmpfile.read(( char *)&LG.Body.LV,a);
tmpfile.read(( char *)&LG.LHand.LV,a);
tmpfile.read(( char *)&LG.RHand.LV,a);
tmpfile.read(( char *)&LG.LLeg.LV,a);
tmpfile.read(( char *)&LG.RLeg.LV,a);

tmpfile.read(( char *)&LG.Head.ID,a);
tmpfile.read(( char *)&LG.Body.ID,a);
tmpfile.read(( char *)&LG.LHand.ID,a);
tmpfile.read(( char *)&LG.RHand.ID,a);
tmpfile.read(( char *)&LG.LLeg.ID,a);
tmpfile.read(( char *)&LG.RLeg.ID,a);

tmpfile.read(( char *)&LG.Head.Type,a);
tmpfile.read(( char *)&LG.Body.Type,a);
tmpfile.read(( char *)&LG.LHand.Type,a);
tmpfile.read(( char *)&LG.RHand.Type,a);
tmpfile.read(( char *)&LG.LLeg.Type,a);
tmpfile.read(( char *)&LG.RLeg.Type,a);

tmpfile.read(( char *)&LG.Head.Value,a);
tmpfile.read(( char *)&LG.Body.Value,a);
tmpfile.read(( char *)&LG.LHand.Value,a);
tmpfile.read(( char *)&LG.RHand.Value,a);
tmpfile.read(( char *)&LG.LLeg.Value,a);
tmpfile.read(( char *)&LG.RLeg.Value,a);

tmpfile.read(( char *)&LG.Head.Strength,a);
tmpfile.read(( char *)&LG.Body.Strength,a);
tmpfile.read(( char *)&LG.LHand.Strength,a);
tmpfile.read(( char *)&LG.RHand.Strength,a);
tmpfile.read(( char *)&LG.LLeg.Strength,a);
tmpfile.read(( char *)&LG.RLeg.Strength,a);

tmpfile.read(( char *)&LG.Head.Agility,a);
tmpfile.read(( char *)&LG.Body.Agility,a);
tmpfile.read(( char *)&LG.LHand.Agility,a);
tmpfile.read(( char *)&LG.RHand.Agility,a);
tmpfile.read(( char *)&LG.LLeg.Agility,a);
tmpfile.read(( char *)&LG.RLeg.Agility,a);

tmpfile.read(( char *)&LG.Head.DEF_Ski,a);
tmpfile.read(( char *)&LG.Body.DEF_Ski,a);
tmpfile.read(( char *)&LG.LHand.DEF_Ski,a);
tmpfile.read(( char *)&LG.RHand.DEF_Ski,a);
tmpfile.read(( char *)&LG.LLeg.DEF_Ski,a);
tmpfile.read(( char *)&LG.RLeg.DEF_Ski,a);

tmpfile.read(( char *)&LG.Head.ATK_Ski.ID,a);
tmpfile.read(( char *)&LG.Body.ATK_Ski.ID,a);
tmpfile.read(( char *)&LG.LHand.ATK_Ski.ID,a);
tmpfile.read(( char *)&LG.RHand.ATK_Ski.ID,a);
tmpfile.read(( char *)&LG.LLeg.ATK_Ski.ID,a);
tmpfile.read(( char *)&LG.RLeg.ATK_Ski.ID,a);

LG.Head.ATK_Ski=SystemHJ[LG.Head.ATK_Ski.ID];
LG.Body.ATK_Ski=SystemHJ[LG.Body.ATK_Ski.ID];
LG.LHand.ATK_Ski=SystemHJ[LG.LHand.ATK_Ski.ID];
LG.RHand.ATK_Ski=SystemHJ[LG.RHand.ATK_Ski.ID];
LG.LLeg.ATK_Ski=SystemHJ[LG.LLeg.ATK_Ski.ID];
LG.RLeg.ATK_Ski=SystemHJ[LG.RLeg.ATK_Ski.ID];



tmpfile.read(( char *)&LG.Head.Add_Str,a);
tmpfile.read(( char *)&LG.Body.Add_Str,a);
tmpfile.read(( char *)&LG.LHand.Add_Str,a);
tmpfile.read(( char *)&LG.RHand.Add_Str,a);
tmpfile.read(( char *)&LG.LLeg.Add_Str,a);
tmpfile.read(( char *)&LG.RLeg.Add_Str,a);

tmpfile.read(( char *)&LG.Head.Add_Agi,a);
tmpfile.read(( char *)&LG.Body.Add_Agi,a);
tmpfile.read(( char *)&LG.LHand.Add_Agi,a);
tmpfile.read(( char *)&LG.RHand.Add_Agi,a);
tmpfile.read(( char *)&LG.LLeg.Add_Agi,a);
tmpfile.read(( char *)&LG.RLeg.Add_Agi,a);

for(int i=0;i<LH_SIZE;i++){
    LingHuan temp=LH[i];
    tmpfile.read(( char *)&temp.LV,a);
    tmpfile.read(( char *)&temp.ID,a);
    tmpfile.read(( char *)&temp.DEF_Ski,a);
    tmpfile.read(( char *)&temp.Value,a);
    tmpfile.read(( char *)&temp.Strength,a);
    tmpfile.read(( char *)&temp.Agility,a);
    LH[i]=temp;
}

for(int i=0;i<BAG_SIZE;i++){
    Item temp;
    tmpfile.read(( char *)&temp.ID,a);
    temp=SystemItem[temp.ID];
    tmpfile.read(( char *)&temp.Count,a);
    Bag.append(temp);
}


for(int i=0;i<MYTASKLIST_SIZE;i++){
    Task temp;
    tmpfile.read(( char *)&temp.ID,a);
    temp=SystemTask[temp.ID];
    tmpfile.read(( char *)&temp.FMB,a);
    myTaskList.append(temp);
}

for(int i=0;i<LGBAG_SIZE;i++){
    LingGu temp=LGBag[i];
tmpfile.read(( char *)&temp.LV,a);
tmpfile.read(( char *)&temp.ID,a);
tmpfile.read(( char *)&temp.Type,a);
tmpfile.read(( char *)&temp.Value,a);
tmpfile.read(( char *)&temp.Strength,a);
tmpfile.read(( char *)&temp.Agility,a);
tmpfile.read(( char *)&temp.DEF_Ski,a);
tmpfile.read(( char *)&temp.ATK_Ski.ID,a);
temp.ATK_Ski=SystemHJ[temp.ATK_Ski.ID];
tmpfile.read(( char *)&temp.Add_Str,a);
tmpfile.read(( char *)&temp.Add_Agi,a);
LGBag[i]=temp;
}

for(int i=0;i<LHBAG_SIZE;i++){
    LingHuan temp=LHBag[i];
    tmpfile.read(( char *)&temp.LV,a);
    tmpfile.read(( char *)&temp.ID,a);
    tmpfile.read(( char *)&temp.DEF_Ski,a);
    tmpfile.read(( char *)&temp.Value,a);
    tmpfile.read(( char *)&temp.Strength,a);
    tmpfile.read(( char *)&temp.Agility,a);
    LHBag[i]=temp;
}

    tmpfile.close();
    UpdateBuff();
}

int RenWu::UpdateLV(){
	int sum = 0;
	while (Exp_Now >= Exp_Need)
		if (Exp_Now >= Exp_Need)
		{
            sum += 1;
			LV++;
            Exp_Now=Exp_Now-Exp_Need;
            Exp_Need = (((LV-1)*(LV-1)*(LV-1)+60)/25)*((LV-1)+60);//等级公式
            Ori_Strength+=2;
            Ori_Agility+=2;
            Ori_Vitality+=1;
            Ori_Energy=Ori_Energy+50;
            Ori_Sour+=1;
		}
    UpdateBuff();
	return sum;
}


int RenWu::ExceptTask(Task a){
    if(a.ID==0)
        return -1;

    for(int i=0;i<myTaskList.size();i++)
       if(myTaskList[i].ID==a.ID)
          return 0;
    myTaskList.append(a);
    return 1;
}

bool RenWu::IsHaveTaskFinish(){
    for (int i = 0; i <myTaskList.size(); i++)
        if (myTaskList[i].FMB >= myTaskList[i].MB)
			return true;
	return false;
}

int RenWu::FinishTask(Task a){
    if(a.ID==0)
        return -1;
    else{
	SystemTask[a.ID].IsFinish = 1;
    for(int i=0;i<myTaskList.size();i++)//删除
    if(myTaskList[i].ID==a.ID)
        myTaskList.removeAt(i);

    for(int i=0;i<Bag.size();i++)//删除任务道具
    if(Bag[i].ID==a.NGetItem&&a.NGetItem!=0)
        for(int j=0;j<a.MB;j++)
        Bag[i].Count--;


	Exp_Now += a.A_Exp;
    int UL=UpdateLV();
    if(UL>0)
       QMessageBox::about(NULL,"提示","恭喜！你升级了！");
	Coin += a.A_Coin;
    if (a.A_Item != 0){
        int stop=0;
        for (int i = 1; i <= a.A_Count; i++){
            for(int i=0;i<Bag.size();i++)
                if(Bag[i].ID==SystemItem[a.A_Item].ID){
                    Bag[i].Count++;
                    stop=1;
                    break;
                    }
        }
        if(stop==0){
            Bag.append(SystemItem[a.A_Item]);
            Bag.last().Count=a.A_Count;
        }
        return 1;
    }
    }
    return -1;
}

void RenWu::UseItem(Item a)
{
	Ori_Strength += a.Str;
	Ori_Agility += a.Agi;
	Ori_Vitality += a.Vit;
	Ori_Energy += a.Ene;
	Ori_Sour += a.Sour;
	Exp_Now += a.Exp;

    for(int i=0;i<Bag.size();i++)
        if(a.ID==Bag[i].ID){
            if(Bag[i].Count>1)
                Bag[i].Count--;
            else
                Bag.removeAt(i);
        }

    int UL=UpdateLV();
    if(UL>0)
       QMessageBox::about(NULL,"提示","恭喜！你升级了！");
}

int RenWu::WearLH(LingHuan a){
    for(int i=0;i<LH.size();i++)
        if(LH[i].ID==a.ID)
            return 2;

    if ((int(LV/10)+1) <= LH.size())
		return -1; 
	else{
		if (Ori_Strength < a.Strength || Ori_Agility < a.Agility)
			return 0;
        else{
           LH.append(a);
           for(int j=0;j<LHBag.size();j++)
               if(a.ID==LHBag[j].ID&&a.Value==LHBag[j].Value)
                   LHBag.removeAt(j);
        }

		return 1;
	}
}

int RenWu::WearLG(LingGu a){

	if (Ori_Strength < a.Strength || Ori_Agility < a.Agility)
		return 0;
	else{
		switch (a.Type){
		case 1:
				if(LG.Head.LV!=0)
				return -1;
				LG.Head = a;
				break;
		case 2:
				if(LG.Body.LV!=0)
				return -1;
				LG.Body = a;
				break;
		case 3:
                if(LG.LHand.LV!=0)
				return -1;
				LG.LHand = a;
				break;
		case 4:
				if(LG.RHand.LV!=0)
				return -1;
				LG.RHand = a;
				break;
		case 5:
				if(LG.LLeg.LV!=0)
				return -1;
				LG.LLeg = a;
				break;
		case 6:
				if(LG.RLeg.LV!=0)
				return -1;
				LG.RLeg = a;
				break;
		}
        for(int i=0;i<LGBag.size();i++)
            if(a.ID==LGBag[i].ID&&a.Value==LGBag[i].Value)
                LGBag.removeAt(i);
		return 1;
	}
}


void RenWu::TakeoffLH(LingHuan a){
    for(int i=0;i<LH.size();i++)
        if(LH[i].ID==a.ID&&a.Value==LH[i].Value){
            LH.removeAt(i);
            LHBag.append(a);
            break;
        }

}

void RenWu::TakeoffLG(LingGu a){
    switch (a.Type){
    case 1:
        LG.Head.clear();
            break;
    case 2:
        LG.Body.clear();
            break;
    case 3:
        LG.LHand.clear();
            break;
    case 4:
        LG.RHand.clear();
            break;
    case 5:
        LG.LLeg.clear();
            break;
    case 6:
        LG.RLeg.clear();
            break;
    }
    LGBag.append(a);
}

void RenWu::UpdateBuff(){
    myBuffList.clear();
	Strength = Ori_Strength;
	Agility = Ori_Agility;
	Vitality = Ori_Vitality;

    for (int i = 0; i <LH.size(); i++){
        if(LH[i].ID!=0)
        myBuffList.append(SystemBuff[LH[i].DEF_Ski]);
    }
    if(LG.Head.ID!=0)
    myBuffList.append(SystemBuff[LG.Head.DEF_Ski]);
    if(LG.Body.ID!=0)
    myBuffList.append(SystemBuff[LG.Body.DEF_Ski]);
    if(LG.LHand.ID!=0)
    myBuffList.append(SystemBuff[LG.LHand.DEF_Ski]);
    if(LG.RHand.ID!=0)
    myBuffList.append(SystemBuff[LG.RHand.DEF_Ski]);
    if(LG.LLeg.ID!=0)
    myBuffList.append(SystemBuff[LG.LLeg.DEF_Ski]);
    if(LG.RLeg.ID!=0)
    myBuffList.append(SystemBuff[LG.RLeg.DEF_Ski]);

	Strength += LG.Head.Add_Str;
	Agility += LG.Head.Add_Agi;
	Strength += LG.Body.Add_Str;
	Agility += LG.Body.Add_Agi;
	Strength += LG.LLeg.Add_Str;
	Agility += LG.LLeg.Add_Agi;
	Strength += LG.RLeg.Add_Str;
	Agility += LG.RLeg.Add_Agi;
	Strength += LG.RHand.Add_Str;
	Agility += LG.RHand.Add_Agi;
	Strength += LG.LHand.Add_Str;
    Agility += LG.LHand.Add_Agi;

    for (int i = 0; i < myBuffList.size(); i++){
        int a = myBuffList[i].ID;
		switch (a){
        case 3:
            Vitality+=20;
				break;
        case 6:
            Vitality+=20;
				break;
        case 9:
            Strength+=10;
                break;
        case 10:
            Agility+=10;
                break;
        case 11:
            Vitality+=10;
                break;

		}
	}
}

#endif
