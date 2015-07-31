#ifndef HL_GAMESYSTEM
#define HL_GAMESYSTEM


#include <QString>
#include<QTextStream>
#include<QFile>
#include<QList>
#include "HL_RenWu.h"
#include "HL_NPC.h"
#include "HL_FightSystem.h"
#include "HL_LingHuan.h"



class GameSystem{
  public:
	RenWu Me;
  public:
    GameSystem(){
        SystemMap[0][0].Init();
        SystemHJ[0].Init();
        SystemHL[0].Init();
        SystemItem[0].Init();
        SystemTask[0].Init();
        SystemMessage[0].Init();
        SystemBuff[0].Init();
        SystemNPC[0].Init();
       // Me.Init();



        Me.LV=98;
        Me.Exp_Need=100000;
        Me.Exp_Now=0;
        Me.Name="酱油A";
        Me.Coin=10;
        Me.PosX=1;
        Me.PosY=1;
        Me.Ori_Agility=260;
        Me.Ori_Energy=5000;
        Me.Ori_Strength=260;
        Me.Ori_Vitality=110;
        Me.Ori_Sour=200;

        LingHuan a;
        a.LV=93;
        a.ID=10;
        a.DEF_Ski=8;
        a.Name=SystemHL[10].Name;
        a.Des=SystemHL[10].Des;
        a.Col="彩";
        a.Value=9999;
        a.Strength=SystemHL[10].Strength+a.LV*2;
        a.Agility=SystemHL[10].Agility+a.LV*2;
        Me.LH.append(a);

        a.LV=93;
        a.ID=11;
        a.DEF_Ski=8;
        a.Name=SystemHL[11].Name;
        a.Des=SystemHL[11].Des;
        a.Strength=SystemHL[11].Strength+a.LV*2;
        a.Agility=SystemHL[11].Agility+a.LV*2;
        Me.LH.append(a);

        a.LV=93;
        a.ID=12;
        a.DEF_Ski=9;
        a.Name=SystemHL[12].Name;
        a.Des=SystemHL[12].Des;
        a.Strength=SystemHL[12].Strength+a.LV*2;
        a.Agility=SystemHL[12].Agility+a.LV*2;
        Me.LH.append(a);

        a.LV=93;
        a.ID=13;
        a.DEF_Ski=9;
        a.Name=SystemHL[13].Name;
        a.Des=SystemHL[13].Des;
        a.Strength=SystemHL[13].Strength+a.LV*2;
        a.Agility=SystemHL[13].Agility+a.LV*2;
        Me.LH.append(a);

        a.LV=94;
        a.ID=14;
        a.DEF_Ski=10;
        a.Name=SystemHL[14].Name;
        a.Des=SystemHL[14].Des;
        a.Strength=SystemHL[14].Strength+a.LV*2;
        a.Agility=SystemHL[14].Agility+a.LV*2;
        Me.LH.append(a);

        a.LV=94;
        a.ID=15;
        a.DEF_Ski=9;
        a.Name=SystemHL[15].Name;
        a.Des=SystemHL[15].Des;
        a.Strength=SystemHL[15].Strength+a.LV*2;
        a.Agility=SystemHL[15].Agility+a.LV*2;
        Me.LH.append(a);

        a.LV=95;
        a.ID=16;
        a.DEF_Ski=10;
        a.Name=SystemHL[16].Name;
        a.Des=SystemHL[16].Des;
        a.Strength=SystemHL[16].Strength+a.LV*2;
        a.Agility=SystemHL[16].Agility+a.LV*2;
        Me.LH.append(a);

        a.LV=95;
        a.ID=17;
        a.DEF_Ski=11;
        a.Name=SystemHL[17].Name;
        a.Des=SystemHL[17].Des;
        a.Strength=SystemHL[17].Strength+a.LV*2;
        a.Agility=SystemHL[17].Agility+a.LV*2;
        Me.LH.append(a);

        a.LV=99;
        a.ID=18;
        a.DEF_Ski=12;
        a.Name=SystemHL[18].Name;
        a.Des=SystemHL[18].Des;
        a.Strength=SystemHL[18].Strength+a.LV*2;
        a.Agility=SystemHL[18].Agility+a.LV*2;
        Me.LH.append(a);




        Me.UpdateBuff();






       // -----*/

    }

    static LingGu CreateLG(HunLing a,int type);
    static LingHuan CreateLH(HunLing a);
    static NPC CreateNPC(QList<LingHuan> a);
    static QList<LingHuan> CreateLHList(DiTu a);
    static bool CanExcept(Task a,RenWu* b);
	bool CanGoTo(DiTu a);
    static bool IsTaskFinish(Task a);//判断此任务是否已完成
    static QList<Message> CanTalkList(NPC a,RenWu* b);
    static QList<Task> CanExceptList(NPC a,RenWu* b);
    static QList<NPC> CanShowList(DiTu a);
    static DropData DropItem(QList<HunLing> a);
    template <class T>
    static HunLing CreatHL(T a,LingHuan b){
        HunLing tempHL = SystemHL[b.ID];
        tempHL.LV = b.LV;
        tempHL.Strength = a.Strength+b.Strength;
        tempHL.Agility = a.Agility+b.Agility;
        tempHL.ATK =(tempHL.LV+10) * (tempHL.Strength * (tempHL.ATK_Str+10) + tempHL.Agility * (tempHL.ATK_Agi+10))/(100+tempHL.LV/5);
        tempHL.DEF =(tempHL.LV+10) * (tempHL.Strength * (tempHL.ATK_Str+10) + tempHL.Agility * (tempHL.ATK_Agi+10))/(180+tempHL.LV/5);
        tempHL.VIT = (((tempHL.LV+tempHL.VIT_Vit) * tempHL.LV*a.Vitality)+(a.Vitality+tempHL.Strength)*a.Vitality)/(10+tempHL.LV/10);
        tempHL.VITNOW=tempHL.VIT;
        return tempHL;

     }

};

bool GameSystem::IsTaskFinish(Task a){
    return a.FMB>=a.MB;
}


LingHuan GameSystem::CreateLH(HunLing a){
	LingHuan temp;
    temp.LV = a.LV - 2 + GetNumber(2, 4);//-2～2的波动;
	temp.Name = a.Name;
	temp.Des = a.Des;
    if (temp.LV > 0 && temp.LV < 10)
        temp.Col = "灰";
    if (temp.LV >= 10 && temp.LV < 20)
        temp.Col = "白";
    if (temp.LV >= 30 && temp.LV < 40)
        temp.Col = "蓝";
    if (temp.LV >= 40 && temp.LV < 50)
        temp.Col = "黄";
    if (temp.LV >= 50 && temp.LV < 60)
        temp.Col = "橙";
    if (temp.LV >= 60 && temp.LV < 70)
        temp.Col = "绿";
    if (temp.LV >= 80 && temp.LV < 90)
        temp.Col = "紫";
    if (temp.LV >= 90)
        temp.Col = "彩";
    temp.Strength = a.Strength*0.9;
    temp.Agility = a.Agility*0.9;
	temp.ID = a.ID;
	temp.DEF_Ski = a.DEF_Ski;
    temp.Value=(temp.Strength * 100 + temp.Agility * 100 + temp.LV * 50 ) * 1.5;
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
    temp.Strength = int(double(a.Strength)*0.8);
    temp.Agility = int(double(a.Agility)*0.8);
	temp.ATK_Ski = a.ATK_Ski;
    temp.ATK_Ski.NowTurn=0.;
	temp.Add_Str = GetNumber(5, a.LV) / 5 + GetNumber(10, a.Strength) / 10;
	temp.Add_Agi = GetNumber(5, a.LV) / 5 + GetNumber(10, a.Agility) / 10;
	temp.Value =(temp.Strength * 100 + temp.Agility * 100 + temp.LV * 50 +temp.Add_Str * 150 + temp.Add_Agi * 150) * 1.5;
    temp.DEF_Ski = a.DEF_Ski;
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

    temp.Ori_Vitality = (temp.Ori_Strength + temp.Ori_Agility)/3;//体力等于力量加敏捷/3

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
        if(aaa!=0)

        temp.Strength = tempHL.Strength + tempHL.LV * 2 ;
        temp.Agility = tempHL.Agility + tempHL.LV * 2;
		temp.Name = tempHL.Name;
		temp.Des = tempHL.Des;
		temp.DEF_Ski = tempHL.DEF_Ski;
		temp.ID = tempHL.ID;
        if (temp.LV > 0 && temp.LV < 10)
            temp.Col = "灰";
        if (temp.LV >= 10 && temp.LV < 20)
            temp.Col = "白";
        if (temp.LV >= 30 && temp.LV < 40)
            temp.Col = "蓝";
        if (temp.LV >= 40 && temp.LV < 50)
            temp.Col = "黄";
        if (temp.LV >= 50 && temp.LV < 60)
            temp.Col = "橙";
        if (temp.LV >= 60 && temp.LV < 70)
            temp.Col = "绿";
        if (temp.LV >= 80 && temp.LV < 90)
            temp.Col = "紫";
        if (temp.LV >= 90)
            temp.Col = "彩";
		temp.Value = 0;
        tempList.append(temp);
	}
	return tempList;
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
            for(int j=0;j<b->myTaskList.size();j++)
        if (temp.ID==b->myTaskList[j].ID||temp.ID==0)
                tempList.append(SystemMessage[aaa]);
    }

    return tempList;
}

bool GameSystem::CanExcept(Task a,RenWu* b){//判断能否接受任务
    for(int i=0;i<b->myTaskList.size();i++)
    if(a.ID==b->myTaskList[i].ID)
        return false;
    if(SystemTask[a.ID].IsFinish==1)
        return false;
    return SystemTask[a.Need_ID].IsFinish;
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

QList<NPC> GameSystem::CanShowList(DiTu a){//返回目前可以显示的NPC
    QList<NPC>  tempList;
    for (int i = 0; i <10; i++){
        if (SystemTask[SystemNPC[a.IndexNPC[i]].TaskShow].IsFinish==1&&a.IndexNPC[i]!=0)
            tempList.append(SystemNPC[a.IndexNPC[i]]);
	}
	return tempList;
}

DropData GameSystem::DropItem(QList<HunLing> a){//通过魂灵列表生成掉落的东西,特定物品可特定判断
	DropData tempData;
    tempData.Coin=0;
    tempData.Exp=0;
    for (int i = 0; i < a.size(); i++){
        HunLing temp = a[i];


        temp.Strength = SystemHL[temp.ID].Strength + temp.LV * 2;
        temp.Agility=SystemHL[temp.ID].Agility+temp.LV * 2;
        /*特定掉落
        if(temp.ID==x)
            tempData.Item.Insert(SystemItem[aaa]);*/
        /*全局掉落*/

        int count=GetNumber(1,GetNumber(0,GetNumber(2,5)));
        for(int j=0;j<count;j++){
		int aaa = temp.DropItem[GetNumber(1, 9)];
        if(aaa!=0)
        tempData.Item.append(SystemItem[aaa]);
        }
        tempData.Exp +=(a[i].LV-1)*(a[i].LV)+60;
		tempData.Coin += GetNumber(temp.LV * 1.5, temp.LV * 2);
        if (GetNumber(1, 50) == 1){
			LingGu tempLG = CreateLG(temp,GetNumber(1,6));
            tempData.LG.append(tempLG);
		}
        if (GetNumber(1, 15) == 1){
            LingHuan tempLH = CreateLH(temp);
            tempData.LH.append(tempLH);
		}

	}
	return tempData;
}

#endif
