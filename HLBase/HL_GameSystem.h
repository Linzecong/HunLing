#ifndef HL_GAMESYSTEM
#define HL_GAMESYSTEM
#define SAVEPATH QString("./Save/")
#define DATAPATH QString("./Data/")

#include <QString>
#include<QTextStream>
#include<QFile>
#include<QList>
#include "HL_RenWu.h"
#include "HL_NPC.h"
#include "HL_FightSystem.h"
#include "HL_LingHuan.h"

class DropData{//掉落的东西
  public:
	int Exp;
	int Coin;
    QList<Item> Item;
    QList<LingGu> LG;
    QList<LingHuan> LH;
};

class GameSystem{
  public:
	RenWu Me;
  public:
    GameSystem(){
       SystemMap[0][0].Init();
        SystemHJ[0].Init();
        SystemHL[0].Init();
        SystemItem[0].Init();
        SystemNPC[0].Init();
        SystemTask[0].Init();
        SystemMessage[0].Init();
        SystemBuff[0].Init();
      //  Me.Init();


        // 测试用
        Me.LV=45;
        Me.Exp_Need=100;
        Me.Exp_Now=10;
        Me.Name="傻逼";
        Me.Coin=100000000;
        Me.PosX=1;
        Me.PosY=1;
        Me.Ori_Agility=10;
        Me.Ori_Energy=100;
        Me.Ori_Strength=10;
        Me.Ori_Vitality=100;
        Me.Ori_Sour=100;
        SystemHL[1].LV=80;
        LingHuan a=CreateLH(SystemHL[1]);
        Me.LH.append(a);
        SystemHL[2].LV=20;
        a=CreateLH(SystemHL[2]);
        Me.LH.append(a);
        Me.Bag.append(SystemItem[1]);
        Me.Bag.append(SystemItem[2]);
        SystemHL[3].LV=60;
        a=CreateLH(SystemHL[3]);
        Me.LHBag.append(a);
        Me.UpdateBuff();



       // -----*/

    }

    static LingGu CreateLG(HunLing a,int type);
    static LingHuan CreateLH(HunLing a);
    static NPC CreateNPC(QList<LingHuan> a);
    static QList<LingHuan> CreateLHList(DiTu a);
    static bool CanExcept(Task a,RenWu* b);
	bool CanGoTo(DiTu a);

    static QList<Message> CanTalkList(NPC a,RenWu* b);
    static QList<Task> CanExceptList(NPC a,RenWu* b);
    static QList<NPC> CanShowList(DiTu a,RenWu* b);
    static DropData DropItem(QList<HunLing> a);
    template <class T>
    static HunLing CreatHL(T a,LingHuan b){
        HunLing tempHL = SystemHL[b.ID];
        tempHL.LV = b.LV;
        tempHL.Strength += a.Strength;
        tempHL.Agility += a.Agility;
        tempHL.ATK =(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.ATK_Str + tempHL.Agility * tempHL.ATK_Agi);
        tempHL.DEF =(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.DEF_Str + tempHL.Agility * tempHL.DEF_Agi);
        tempHL.VIT = a.Vitality * tempHL.VIT_Vit * tempHL.LV;
        tempHL.VITNOW=tempHL.VIT;
        return tempHL;

     }

};


LingHuan GameSystem::CreateLH(HunLing a){
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

LingGu GameSystem::CreateLG(HunLing a,int type){
	LingGu temp;
	temp.ID=a.ID;
	temp.LV = a.LV - 2 + GetNumber(2, 4);//-2～2的波动
	temp.Type = type;
	switch (temp.Type){
	case 1:
			temp.Name = a.Name + "之头盖骨";
			break;
	case 2:
			temp.Name = a.Name + "之躯干骨";
			break;
	case 3:
			temp.Name = a.Name + "之左臂骨";
			break;
	case 4:
			temp.Name = a.Name + "之右臂骨";
			break;
	case 5:
			temp.Name = a.Name + "之左腿骨";
			break;
	case 6:
			temp.Name = a.Name + "之右腿骨";
			break;
	}
	temp.Strength = a.Strength - 5 + GetNumber(5, 10);//-5～5
	temp.Agility = a.Agility - 5 + GetNumber(5, 10);
	temp.ATK_Ski = a.ATK_Ski;
	temp.Add_Str = GetNumber(5, a.LV) / 5 + GetNumber(10, a.Strength) / 10;
	temp.Add_Agi = GetNumber(5, a.LV) / 5 + GetNumber(10, a.Agility) / 10;
	temp.Value =(temp.Strength * 100 + temp.Agility * 100 + temp.LV * 50 +temp.Add_Str * 150 + temp.Add_Agi * 150) * 1.5;
	temp.DEF_Ski = GetNumber(1, 199);//随机防御技能
	return temp;
}

NPC GameSystem::CreateNPC(QList<LingHuan> a){//通过灵环列表生成NPC，为了让魂灵和NPC整合
	NPC temp;
    if(a.isEmpty()==true)
        return temp;
	temp.LH = a;
    temp.Des="魂灵";//判断是否有灵骨技能的依据
	int tempLV = 0;
    for (int i = 0; i < a.size(); i++)
        tempLV += a[i].LV;
    temp.LV = tempLV / a.size();//等级平均数

	int tempStr = 0;
    for (int i = 0; i < a.size(); i++)
        tempStr += a[i].Strength;
    temp.Ori_Strength = tempStr / a.size();//平均力量

	int tempAgi = 0;
    for (int i = 0; i < a.size(); i++)
        tempAgi += a[i].Agility;
    temp.Ori_Agility = tempAgi / a.size();//平均敏捷

	temp.Ori_Vitality = temp.Ori_Strength + temp.Ori_Agility;//体力等于力量加敏捷

	temp.Ori_Energy = temp.Ori_Vitality * 50 * temp.LV;//相当于无限魂力
	temp.Ori_Sour = 500;//灵力

    temp.UpdateBuff();//更新战前Buff

	return temp;
}

QList<LingHuan> GameSystem::CreateLHList(DiTu a){//通过地图，生成灵环列表
    int LHCount = GetNumber(1, a.HLCount);//一个格子的魂灵数量
    QList<LingHuan> tempList;
	for (int i = 1; i <= LHCount; i++){
		LingHuan temp;
        int aaa = a.IndexHL[GetNumber(1, 9)];
        if(aaa==0)
            continue;
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
        tempList.append(temp);
	}
	return tempList;
}

bool GameSystem::CanExcept(Task a,RenWu* b){//判断能否接受任务
    for(int i=0;i<b->myTaskList.size();i++)
    if(a.ID==b->myTaskList[i].ID)
        return false;
    return SystemTask[a.Need_ID].IsFinish;
}

bool GameSystem::CanGoTo(DiTu a){//判断能否去那个地方
	return SystemTask[a.NTask].IsFinish;
}



QList<Message> GameSystem::CanTalkList(NPC a, RenWu *b){//返回一个NPC所能说的话的列表
    QList<Message> tempList;
    for (int i = 0; i < 20; i++){
		int aaa = a.CanTalk[i];
		if (aaa == 0)
			continue;
        Task temp = SystemTask[SystemMessage[aaa].NTask];//说话所需任务(已完成的任务)
            if (SystemTask[temp.ID].IsFinish==1){
                tempList.append(SystemMessage[aaa]);
                break;
            }
    }
	return tempList;
}

QList<Task> GameSystem::CanExceptList(NPC a, RenWu *b){//返回当前可以接受的任务列表
    QList<Task> tempList;
    for (int i = 0; i <a.myTaskList.size(); i++){
        Task temp = a.myTaskList[i];
        if (CanExcept(temp,b) == 1)
            tempList.append(temp);
	}
	return tempList;
}

QList<NPC> GameSystem::CanShowList(DiTu a, RenWu *b){//返回目前可以显示的NPC
    QList<NPC>  tempList;
    for (int i = 0; i <10; i++){
        if (SystemTask[SystemNPC[a.IndexNPC[i]].TaskShow].IsFinish==1&&a.IndexNPC[i]!=0){
            tempList.append(SystemNPC[a.IndexNPC[i]]);
            break;
        }
	}
	return tempList;
}

DropData GameSystem::DropItem(QList<HunLing> a){//通过魂灵列表生成掉落的东西,特定物品可特定判断
	DropData tempData;
    for (int i = 0; i < a.size(); i++){
        HunLing temp = a[i];

        /*特定掉落
        if(temp.ID==x)
            tempData.Item.Insert(SystemItem[aaa]);*/
        /*全局掉落*/

		int aaa = temp.DropItem[GetNumber(1, 9)];
        tempData.Item.append(SystemItem[aaa]);
		tempData.Exp +=
			100 * pow(1.2, temp.LV) - (100 * pow(1.2, temp.LV - 1));
		tempData.Coin += GetNumber(temp.LV * 1.5, temp.LV * 2);
		if (GetNumber(1, 100) == 1){
			LingGu tempLG = CreateLG(temp,GetNumber(1,6));
            tempData.LG.append(tempLG);
		}
		if (GetNumber(1, 20) == 1){
			LingHuan tempLH = CreateLH(temp);
            tempData.LH.append(tempLH);
		}

	}
	return tempData;
}

#endif
