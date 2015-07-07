#define SAVEPATH QString("./Save/")
#define DATAPATH QString("./Data/")
#include <QString>
#include<QTextStream>

#include "HL_RenWu.h"
#include "HL_NPC.h"
#include "HL_FightSystem.h"
class DropData//掉落的东西
{
  public:
	int Exp;
	int Coin;
	ItemList Item;
	LGBagList LG;
	LHBagList LH;
};

class GameSystem
{

  public:
	RenWu Me;
  public:
    ~GameSystem()
    {

    }

    static LingGu CreateLG(HunLing a,int type);
    static LingHuan CreateLH(HunLing a);
   static NPC CreateNPC(LHList a);
    static LHList CreateLHList(DiTu a);
    static bool CanExcept(Task a,RenWu* b);
	bool CanGoTo(DiTu a);
	void FinishTask(Task & a, HunLing b);
	void FinishTask(Task & a, NPC b, int type);
    static MessageList CanTalkList(NPC a,RenWu* b);
    static TaskList CanExceptList(NPC a,RenWu* b);
    static NPCList CanShowList(DiTu a,RenWu* b);
    static DropData DropItem(HLList a);

};

LingHuan GameSystem::CreateLH(HunLing a)//生成灵环
{
	LingHuan temp;
	temp.LV = a.LV;
	temp.Name = a.Name;
	temp.Des = a.Des;
	if (temp.LV > 0 && temp.LV < 20)
		temp.Col = "白";
	if (temp.LV >= 20 && temp.LV < 40)
		temp.Col = "黄";
	if (temp.LV >= 40 && temp.LV < 60)
		temp.Col = "紫";
	if (temp.LV >= 60 && temp.LV < 80)
		temp.Col = "黑";
	if (temp.LV >= 80 && temp.LV < 90)
		temp.Col = "红";
	if (temp.LV >= 90 && temp.LV < 95)
		temp.Col = "橙";
	if (temp.LV >= 95 && temp.LV < 100)
		temp.Col = "金";
	temp.Strength = a.Strength;
	temp.Agility = a.Agility;
	temp.ID = a.ID;
	temp.DEF_Ski = a.DEF_Ski;
	return temp;
}

LingGu GameSystem::CreateLG(HunLing a,int type)//生成灵骨
{
	LingGu temp;
	temp.ID=a.ID;
	temp.LV = a.LV - 2 + GetNumber(2, 4);//-2～2的波动
	temp.Type = type;
	switch (temp.Type)
	{
	case 1:
		{
			temp.Name = a.Name + "之头盖骨";
			break;
		}
	case 2:
		{
			temp.Name = a.Name + "之躯干骨";
			break;
		}
	case 3:
		{
			temp.Name = a.Name + "之左臂骨";
			break;
		}
	case 4:
		{
			temp.Name = a.Name + "之右臂骨";
			break;
		}
	case 5:
		{
			temp.Name = a.Name + "之左腿骨";
			break;
		}
	case 6:
		{
			temp.Name = a.Name + "之右腿骨";
			break;
		}
	}
	temp.Strength = a.Strength - 5 + GetNumber(5, 10);//-5～5
	temp.Agility = a.Agility - 5 + GetNumber(5, 10);
	temp.ATK_Ski = a.ATK_Ski;
	temp.Add_Str = GetNumber(5, a.LV) / 5 + GetNumber(10, a.Strength) / 10;
	temp.Add_Agi = GetNumber(5, a.LV) / 5 + GetNumber(10, a.Agility) / 10;
	temp.Value =
		(temp.Strength * 100 + temp.Agility * 100 + temp.LV * 50 +
		 temp.Add_Str * 150 + temp.Add_Agi * 150) * 1.5;
	temp.DEF_Ski = GetNumber(1, 199);//随机防御技能
	return temp;
}

 NPC GameSystem::CreateNPC(LHList a)//通过灵环列表生成NPC，为了让魂灵和NPC整合
{
	NPC temp;
	temp.LH = a;
    temp.Des="魂灵";//判断是否有灵骨技能的依据
	int tempLV = 0;
	for (int i = 1; i <= a.Count(); i++)
		tempLV += a.GetData(i).LV;
	temp.LV = tempLV / a.Count();//等级平均数

	int tempStr = 0;
	for (int i = 1; i <= a.Count(); i++)
		tempStr += a.GetData(i).Strength;
	temp.Ori_Strength = tempStr / a.Count();//平均力量

	int tempAgi = 0;
	for (int i = 1; i <= a.Count(); i++)
		tempAgi += a.GetData(i).Agility;
	temp.Ori_Agility = tempAgi / a.Count();//平均敏捷

	temp.Ori_Vitality = temp.Ori_Strength + temp.Ori_Agility;//体力等于力量加敏捷

	temp.Ori_Energy = temp.Ori_Vitality * 50 * temp.LV;//相当于无限魂力
	temp.Ori_Sour = 500;//灵力

	for (int i = 1; i <= a.Count(); i++)//插入Buff
		temp.myBuffList.Insert(SystemBuff[a.GetData(i).DEF_Ski]);

    temp.UpdateBuff();//更新战前Buff

	return temp;

}




LHList GameSystem::CreateLHList(DiTu a)//通过地图，生成灵环列表
{
    int LHCount = GetNumber(0, 9);//数量
	LHList tempList;
	for (int i = 1; i <= LHCount; i++)
	{
		LingHuan temp;
        int aaa = a.IndexHL[GetNumber(1, 9)];
		HunLing tempHL = SystemHL[aaa];
		tempHL.LV = GetNumber(a.MinLV, a.MaxLV);
		temp.LV = tempHL.LV;
        int AgiP=0;
        if(aaa!=0)
         AgiP =tempHL.LV * 5 * tempHL.Agility / (tempHL.Agility +tempHL.Strength);
		temp.Strength = tempHL.Strength + tempHL.LV * 5 - AgiP;
		temp.Agility = tempHL.Agility + AgiP;
		temp.Name = tempHL.Name;
		temp.Des = tempHL.Des;
		temp.DEF_Ski = tempHL.DEF_Ski;
		temp.ID = tempHL.ID;
		if (temp.LV > 0 && temp.LV < 20)
			temp.Col = "白";
		if (temp.LV >= 20 && temp.LV < 40)
			temp.Col = "黄";
		if (temp.LV >= 40 && temp.LV < 60)
			temp.Col = "紫";
		if (temp.LV >= 60 && temp.LV < 80)
			temp.Col = "黑";
		if (temp.LV >= 80 && temp.LV < 90)
			temp.Col = "红";
		if (temp.LV >= 90 && temp.LV < 95)
			temp.Col = "橙";
		if (temp.LV >= 95 && temp.LV < 100)
			temp.Col = "金";
		temp.Value = 0;
		tempList.Insert(temp);
	}
	return tempList;
}

bool GameSystem::CanExcept(Task a,RenWu* b)//判断能否接受任务
{
    for(int i=1;i<=b->myTaskList.Count();i++)
    if(a.ID==b->myTaskList.GetData(i).ID)
        return false;
    return SystemTask[a.Need_ID].IsFinish;


}

bool GameSystem::CanGoTo(DiTu a)//判断能否去那个地方
{
	return SystemTask[a.NTask].IsFinish;
}

void GameSystem::FinishTask(Task & a, HunLing b)//完成杀死魂灵任务+1
{
	if (a.NKillHL == b.ID)
		a.FMB++;
}

void GameSystem::FinishTask(Task & a, NPC b, int type)//完成 1杀NPC 2谈NPC +1
{
	if (type == 1)				// NTalk
		if (a.NTalkNPC == b.ID)
			a.FMB++;
	if (type == 2)
		if (a.NKillNPC == b.ID)
			a.FMB++;
}

MessageList GameSystem::CanTalkList(NPC a, RenWu *b)//返回一个NPC所能说的话的列表
{
	MessageList tempList;
	for (int i = 1; i <= 19; i++)
	{

		int aaa = a.CanTalk[i];
		if (aaa == 0)
			continue;
		if (SystemMessage[aaa].NTask == 0)
		{
			tempList.Insert(SystemMessage[aaa]);
			continue;
		}
		Task temp = SystemTask[SystemMessage[aaa].NTask];//说话所需任务
        for (int j = 1; j <= b->myTaskList.Count(); j++)
		{
            if (b->myTaskList.GetData(j).ID == temp.ID)
				tempList.Insert(SystemMessage[aaa]);
		}



	}
	return tempList;
}

TaskList GameSystem::CanExceptList(NPC a, RenWu *b)//返回当前可以接受的任务列表
{
	TaskList tempList;
	for (int i = 1; i <= a.myTaskList.Count(); i++)
	{
		Task temp = a.myTaskList.GetData(i);
        if (temp.IsFinish == 0 && CanExcept(temp,b) == true)
			tempList.Insert(temp);
	}
	return tempList;
}

NPCList GameSystem::CanShowList(DiTu a, RenWu *b)//返回目前可以显示的NPC
{
	NPCList tempList;
    for (int i = 1; i <= 9; i++)
	{
        for(int j=1;j<=b->myTaskList.Count();j++)
        if (SystemNPC[a.IndexNPC[i]].TaskShow==b->myTaskList.GetData(j).ID)
			tempList.Insert(SystemNPC[a.IndexNPC[i]]);
	}
	return tempList;
}



DropData GameSystem::DropItem(HLList a)//通过魂灵列表生成掉落的东西
{
	DropData tempData;
	for (int i = 1; i <= a.Count(); i++)
	{
		HunLing temp = a.GetData(i);
		int aaa = temp.DropItem[GetNumber(1, 9)];
		tempData.Item.Insert(SystemItem[aaa]);
		tempData.Exp +=
			100 * pow(1.2, temp.LV) - (100 * pow(1.2, temp.LV - 1));
		tempData.Coin += GetNumber(temp.LV * 1.5, temp.LV * 2);
		if (GetNumber(1, 100) == 1)
		{
			LingGu tempLG = CreateLG(temp,GetNumber(1,6));
			tempData.LG.Insert(tempLG);
		}
		if (GetNumber(1, 20) == 1)
		{
			LingHuan tempLH = CreateLH(temp);
			tempData.LH.Insert(tempLH);
		}
	}
	return tempData;
}
