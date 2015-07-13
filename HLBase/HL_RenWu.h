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

class RenWu{
  public:
	int LV;
	double Exp_Now;
	double Exp_Need;
	QString Name;
	double Coin;
	int PosX;
	int PosY;
    double Strength;//加了buff后的数据
	double Agility;
	double Vitality;
	double Energy;
	double Sour;
    double Ori_Strength;//原始数据
	double Ori_Agility;
	double Ori_Vitality;
	double Ori_Energy;
	double Ori_Sour;
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
    void UseItem(Item a);//战前使用道具只有这些效果,不负责删除
    int WearLH(LingHuan a);//穿灵环，等级不足返回-1，需求不够返回0，1返回成功,2返回相同
    int WearLG(LingGu a);//穿灵骨,-1已有灵骨，0需求不足，1成功
    void TakeoffLH(int a);//a is ID
    void TakeoffLG(int a);// a is Type

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

        for(int i=0;i<myTaskList.size();i++)
        in<<myTaskList[i].Name<<" "<<myTaskList[i].Des<<endl;

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
    tmpfile.write(( char *)&Strength,b);
    tmpfile.write(( char *)&Agility,b);
    tmpfile.write(( char *)&Vitality,b);
    tmpfile.write(( char *)&Energy,b);
    tmpfile.write(( char *)&Sour,b);
    tmpfile.write(( char *)&Ori_Strength,b);
    tmpfile.write(( char *)&Ori_Agility,b);
    tmpfile.write(( char *)&Ori_Vitality,b);
    tmpfile.write(( char *)&Ori_Energy,b);
    tmpfile.write(( char *)&Ori_Sour,b);

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

tmpfile.write(( char *)&LG.Head.Value,b);
tmpfile.write(( char *)&LG.Body.Value,b);
tmpfile.write(( char *)&LG.LHand.Value,b);
tmpfile.write(( char *)&LG.RHand.Value,b);
tmpfile.write(( char *)&LG.LLeg.Value,b);
tmpfile.write(( char *)&LG.RLeg.Value,b);

tmpfile.write(( char *)&LG.Head.Strength,b);
tmpfile.write(( char *)&LG.Body.Strength,b);
tmpfile.write(( char *)&LG.LHand.Strength,b);
tmpfile.write(( char *)&LG.RHand.Strength,b);
tmpfile.write(( char *)&LG.LLeg.Strength,b);
tmpfile.write(( char *)&LG.RLeg.Strength,b);

tmpfile.write(( char *)&LG.Head.Agility,b);
tmpfile.write(( char *)&LG.Body.Agility,b);
tmpfile.write(( char *)&LG.LHand.Agility,b);
tmpfile.write(( char *)&LG.RHand.Agility,b);
tmpfile.write(( char *)&LG.LLeg.Agility,b);
tmpfile.write(( char *)&LG.RLeg.Agility,b);

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

tmpfile.write(( char *)&LG.Head.Add_Str,b);
tmpfile.write(( char *)&LG.Body.Add_Str,b);
tmpfile.write(( char *)&LG.LHand.Add_Str,b);
tmpfile.write(( char *)&LG.RHand.Add_Str,b);
tmpfile.write(( char *)&LG.LLeg.Add_Str,b);
tmpfile.write(( char *)&LG.RLeg.Add_Str,b);

tmpfile.write(( char *)&LG.Head.Add_Agi,b);
tmpfile.write(( char *)&LG.Body.Add_Agi,b);
tmpfile.write(( char *)&LG.LHand.Add_Agi,b);
tmpfile.write(( char *)&LG.RHand.Add_Agi,b);
tmpfile.write(( char *)&LG.LLeg.Add_Agi,b);
tmpfile.write(( char *)&LG.RLeg.Add_Agi,b);

for(int i=0;i<LH.size();i++){
    LingHuan temp=LH[i];
    tmpfile.write(( char *)&temp.LV,a);
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&temp.DEF_Ski,a);
    tmpfile.write(( char *)&temp.Value,b);
    tmpfile.write(( char *)&temp.Strength,b);
    tmpfile.write(( char *)&temp.Agility,b);

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
tmpfile.write(( char *)&temp.Value,b);
tmpfile.write(( char *)&temp.Strength,b);
tmpfile.write(( char *)&temp.Agility,b);
tmpfile.write(( char *)&temp.DEF_Ski,a);
tmpfile.write(( char *)&temp.ATK_Ski.ID,a);
tmpfile.write(( char *)&temp.Add_Str,b);
tmpfile.write(( char *)&temp.Add_Agi,b);
}

for(int i=0;i<LHBag.size();i++){
    LingHuan temp=LHBag[i];
    tmpfile.write(( char *)&temp.LV,a);
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&temp.DEF_Ski,a);
    tmpfile.write(( char *)&temp.Value,b);
    tmpfile.write(( char *)&temp.Strength,b);
    tmpfile.write(( char *)&temp.Agility,b);
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
    tmpfile.read(( char *)&Strength,b);
    tmpfile.read(( char *)&Agility,b);
    tmpfile.read(( char *)&Vitality,b);
    tmpfile.read(( char *)&Energy,b);
    tmpfile.read(( char *)&Sour,b);
    tmpfile.read(( char *)&Ori_Strength,b);
    tmpfile.read(( char *)&Ori_Agility,b);
    tmpfile.read(( char *)&Ori_Vitality,b);
    tmpfile.read(( char *)&Ori_Energy,b);
    tmpfile.read(( char *)&Ori_Sour,b);

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

tmpfile.read(( char *)&LG.Head.Value,b);
tmpfile.read(( char *)&LG.Body.Value,b);
tmpfile.read(( char *)&LG.LHand.Value,b);
tmpfile.read(( char *)&LG.RHand.Value,b);
tmpfile.read(( char *)&LG.LLeg.Value,b);
tmpfile.read(( char *)&LG.RLeg.Value,b);

tmpfile.read(( char *)&LG.Head.Strength,b);
tmpfile.read(( char *)&LG.Body.Strength,b);
tmpfile.read(( char *)&LG.LHand.Strength,b);
tmpfile.read(( char *)&LG.RHand.Strength,b);
tmpfile.read(( char *)&LG.LLeg.Strength,b);
tmpfile.read(( char *)&LG.RLeg.Strength,b);

tmpfile.read(( char *)&LG.Head.Agility,b);
tmpfile.read(( char *)&LG.Body.Agility,b);
tmpfile.read(( char *)&LG.LHand.Agility,b);
tmpfile.read(( char *)&LG.RHand.Agility,b);
tmpfile.read(( char *)&LG.LLeg.Agility,b);
tmpfile.read(( char *)&LG.RLeg.Agility,b);

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

tmpfile.read(( char *)&LG.Head.Add_Str,b);
tmpfile.read(( char *)&LG.Body.Add_Str,b);
tmpfile.read(( char *)&LG.LHand.Add_Str,b);
tmpfile.read(( char *)&LG.RHand.Add_Str,b);
tmpfile.read(( char *)&LG.LLeg.Add_Str,b);
tmpfile.read(( char *)&LG.RLeg.Add_Str,b);

tmpfile.read(( char *)&LG.Head.Add_Agi,b);
tmpfile.read(( char *)&LG.Body.Add_Agi,b);
tmpfile.read(( char *)&LG.LHand.Add_Agi,b);
tmpfile.read(( char *)&LG.RHand.Add_Agi,b);
tmpfile.read(( char *)&LG.LLeg.Add_Agi,b);
tmpfile.read(( char *)&LG.RLeg.Add_Agi,b);

for(int i=0;i<LH_SIZE;i++){
    LingHuan temp=LH[i];
    tmpfile.read(( char *)&temp.LV,a);
    tmpfile.read(( char *)&temp.ID,a);
    tmpfile.read(( char *)&temp.DEF_Ski,a);
    tmpfile.read(( char *)&temp.Value,b);
    tmpfile.read(( char *)&temp.Strength,b);
    tmpfile.read(( char *)&temp.Agility,b);
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
    LingGu temp;
tmpfile.read(( char *)&temp.LV,a);
tmpfile.read(( char *)&temp.ID,a);
tmpfile.read(( char *)&temp.Type,a);
tmpfile.read(( char *)&temp.Value,b);
tmpfile.read(( char *)&temp.Strength,b);
tmpfile.read(( char *)&temp.Agility,b);
tmpfile.read(( char *)&temp.DEF_Ski,a);
tmpfile.read(( char *)&temp.ATK_Ski.ID,a);
temp.ATK_Ski=SystemHJ[temp.ATK_Ski.ID];
tmpfile.read(( char *)&temp.Add_Str,b);
tmpfile.read(( char *)&temp.Add_Agi,b);
LGBag.append(temp);
}

for(int i=0;i<LHBAG_SIZE;i++){
    LingHuan temp;
    tmpfile.read(( char *)&temp.LV,a);
    tmpfile.read(( char *)&temp.ID,a);
    tmpfile.read(( char *)&temp.DEF_Ski,a);
    tmpfile.read(( char *)&temp.Value,b);
    tmpfile.read(( char *)&temp.Strength,b);
    tmpfile.read(( char *)&temp.Agility,b);
    LHBag.append(temp);
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
            Exp_Need = 100 * pow(1.2, LV + 1);//等级公式
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
        if(myTaskList[i].ID==0){
            myTaskList[i]=a;
            return 1;
            }
    for(int i=0;i<myTaskList.size();i++)
       if(myTaskList[i].ID==a.ID){
          return 0;
}

return -1;
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

	Exp_Now += a.A_Exp;
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
    int UL=UpdateLV();
    if(UL>0)
       QMessageBox::about(NULL,"提示","恭喜！你升级了！");
}

int RenWu::WearLH(LingHuan a){
    for(int i=0;i<LH.size();i++)
        if(LH[i].ID==a.ID)
            return 2;

    if (int(LV/10) <= LH.size())
		return -1; 
	else{
		if (Ori_Strength < a.Strength || Ori_Agility < a.Agility)
			return 0;
		else
           LH.append(a);

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
		return 1;
	}
}


void RenWu::TakeoffLH(int a){
    for(int i=0;i<LH.size();i++)
        if(LH[i].ID==a)
            LH.removeAt(i);
}

void RenWu::TakeoffLG(int a){
    switch (a){
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
}

void RenWu::UpdateBuff(){
    myBuffList.clear();
	Strength = Ori_Strength;
	Agility = Ori_Agility;
	Vitality = Ori_Vitality;
	Energy = Ori_Energy;
	Sour = Ori_Sour;
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
	Agility += LG.RHand.Add_Agi;

    for (int i = 0; i < myBuffList.size(); i++){
        int a = myBuffList[i].ID;
		switch (a){
		case 1:
				break;
		case 2:
				break;
		}
	}
}

#endif
