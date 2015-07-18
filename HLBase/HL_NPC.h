/*NPC*/

#ifndef HL_NPC
#define HL_NPC

#include <QString>
#include <QList>
#include "HL_RenWu.h"

class NPC:public RenWu{
  public:
	QString Des;
	int CanATK;
	int LHID[10];
	int LHLV[10];
	int LGID[7];
	int LGLV[7];
	int CanTalk[20];
	int Task[10];
    int TaskShow;
	int ID;
    void Update();//设置LHLG,更新buff
	void Init();
	void Save();
    QList<int> CanUseHJList(int hl);//返回当前可以使用的技能(魂灵ID)，0魂技,1~6魂骨技能
    NPC();
} SystemNPC[200];

NPC::NPC():RenWu(){
    Des="空";CanATK=0;TaskShow=0;ID=0;
    for(int i=0;i<10;i++){
        LHID[i]=0;LHLV[i]=0;Task[i]=0;
    }
    for(int i=0;i<7;i++){
        LGID[i]=0;LGLV[i]=0;
    }
    for(int i=0;i<20;i++){
        CanTalk[i]=0;
    }
}

QList<int> NPC::CanUseHJList(int hl){
    QList<int> temp;
    if(SystemHL[hl].ATK_Ski.Energy<=Energy&&SystemHL[hl].ATK_Ski.Sour<=Sour&&SystemHL[hl].ATK_Ski.NowTurn==0)
        temp.append(0);
    if(LG.Head.ATK_Ski.Energy<=Energy&&LG.Head.ATK_Ski.Sour<=Sour&&LG.Head.ATK_Ski.NowTurn==0&&LG.Head.ATK_Ski.ID!=0)
        temp.append(1);
    if(LG.Body.ATK_Ski.Energy<=Energy&&LG.Body.ATK_Ski.Sour<=Sour&&LG.Body.ATK_Ski.NowTurn==0&&LG.Body.ATK_Ski.ID!=0)
        temp.append(2);
    if(LG.LHand.ATK_Ski.Energy<=Energy&&LG.LHand.ATK_Ski.Sour<=Sour&&LG.LHand.ATK_Ski.NowTurn==0&&LG.LHand.ATK_Ski.ID!=0)
        temp.append(3);
    if(LG.RHand.ATK_Ski.Energy<=Energy&&LG.RHand.ATK_Ski.Sour<=Sour&&LG.RHand.ATK_Ski.NowTurn==0&&LG.RHand.ATK_Ski.ID!=0)
        temp.append(4);
    if(LG.LLeg.ATK_Ski.Energy<=Energy&&LG.LLeg.ATK_Ski.Sour<=Sour&&LG.LLeg.ATK_Ski.NowTurn==0&&LG.LLeg.ATK_Ski.ID!=0)
        temp.append(5);
    if(LG.RLeg.ATK_Ski.Energy<=Energy&&LG.RLeg.ATK_Ski.Sour<=Sour&&LG.RLeg.ATK_Ski.NowTurn==0&&LG.RLeg.ATK_Ski.ID!=0)
        temp.append(6);

    return temp;
}

void NPC::Save(){
        QFile file((DATAPATH+"SaveNPC.str"));
        file.open(QIODevice::WriteOnly);
         QTextStream in(&file);
         for(int i=0;i<200;i++)
        in<<SystemNPC[i].Name<<" "<<SystemNPC[i].Des<<endl;
         file.close();

     QFile tmpfile(DATAPATH+"SaveNPC.num" );
    tmpfile.open(QIODevice::WriteOnly);
    int a=sizeof(int);
    for(int i=0;i<200;i++){
    tmpfile.write(( char *)&SystemNPC[i].ID,a);
    tmpfile.write(( char *)&SystemNPC[i].LV,a);
    tmpfile.write(( char *)&SystemNPC[i].Ori_Strength,a);
    tmpfile.write(( char *)&SystemNPC[i].Ori_Agility,a);
    tmpfile.write(( char *)&SystemNPC[i].Ori_Vitality,a);
    tmpfile.write(( char *)&SystemNPC[i].Ori_Energy,a);
    tmpfile.write(( char *)&SystemNPC[i].Ori_Sour,a);
    tmpfile.write(( char *)&SystemNPC[i].CanATK,a);
    tmpfile.write(( char *)&SystemNPC[i].TaskShow,a);
    tmpfile.write(( char *)&SystemNPC[i].LHID,sizeof(LHID));
    tmpfile.write(( char *)&SystemNPC[i].LHLV,sizeof(LHLV));
    tmpfile.write(( char *)&SystemNPC[i].LGID,sizeof(LGID));
    tmpfile.write(( char *)&SystemNPC[i].LGLV,sizeof(LGLV));
    tmpfile.write(( char *)&SystemNPC[i].CanTalk,sizeof(CanTalk));
    tmpfile.write(( char *)&SystemNPC[i].Task,sizeof(Task));
    }
    tmpfile.close();
}

void NPC::Init(){
    QFile file((DATAPATH+"SaveNPC.str"));
     file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=0;i<200;i++)
        in>>SystemNPC[i].Name>>SystemNPC[i].Des;
      file.close();

    QFile tmpfile( DATAPATH+"SaveNPC.num" );
    tmpfile.open(QIODevice::ReadOnly);
     int a=sizeof(int);
    for(int i=0;i<200;i++){
        tmpfile.read(( char *)&SystemNPC[i].ID,a);
        tmpfile.read(( char *)&SystemNPC[i].LV,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Strength,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Agility,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Vitality,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Energy,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Sour,a);
        tmpfile.read(( char *)&SystemNPC[i].CanATK,a);
        tmpfile.read(( char *)&SystemNPC[i].TaskShow,a);
        tmpfile.read(( char *)&SystemNPC[i].LHID,sizeof(LHID));
        tmpfile.read(( char *)&SystemNPC[i].LHLV,sizeof(LHLV));
        tmpfile.read(( char *)&SystemNPC[i].LGID,sizeof(LGID));
        tmpfile.read(( char *)&SystemNPC[i].LGLV,sizeof(LGLV));
        tmpfile.read(( char *)&SystemNPC[i].CanTalk,sizeof(CanTalk));
        tmpfile.read(( char *)&SystemNPC[i].Task,sizeof(Task));
    }
    tmpfile.close();

    for(int i=0;i<200;i++)
        SystemNPC[i].Update();
}

void NPC::Update(){
    for(int i=0;i<10;i++){
		int a=LHID[i];
		if(a==0)
        continue;
		int b=LHLV[i];
        if(b==0)
            continue;
		HunLing tempHL=SystemHL[a];
		tempHL.LV=b;
	    tempHL.Update();
		LingHuan temp;
		temp.LV = tempHL.LV;
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
        LH.append(temp);
	}
	for(int i=1;i<=6;i++){
		int aID=LGID[i];
		if(aID==0)
		continue;
		int aLV=LGLV[i];
        if(aLV==0)
            continue;
		HunLing a=SystemHL[aID];
		a.LV=aLV;
	    a.Update();
	    LingGu temp;
	temp.ID=a.ID;
	temp.LV = a.LV - 2 + GetNumber(2, 4);
	temp.Type = i;
	temp.Strength = a.Strength - 5 + GetNumber(5, 10);
	temp.Agility = a.Agility - 5 + GetNumber(5, 10);
	temp.ATK_Ski = a.ATK_Ski;
	temp.Add_Str = GetNumber(5, a.LV) / 5 + GetNumber(10, a.Strength) / 10;
	temp.Add_Agi = GetNumber(5, a.LV) / 5 + GetNumber(10, a.Agility) / 10;
	temp.Value =(temp.Strength * 100 + temp.Agility * 100 + temp.LV * 50 +temp.Add_Str * 150 + temp.Add_Agi * 150) * 1.5;
	temp.DEF_Ski = GetNumber(1, temp.LV * 2);
    switch (temp.Type){
    case 1:
            temp.Name = a.Name + "之头盖骨";
            LG.Head=temp;
            break;
    case 2:
            temp.Name = a.Name + "之躯干骨";
            LG.Body=temp;
            break;
    case 3:
            temp.Name = a.Name + "之左臂骨";
            LG.LHand=temp;
            break;
    case 4:
            temp.Name = a.Name + "之右臂骨";
            LG.RHand=temp;
            break;
    case 5:
            temp.Name = a.Name + "之左腿骨";
            LG.LLeg=temp;
            break;
    case 6:
            temp.Name = a.Name + "之右腿骨";
            LG.RLeg=temp;
            break;
    }
		
	}

    for(int i=0;i<10;i++){
        if(Task[i]!=0)
        myTaskList.append(SystemTask[Task[i]]);//Attention
    }
    UpdateBuff();
}



/*
class NPCList{
  public:
    QList<NPC> List;
  public:
	int Count();
	void Insert(NPC a);
	NPC GetData(int a);
};
*/

class Message{
  public:
	int NTask;					// 接了哪个后可以说
	QString Msg;
	int ID;
	void Init();
    Message(){
        NTask=0;
        Msg="空";
    }
} SystemMessage[500];

void Message::Init(){
	QFile file((DATAPATH+"SaveMessage.str"));
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
    for (int i = 0; i <500; i++)
		in >> SystemMessage[i].NTask >> SystemMessage[i].Msg;
	file.close();
}  


/*
class MessageList{
  public:
    QList<Message> List;
  public:
	int Count();
	void Insert(Message a);
	Message GetData(int a);
};


int NPCList::Count(){
    return List.size();
}

void NPCList::Insert(NPC a){
    List.append(a);
}

NPC NPCList::GetData(int a){
    return List[a];
}

int MessageList::Count(){
    return List.size();
}

void MessageList::Insert(Message a){
    List.append(a);
}

Message MessageList::GetData(int a){
    return List[a];
}
*/
#endif
