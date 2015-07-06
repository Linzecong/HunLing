#include <QString>
#include <QList>
//#include "HLQTData/HL_HunLing.h"
/*
class HLInOrderNode
{
  public:
	int x;//列表第几个
    int Agility;//敏捷
	HLInOrderNode *link;
	int type;					// 敌人还是自己,0敌人1自己
    HLInOrderNode(HLInOrderNode a, int type1);
    HLInOrderNode();
};

HLInOrderNode::HLInOrderNode(HLInOrderNode a, int type1)
{
    x = a.x;
    Agility = a.Agility;
    type = type1;
    link = NULL;
}
HLInOrderNode::HLInOrderNode()
{
    x = 0;
    Agility = 0;
    type = -1;
    link = NULL;
}

class HLInOrderList
{
  public:
	HLInOrderNode * first;
	int next;					// 循环用
  public:
    void Resort();
	int Count();
	HLInOrderNode GetData(int a);
	void Insert(HLInOrderNode a, int type);
	HLInOrderNode Replace(HLInOrderNode a, int b);
	void Exchange(int a, int b);
    HLInOrderList(HLList a, HLList b);
    HLInOrderList(){first=NULL;}
	int GetX();//直接调用这个
	int GetType();//再调用这个


};

void HLInOrderList::Resort()
{
    for (int i = 1; i <= Count(); i++)//由大到小排
        for (int j = 1; j <= Count(); j++)
            if (GetData(i).Agility < GetData(j).Agility)
                Exchange(i, j);
}

void HLInOrderList::Insert(HLInOrderNode a, int type)
{
	if (first == NULL)			// 如果为空
	{
		HLInOrderNode *newHL = new HLInOrderNode(a, type);
		first = newHL;			// 插入第一个
	}
	else
	{
		HLInOrderNode *newHL = new HLInOrderNode(a, type);
		HLInOrderNode *temp = first;
		while (temp->link != NULL)	// 遍历直到一个为空
			temp = temp->link;	// 变成下一个
		temp->link = newHL;
	}
}

HLInOrderNode HLInOrderList::Replace(HLInOrderNode a, int b)
{
	if (first == NULL)
	{
		HLInOrderNode *temp = new HLInOrderNode(a, a.type);
		first = temp;
		HLInOrderNode C;
		return C;
	}
	if (b <= 1)					// 如果是第一个
	{
		HLInOrderNode A1 = *first;
		*first = a;				// 直接把值域替换
		return A1;
	}
	if (b > 1)
	{
		HLInOrderNode *del;		// 释放内存用
		HLInOrderNode *current = first;	// 指向第一个
		HLInOrderNode *temp = new HLInOrderNode(a, a.type);	// 新建要插入的节点

		for (int i = 2; i < b; i++)	// 找到要替代的前一个
			current = current->link;

		del = current->link;	// 找出要替代的
		current->link = temp;	// 替换
		temp->link = del->link;	// 替换 替换的那个 的下一个
		HLInOrderNode A1 = *del;	// 返回用
		delete del;				// 释放内存
		return A1;
	}
}


void HLInOrderList::Exchange(int a, int b)
{

	HLInOrderNode temp1 = GetData(a);
	HLInOrderNode temp2 = Replace(temp1, b);
	Replace(temp2, a);
}

HLInOrderList::HLInOrderList(HLList a, HLList b)
{
	next = 1;
	for (int i = 1; i <= a.Count(); i++)//插入自己
	{
		HLInOrderNode temp;
		temp.x = i;
        temp.Agility = a.GetData(i).Agility;
		temp.type = 1;
		temp.link = NULL;
		Insert(temp, 1);
	}
	for (int i = 1; i <= b.Count(); i++)//插入敌人
	{
		HLInOrderNode temp;
		temp.x = i;
        temp.Agility = b.GetData(i).Agility;
		temp.type = 0;
		temp.link = NULL;
		Insert(temp, 0);
	}
	for (int i = 1; i <= Count(); i++)//由大到小排
		for (int j = 1; j <= Count(); j++)
            if (GetData(i).Agility < GetData(j).Agility)
				Exchange(i, j);

}

HLInOrderNode HLInOrderList::GetData(int a)
{
	if (first == NULL)
	{
		HLInOrderNode C;
		return C;
	}
	HLInOrderNode *temp = first;	// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个

	return *temp;
}

int HLInOrderList::GetX()//战斗时直接调用这个配合HLList.GetData(x);取得魂灵
{
	int a = next;
	if (first == NULL)
	{
        return 0;
	}
	HLInOrderNode *temp = first;	// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个

	next++;//指向下一个
	if (next > Count())
		next = 1;

	return temp->x;
}

int HLInOrderList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	HLInOrderNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

int HLInOrderList::GetType()//战斗时直接调用
{
	int a = next;
	if (first == NULL)
	{
		int C = -1;
		return C;
	}
	HLInOrderNode *temp = first;	// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个

	return temp->type;
}
*/

class EnergyBar
{
public:
    HLList* Me;
    HLList* Enemy;
    QList<int> List;
    int totle;//能量最大值
    QList<int> ATKList;
    int type;// 敌人还是自己,0敌人1自己
    int index;
public:
    EnergyBar(HLList* a,HLList* b);
    ~EnergyBar(){}
    void next();

};
EnergyBar::EnergyBar(HLList* a,HLList* b)
{
    Enemy=b;
    Me=a;
    totle=0;
    for(int i=1;i<=Enemy->Count();i++)//统计能量最大值
    {
        totle+=Enemy->GetData(i).Agility;
       List.append(Enemy->GetData(i).Agility);
    }
    for(int i=1;i<=Me->Count();i++)
    {
        totle+=Me->GetData(i).Agility;
        List.append(Me->GetData(i).Agility);
    }
    type=0;
    index=0;

}

void EnergyBar::next()
{
    if(ATKList.isEmpty()==1)//如果可攻击列表是空的
    {
    int stop=0;//停止循环标志
    while(stop==0)
    {
        for(int i=0;i<=List.size();i++)
        {
            if((i+1)>Me->Count())//判断是加敌人还是自己的敏捷值
            List[i]+=Me->GetData(i).Agility;
            else
            List[i]+=Enemy->GetData(i).Agility;

            if(List[i]>=totle)//如果大于能量最大值
            {
                List[i]-=totle;//循环
                ATKList.append(i);//将序号插入可循环列表
                stop=1;
            }
        }
    }


    if(ATKList.size()>1)//如果可循环列表大于一个
    for(int i=0;i<=ATKList.size();i++)//按照敏捷值大小由大到小排序
        for(int j=0;j<=ATKList.size();j++)
        if(List[ATKList[j]]>List[ATKList[i]])
        {
                int a=ATKList[i];
                ATKList[j]=a;
                ATKList[i]=ATKList[j];
        }

    if(ATKList[0]>Me->Count())//设置本轮攻击的人
     {
        type=0;
        index=ATKList[0]-Me->Count();
    }
    else
    {
        type=1;
        index=ATKList[0];
    }
    ATKList.removeFirst();//移除
    }
    else//如果可攻击列表不为空
    {
        if(ATKList[0]>Me->Count())
         {
            type=0;
            index=ATKList[0]-Me->Count();
        }
        else
        {
            type=1;
            index=ATKList[0];
        }
        ATKList.removeFirst();
    }

}





class FightSystem
{
  public:
	RenWu * Me;
	NPC Enemy;
    HLList* MyHL;
    HLList* EnemyHL;
    EnergyBar* EB;
	int Turn;
  public:
	void SetBuff();//初始化后自动调用，设置Buff效果
    FightSystem(RenWu* a, NPC b,HLList* a1,HLList* b1);
	void TurnOut();				// 技能-1
	QString Attack(HunLing * a, HunLing * b);//攻击
	QString Skill(HunLing * a, HunLing * b, HunJi * skill);//技能，直接传入技能。
	QString UseItem(int a, HunLing * b,HunLing *c);//用道具，道具编号。
    QString Skip();
	int CanGoOn();				// 判断能否继续
	void UpdateATKDEF();//每轮前调用，更新攻击和防御力和体力
};

QString FightSystem::Skip()
{

}

FightSystem::FightSystem(RenWu* a, NPC b, HLList *a1, HLList *b1)
{
    Me = a;
    Enemy= b;
    MyHL=a1;
    EnemyHL=b1;
	Turn = 1;
   EB=new EnergyBar(MyHL,EnemyHL);
	SetBuff();


}

void FightSystem::SetBuff()
{
	for (int i = 1; i <= Me->myBuffList.Count(); i++)//注意！通过人物的BuffList来更新
	{
		int a = Me->myBuffList.GetData(i).ID;
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

	for (int i = 1; i <= Enemy.myBuffList.Count(); i++)//注意！！
	{
		int a = Enemy.myBuffList.GetData(i).ID;
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

void FightSystem::TurnOut()		// 技能冷却-1
{
    Turn++;
    for (int i = 1; i <= MyHL->Count(); i++)
	{
        HunLing temp = MyHL->GetData(i);
		temp.ATK_Ski.NowTurn--;
		if (temp.ATK_Ski.NowTurn < 0)
			temp.ATK_Ski.NowTurn = 0;
        MyHL->Replace(temp, i);
	}
    for (int i = 1; i <= EnemyHL->Count(); i++)
	{
        HunLing temp = EnemyHL->GetData(i);
		temp.ATK_Ski.NowTurn--;
		if (temp.ATK_Ski.NowTurn < 0)
			temp.ATK_Ski.NowTurn = 0;
        EnemyHL->Replace(temp, i);
	}
}

int FightSystem::CanGoOn()		// 判断能否继续。0我输，1继续，-1赢了,-2平局
{
    if(Turn>=30)
        return -2;
	int n = 0;
    for (int i = 1; i <= MyHL->Count(); i++)
        if (MyHL->GetData(i).VIT != 0)
			n = 1;

	if (n == 1)
	{
		n = -1;
        for (int i = 1; i <= EnemyHL->Count(); i++)
            if (EnemyHL->GetData(i).VIT != 0)
				n = 1;
	}
    return n;//注意初始化掉落
}

 QString FightSystem::Attack(HunLing * a, HunLing * b)
{
	double ATKPoint = a->ATK - b->DEF;
	if (ATKPoint < 0)
		return a->Name+"的攻击太低了！起不了作用！";
	else
	{
		b->VIT -= ATKPoint;
		if (b->VIT <= 0)
			b->VIT = 0;
		return a->Name+"对对方"+b->Name+"造成"+QString::number(ATKPoint)+"点伤害！";
	}
}

QString FightSystem::Skill(HunLing * a, HunLing * b, HunJi * skill)//注意技能类型！
{
	QString Description;
	skill->NowTurn += skill->Turn;
	switch (skill->ID)
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
	return Description;
}

QString FightSystem::UseItem(int a, HunLing * b,HunLing* c)
{
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
	return Description;

}

void FightSystem::UpdateATKDEF()
{
    for(int i=1;i<=MyHL->Count();i++)
	{
        HunLing tempHL=MyHL->GetData(i);
		tempHL.ATK =
			(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.ATK_Str +
									 tempHL.Agility * tempHL.ATK_Agi);
		tempHL.DEF =
			(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.DEF_Str +
									 tempHL.Agility * tempHL.DEF_Agi);
        MyHL->Replace(tempHL,i);
	}
        for(int i=1;i<=EnemyHL->Count();i++)
	{
        HunLing tempHL=EnemyHL->GetData(i);
		tempHL.ATK =
			(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.ATK_Str +
									 tempHL.Agility * tempHL.ATK_Agi);
		tempHL.DEF =
			(1 + 0.2 * tempHL.LV) * (tempHL.Strength * tempHL.DEF_Str +
									 tempHL.Agility * tempHL.DEF_Agi);
        EnemyHL->Replace(tempHL,i);
	}
}











