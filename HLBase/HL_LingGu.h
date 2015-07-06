
#include <QString>
	class LingGu
{
  public:
	int LV;
	int ID;
	QString Name;
	int Type;
	double Value;
	double Strength;
	double Agility;
	int DEF_Ski;
    HunJi ATK_Ski;
	double Add_Str;
	double Add_Agi;
    void clear();
};
    void LingGu::clear()
    {
        LV=0;
        ID=0;
        Name="空";
        Type=0;
        Value=0;
        Strength=0;
        Agility=0;
                DEF_Ski=0;
                ATK_Ski=SystemHJ[0];
                Add_Str=0;
                Add_Agi=0;
    }

class LGList
{
  public:
	LingGu Head;
	LingGu Body;
	LingGu LHand;
	LingGu RHand;
	LingGu LLeg;
	LingGu RLeg;
};

class LGNode
{
  public:
	LingGu data;
	LGNode *link;
	  LGNode(LingGu a)
	{
		data = a;
		link = NULL;
	}
};

class LGBagList
{
  public:
	LGNode * first;
	LGBagList()
	{
		first = NULL;
	}

	void Insert(LingGu a);
	void Remove(int a);
	LingGu GetData(int a);
	LingGu Take(int a);
	int Count();
};
int LGBagList::Count()
{
    int sum = 0;
    if (first == NULL)			// 是否空
        return 0;

    LGNode *temp = first;
    while (temp != NULL)		// 不空就++
    {
        sum++;
        temp = temp->link;		// 变成下一个
    }
    return sum;
}
void LGBagList::Remove(int a)
{
	if (first == NULL)
		return;
	if (a <= 1)					// 如果移除的是第一个
	{
		LGNode *temp = first;
		first = first->link;	// 把第一个变成第一个的后一个
		delete temp;			// 释放内存
	}
	if (a > 1)
	{
		LGNode *del;			// 用于释放内存
		LGNode *temp = first;	// 标识第一个
		for (int i = 2; i < a; i++)	// 遍历到要删除的前一个
			temp = temp->link;	// 把这个变成这个的下一个
		del = temp->link;		// 找出要删除的
		temp->link = del->link;	// 要删除的前一个的后一个变成要删除的那个的后一个
		delete del;				// 释放内存，彻底删除
	}
}

LingGu LGBagList::Take(int a)
{
    LingGu C;
	if (first == NULL)	
		return C;

	if (a <= 1)
	{
		LGNode *temp = first;
		first = first->link;
        C  = temp->data;
		delete temp;
	}
	if (a > 1)
	{
		LGNode *del;
		LGNode *temp = first;
		for (int i = 2; i < a; i++)
			temp = temp->link;
		del = temp->link;
		temp->link = del->link;
        C = del->data;	// 保存值域
		delete del;
	}
    return C;
}


void LGBagList::Insert(LingGu a)
{
	if (first == NULL)			// 如果为空
	{
		LGNode *newLG = new LGNode(a);
		first = newLG;			// 插入第一个
	}
	else						// 由大到小排
	{
		LGNode *newLG = new LGNode(a);
		LGNode *temp = first;
		if (first->link == NULL)
		{
			if (a.LV > first->data.LV)
			{
				first = newLG;
				newLG->link = temp;
			}
		}
		else
			first->link = newLG;
		while (temp->link->data.LV > a.LV)	// 遍历直到下一个为空
		{
			if (temp->link == NULL)
				break;
			temp = temp->link;	// 变成下一个
		}
		LGNode *aaa = temp->link;
		temp->link = newLG;		// 插入
		newLG->link = aaa;
	}
}

LingGu LGBagList::GetData(int a)	// 取数据
{
	if (first == NULL)
	{
		LingGu C;
		return C;
	}
	LGNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}
