
#include <QString>
#include "HL_DiTu.h"
#include "HL_HunJi.h"
#include "HL_HunLing.h"
#include "HL_Item.h"
#include "HL_LingGu.h"
#include "HL_LingHuan.h"
#include "HL_Task.h"
	class RenWu
{
  public:
	int LV;
	double Exp_Now;
	double Exp_Need;
	QString Name;
	double Coin;
	int PosX;
	int PosY;
	double Strength;
	double Agility;
	double Vitality;
	double Energy;
	double Sour;
	double Ori_Strength;
	double Ori_Agility;
	double Ori_Vitality;
	double Ori_Energy;
	double Ori_Sour;
	LGList LG;
	LHList LH;
	ItemList Bag;
	TaskList myTaskList;
	BuffList myBuffList;
	LGBagList LGBag;
	LHBagList LHBag;
  public:
	int UpdateLV();
	void ExceptTask(Task a);
	bool IsHaveTaskFinish();
	void FinishTask(Task a);
	void UseItem(Item a);
	int WearLH(LingHuan a);
	int WearLG(LingGu a);
    void TakeoffLH(int a);
    void TakeoffLG(int a);

	void UpdateBuff();
    void Save();//还没写其他，保存
    void Init();//还没写其他，读取
}God;

    void RenWu::Save()
    {
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
        for(int i=1;i<=LH.Count();i++)
        in<<LH.GetData(i).Name<<" "<<LH.GetData(i).Des<<" "<<LH.GetData(i).Col<<endl;
        for(int i=1;i<=myTaskList.Count();i++)
        in<<myTaskList.GetData(i).Name<<" "<<myTaskList.GetData(i).Des<<endl;
        for(int i=1;i<=LGBag.Count();i++)
        in<<LGBag.GetData(i).Name<<endl;
        for(int i=1;i<=LHBag.Count();i++)
        in<<LHBag.GetData(i).Name<<" "<<LHBag.GetData(i).Des<<" "<<LHBag.GetData(i).Col<<endl;
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

for(int i=1;i<=LH.Count();i++)
{
    LingHuan temp=LH.GetData(i);
    tmpfile.write(( char *)&temp.LV,a);
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&temp.DEF_Ski,a);
    tmpfile.write(( char *)&temp.Value,b);
    tmpfile.write(( char *)&temp.Strength,b);
    tmpfile.write(( char *)&temp.Agility,b);

}

for(int i=1;i<=Bag.Count();i++)
{
    Item temp=Bag.GetData(i);
    int abc=Bag.GetCount(i);
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&abc,a);
}


for(int i=1;i<=myTaskList.Count();i++)
{
    Task temp=myTaskList.GetData(i);
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&temp.Need_ID,a);
    tmpfile.write(( char *)&temp.IsFinish,a);
    tmpfile.write(( char *)&temp.MB,a);
    tmpfile.write(( char *)&temp.FMB,a);
    tmpfile.write(( char *)&temp.NKillHL,a);
    tmpfile.write(( char *)&temp.NKillNPC,a);
    tmpfile.write(( char *)&temp.NTalkNPC,a);
    tmpfile.write(( char *)&temp.NGetItem,a);
    tmpfile.write(( char *)&temp.A_Coin,a);
    tmpfile.write(( char *)&temp.A_Exp,a);
    tmpfile.write(( char *)&temp.A_Item,a);
    tmpfile.write(( char *)&temp.A_Count,a);
}

for(int i=1;i<=myBuffList.Count();i++)
{
    Buff temp=myBuffList.GetData(i);
    tmpfile.write(( char *)&temp.ID,a);
}

for(int i=1;i<=LGBag.Count();i++)
{
    LingGu temp=LGBag.GetData(i);
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

for(int i=1;i<=LHBag.Count();i++)
{
    LingHuan temp=LHBag.GetData(i);
    tmpfile.write(( char *)&temp.LV,a);
    tmpfile.write(( char *)&temp.ID,a);
    tmpfile.write(( char *)&temp.DEF_Ski,a);
    tmpfile.write(( char *)&temp.Value,b);
    tmpfile.write(( char *)&temp.Strength,b);
    tmpfile.write(( char *)&temp.Agility,b);
}

    tmpfile.close();
    }

void RenWu::Init()
    {
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
        for(int i=1;i<=LH.Count();i++)
        {
            LingHuan temp;
        in>>temp.Name>>temp.Des>>temp.Col;
        LH.Insert(temp);
        }
        for(int i=1;i<=myTaskList.Count();i++)
        {
            Task temp;
        in>>temp.Name>>temp.Des;
        myTaskList.Insert(temp);
        }
        for(int i=1;i<=LGBag.Count();i++)
        {
            LingGu temp;
        in>>temp.Name;
        LGBag.Insert(temp);
        }
        for(int i=1;i<=LHBag.Count();i++)
        {
            LingHuan temp;
        in>>temp.Name>>temp.Des>>temp.Col;
        LHBag.Insert(temp);
        }
        file.close();

     QFile tmpfile( DATAPATH+"SaveMe.num" );
    tmpfile.open(QIODevice::ReadOnly);

    int a=sizeof(int);
    int b=sizeof(double);
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

for(int i=1;i<=LH.Count();i++)
{
    LingHuan temp=LH.GetData(i);
    tmpfile.read(( char *)&temp.LV,a);
    tmpfile.read(( char *)&temp.ID,a);
    tmpfile.read(( char *)&temp.DEF_Ski,a);
    tmpfile.read(( char *)&temp.Value,b);
    tmpfile.read(( char *)&temp.Strength,b);
    tmpfile.read(( char *)&temp.Agility,b);
    LH.Replace(temp,i);

}

for(int i=1;i<=Bag.Count();i++)
{
    Item temp;
    int abc;
    tmpfile.read(( char *)&temp.ID,a);
    tmpfile.read(( char *)&abc,a);
    for(int j=1;j<=abc;j++)
    Bag.Insert(temp);
}


for(int i=1;i<=myTaskList.Count();i++)
{
    Task temp=myTaskList.TakeByIndex(i);
    tmpfile.read(( char *)&temp.ID,a);
    tmpfile.read(( char *)&temp.Need_ID,a);
    tmpfile.read(( char *)&temp.IsFinish,a);
    tmpfile.read(( char *)&temp.MB,a);
    tmpfile.read(( char *)&temp.FMB,a);
    tmpfile.read(( char *)&temp.NKillHL,a);
    tmpfile.read(( char *)&temp.NKillNPC,a);
    tmpfile.read(( char *)&temp.NTalkNPC,a);
    tmpfile.read(( char *)&temp.NGetItem,a);
    tmpfile.read(( char *)&temp.A_Coin,a);
    tmpfile.read(( char *)&temp.A_Exp,a);
    tmpfile.read(( char *)&temp.A_Item,a);
    tmpfile.read(( char *)&temp.A_Count,a);
    myTaskList.Insert(temp);
}

for(int i=1;i<=myBuffList.Count();i++)
{
    Buff temp;
    tmpfile.read(( char *)&temp.ID,a);
    temp=SystemBuff[temp.ID];
    myBuffList.Insert(temp);
}

for(int i=1;i<=LGBag.Count();i++)
{
    LingGu temp=LGBag.Take(i);
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
LGBag.Insert(temp);
}

for(int i=1;i<=LHBag.Count();i++)
{
    LingHuan temp=LHBag.Take(i);
    tmpfile.read(( char *)&temp.LV,a);
    tmpfile.read(( char *)&temp.ID,a);
    tmpfile.read(( char *)&temp.DEF_Ski,a);
    tmpfile.read(( char *)&temp.Value,b);
    tmpfile.read(( char *)&temp.Strength,b);
    tmpfile.read(( char *)&temp.Agility,b);
    LHBag.Insert(temp);
}

    tmpfile.close();
    }

int RenWu::UpdateLV()//返回升了多少级
{
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
	return sum;
}

void RenWu::ExceptTask(Task a)//接受任务
{
	myTaskList.Insert(a);
}

bool RenWu::IsHaveTaskFinish()//判断是否有任务已完成
{
	for (int i = 1; i <= myTaskList.Count(); i++)
		if (myTaskList.GetData(i).FMB >= myTaskList.GetData(i).MB)
			return true;
	return false;

}

void RenWu::FinishTask(Task a)//完成任务并获得奖励（记得删除任务）
{
	SystemTask[a.ID].IsFinish = 1;
	Exp_Now += a.A_Exp;
	Coin += a.A_Coin;
	if (a.A_Item != 0)
		for (int i = 1; i <= a.A_Count; i++)
			Bag.Insert(SystemItem[a.A_Item]);
}

void RenWu::UseItem(Item a)//战前使用道具，只有这些效果
{
	Ori_Strength += a.Str;
	Ori_Agility += a.Agi;
	Ori_Vitality += a.Vit;
	Ori_Energy += a.Ene;
	Ori_Sour += a.Sour;
	Exp_Now += a.Exp;
	UpdateLV();//判断LV
}

int RenWu::WearLH(LingHuan a)//穿灵环，等级不足返回-1，需求不够返回0，1返回成功,2返回相同
{
    for(int i=1;i<=LH.Count();i++)
        if(LH.GetData(i).ID==a.ID)
            return 2;
	if (LV % 10 <= LH.Count())
		return -1;
	else
	{
		if (Ori_Strength < a.Strength || Ori_Agility < a.Agility)
			return 0;
		else
			LH.Insert(a);
		return 1;
	}
}

int RenWu::WearLG(LingGu a)//穿灵骨,-1已有灵骨，0需求不足，1成功
{
	
	if (Ori_Strength < a.Strength || Ori_Agility < a.Agility)
		return 0;
	else
	{
		switch (a.Type)
		{
		case 1:
			{
				if(LG.Head.LV!=0)
				return -1;
				LG.Head = a;
				break;
			}
		case 2:
			{
				if(LG.Body.LV!=0)
				return -1;
				LG.Body = a;
				break;
			}
		case 3:
			{
                if(LG.LHand.LV!=0)
				return -1;
				LG.LHand = a;
				break;
			}
		case 4:
			{
				if(LG.RHand.LV!=0)
				return -1;
				LG.RHand = a;
				break;
			}
		case 5:
			{
				if(LG.LLeg.LV!=0)
				return -1;
				LG.LLeg = a;
				break;
			}
		case 6:
			{
				if(LG.RLeg.LV!=0)
				return -1;
				LG.RLeg = a;
				break;
			}
		}
		return 1;
	}
}

void RenWu::TakeoffLH(int a)//a is ID
{
    for(int i=1;i<=LH.Count();i++)
        if(LH.GetData(i).ID==a)
            LH.Remove(i);
}

void RenWu::TakeoffLG(int a)// a is Type
{
    switch (a)
    {
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

void RenWu::UpdateBuff()//更新战前Buff
{
	myBuffList.Clear();
	Strength = Ori_Strength;
	Agility = Ori_Agility;
	Vitality = Ori_Vitality;
	Energy = Ori_Energy;
	Sour = Ori_Sour;
	for (int i = 1; i <= LH.Count(); i++)
		myBuffList.Insert(SystemBuff[LH.GetData(i).DEF_Ski]);
	myBuffList.Insert(SystemBuff[LG.Head.DEF_Ski]);
	myBuffList.Insert(SystemBuff[LG.Body.DEF_Ski]);
	myBuffList.Insert(SystemBuff[LG.LHand.DEF_Ski]);
	myBuffList.Insert(SystemBuff[LG.RHand.DEF_Ski]);
	myBuffList.Insert(SystemBuff[LG.LLeg.DEF_Ski]);
	myBuffList.Insert(SystemBuff[LG.RLeg.DEF_Ski]);

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

	for (int i = 1; i <= myBuffList.Count(); i++)
	{
		int a = myBuffList.GetData(i).ID;
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
	}
}
