
#include <QString>
#include <QList>
class NPC:public RenWu
{
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
    void Update();//设置LHLG;
	void Init();
	void Save();
    QList<int> CanUseHJList(int hl);//返回当前可以使用的技能(魂灵ID)，0魂技,1~6魂骨技能
} SystemNPC[200];

QList<int> NPC::CanUseHJList(int hl)
{
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

void NPC::Save()
{
        QFile file((DATAPATH+"SaveNPC.str"));
file.open(QIODevice::WriteOnly);
      QTextStream in(&file);
         for(int i=1;i<=199;i++)
        in<<SystemNPC[i].Name<<" "<<SystemNPC[i].Des<<endl;

     QFile tmpfile( DATAPATH+"SaveNPC.num" );
    tmpfile.open(QIODevice::WriteOnly);
    for(int i=1;i<=199;i++)
    {
    int a=sizeof(i);
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

void NPC::Init()
{
    QFile file((DATAPATH+"SaveNPC.str"));
file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=1;i<=199;i++)
        in>>SystemNPC[i].Name>>SystemNPC[i].Des;
        for(int i=1;i<=199;i++)
        if(SystemNPC[i].Name=="")
        {
        SystemNPC[i].Name="未编辑";
        SystemNPC[i].Des="未编辑";
        }


   file.close();
    QFile tmpfile( DATAPATH+"SaveNPC.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=1;i<=199;i++)
    {
        int a=sizeof(i);
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

    for(int i=1;i<=199;i++)
        SystemNPC[i].Update();
}

void NPC::Update()
{
	for(int i=1;i<=9;i++)
	{
		int a=LHID[i];
		if(a==0)
		break;
		int b=LHLV[i];
		HunLing tempHL=SystemHL[a];
		tempHL.LV=b;
	    tempHL.Update();
		LingHuan temp;
		temp.LV = tempHL.LV;
		int AgiP =
			tempHL.LV * 5 * tempHL.Agility / (tempHL.Agility +
											  tempHL.Strength);
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
		LH.Insert(temp);
	}
	for(int i=1;i<=6;i++)
	{
		int aID=LGID[i];
		if(aID==0)
		continue;
		int aLV=LGLV[i];
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
	temp.Value =
		(temp.Strength * 100 + temp.Agility * 100 + temp.LV * 50 +
		 temp.Add_Str * 150 + temp.Add_Agi * 150) * 1.5;
	temp.DEF_Ski = GetNumber(1, temp.LV * 2);
    switch (temp.Type)
    {
    case 1:
        {
            temp.Name = a.Name + "之头盖骨";
            LG.Head=temp;
            break;
        }
    case 2:
        {
            temp.Name = a.Name + "之躯干骨";
            LG.Body=temp;
            break;
        }
    case 3:
        {
            temp.Name = a.Name + "之左臂骨";
            LG.LHand=temp;
            break;
        }
    case 4:
        {
            temp.Name = a.Name + "之右臂骨";
            LG.RHand=temp;
            break;
        }
    case 5:
        {
            temp.Name = a.Name + "之左腿骨";
            LG.LLeg=temp;
            break;
        }
    case 6:
        {
            temp.Name = a.Name + "之右腿骨";
            LG.RLeg=temp;
            break;
        }
    }
		
	}
	
	for(int i=1;i<=9;i++)
        myTaskList.Insert(SystemTask[Task[i]]);//Attention

    UpdateBuff();
	
}

class NPCNode
{
  public:
	NPC data;
	NPCNode *link;
	  NPCNode(NPC a)
	{
		data = a;
		link = NULL;
	}
};


class NPCList
{
  public:
	NPCNode * first;
  public:
	NPCList()
	{
		first = NULL;
	}
	int Count();
	void Insert(NPC a);
	NPC GetData(int a);
};

class Message
{
  public:
	int NTask;					// 接了哪个后可以说
	QString Msg;
	int ID;
	void Init();
} SystemMessage[500];

void Message::Init()
{
	QFile file((DATAPATH+"SaveMessage.str"));
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
	for (int i = 1; i <= 499; i++)
	{
		in >> SystemMessage[i].NTask >> SystemMessage[i].Msg;

		if (SystemMessage[i].Msg == "")
		{
			SystemMessage[i].Msg = "未编辑";
			SystemMessage[i].NTask = 0;
		}
	}

	file.close();
}  
class MessageNode
{
  public:
	Message data;
	MessageNode *link;
	  MessageNode(Message a)
	{
		data = a;
		link = NULL;
	}
};


class MessageList
{
  public:
	MessageNode * first;
  public:
	MessageList()
	{
		first = NULL;
	}

	int Count();
	void Insert(Message a);
	Message GetData(int a);
};


int NPCList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	NPCNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

void NPCList::Insert(NPC a)
{
	if (first == NULL)			// 如果为空
	{
		NPCNode *newNPC = new NPCNode(a);
		first = newNPC;			// 插入第一个
	}
	else
	{
		NPCNode *newNPC = new NPCNode(a);
		NPCNode *temp = first;
		while (temp->link != NULL)	// 遍历直到一个为空
			temp = temp->link;	// 变成下一个
		temp->link = newNPC;
	}
}

NPC NPCList::GetData(int a)		// 取数据
{
	if (first == NULL)
	{
		NPC C;
		return C;
	}
	NPCNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}

int MessageList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	MessageNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

void MessageList::Insert(Message a)
{
	if (first == NULL)			// 如果为空
	{
		MessageNode *newMessage = new MessageNode(a);
		first = newMessage;		// 插入第一个
	}
	else
	{
		MessageNode *newMessage = new MessageNode(a);
		MessageNode *temp = first;
		while (temp->link != NULL)	// 遍历直到一个为空
			temp = temp->link;	// 变成下一个
		temp->link = newMessage;
	}
}

Message MessageList::GetData(int a)	// 取数据
{
	if (first == NULL)
	{
		Message C;
		return C;
	}
	MessageNode *temp = first;	// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}
