
#include <QString>
	class LingHuan
{
  public:
	int LV;
	int ID;
	int DEF_Ski;
	QString Name;
	QString Des;
	QString Col;
	double Value;
	double Strength;
	double Agility;
};

class LHNode
{
  public:
	LingHuan data;
	LHNode *link;
  public:
	  LHNode(LingHuan Item)
	{
		data = Item;
		link = NULL;
	}
};

class LHBagList
{
  public:
	LHNode * first;
  public:
	LHBagList()
	{
		first = NULL;
	}
	void Remove(int a);
	LingHuan Take(int a);
	int Count();
	void Insert(LingHuan a);
	LingHuan GetData(int a);
};

class LHList
{
  public:
	LHNode * first;
  public:
	LHList()
	{
		first = NULL;
	}
	void Remove(int a);
	LingHuan Replace(LingHuan a, int b);
	LingHuan Take(int a);
	int Count();
	void Insert(LingHuan a);
	LingHuan GetData(int a);
	void Exchange(int a, int b);
};


void LHBagList::Remove(int a)
{
	if (first == NULL)
		return;
	if (a <= 1)					// 如果移除的是第一个
	{
		LHNode *temp = first;
		first = first->link;	// 把第一个变成第一个的后一个
		delete temp;			// 释放内存
	}
	if (a > 1)
	{
		LHNode *del;			// 用于释放内存
		LHNode *temp = first;	// 标识第一个
		for (int i = 2; i < a; i++)	// 遍历到要删除的前一个
			temp = temp->link;	// 把这个变成这个的下一个
		del = temp->link;		// 找出要删除的
		temp->link = del->link;	// 要删除的前一个的后一个变成要删除的那个的后一个
		delete del;				// 释放内存，彻底删除
	}
}

LingHuan LHBagList::Take(int a)
{
    LingHuan C;
	if (first == NULL)
		return C;

	if (a <= 1)
	{
		LHNode *temp = first;
		first = first->link;
        C = temp->data;
		delete temp;
	}
	if (a > 1)
	{
		LHNode *del;
		LHNode *temp = first;
		for (int i = 2; i < a; i++)
			temp = temp->link;
		del = temp->link;
		temp->link = del->link;
        C = del->data;	// 保存值域
		delete del;
	}
    return C;
}

int LHBagList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	LHNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

void LHBagList::Insert(LingHuan a)
{
	if (first == NULL)			// 如果为空
	{
		LHNode *newLH = new LHNode(a);
		first = newLH;			// 插入第一个
	}
	else						// 由大到小排
	{
		LHNode *newLH = new LHNode(a);
		LHNode *temp = first;
		if (first->link == NULL)
		{
			if (a.LV > first->data.LV)
			{
				first = newLH;
				newLH->link = temp;
			}
		}
		else
			first->link = newLH;
		while (temp->link->data.LV > a.LV)	// 遍历直到下一个为空
		{
			if (temp->link == NULL)
				break;
			temp = temp->link;	// 变成下一个
		}
		LHNode *aaa = temp->link;
		temp->link = newLH;		// 插入
		newLH->link = aaa;
	}
}

LingHuan LHBagList::GetData(int a)	// 取数据
{
	if (first == NULL)
	{
		LingHuan C;
		return C;
	}
	LHNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}


LingHuan LHList::Replace(LingHuan a, int b)
{
        LingHuan C;
	if (first == NULL)
	{
		LHNode *temp = new LHNode(a);
		first = temp;
		return C;
	}
	if (b <= 1)					// 如果是第一个
	{
        C = first->data;
		first->data = a;		// 直接把值域替换
	}
	if (b > 1)
	{
		LHNode *del;			// 释放内存用
		LHNode *current = first;	// 指向第一个
		LHNode *temp = new LHNode(a);	// 新建要插入的节点

		for (int i = 2; i < b; i++)	// 找到要替代的前一个
			current = current->link;

		del = current->link;	// 找出要替代的
		current->link = temp;	// 替换
		temp->link = del->link;	// 替换 替换的那个 的下一个
        C = del->data;	// 返回用
		delete del;				// 释放内存
	}

    return C;
}

void LHList::Remove(int a)
{
	if (first == NULL)
		return;
	if (a <= 1)					// 如果移除的是第一个
	{
		LHNode *temp = first;
		first = first->link;	// 把第一个变成第一个的后一个
		delete temp;			// 释放内存
	}
	if (a > 1)
	{
		LHNode *del;			// 用于释放内存
		LHNode *temp = first;	// 标识第一个
		for (int i = 2; i < a; i++)	// 遍历到要删除的前一个
			temp = temp->link;	// 把这个变成这个的下一个
		del = temp->link;		// 找出要删除的
		temp->link = del->link;	// 要删除的前一个的后一个变成要删除的那个的后一个
		delete del;				// 释放内存，彻底删除
	}
}

LingHuan LHList::Take(int a)
{
            LingHuan C;
	if (first == NULL)
		return C;

	if (a <= 1)
	{
		LHNode *temp = first;
		first = first->link;
        C = temp->data;
		delete temp;
	}
	if (a > 1)
	{
		LHNode *del;
		LHNode *temp = first;
		for (int i = 2; i < a; i++)
			temp = temp->link;
		del = temp->link;
		temp->link = del->link;
        C = del->data;	// 保存值域
		delete del;
	}
    return C;
}

int LHList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	LHNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

void LHList::Insert(LingHuan a)
{

	if (first == NULL)			// 如果为空
	{
		LHNode *newLH = new LHNode(a);
		first = newLH;			// 插入第一个
	}
	else
	{
		LHNode *newLH = new LHNode(a);
		LHNode *temp = first;
		while (temp->link != NULL)	// 遍历直到下一个为空
			temp = temp->link;	// 变成下一个
		temp->link = newLH;		// 插入
	}
}

LingHuan LHList::GetData(int a)	// 取数据
{
	if (first == NULL)
	{
		LingHuan C;
		return C;
	}
	LHNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}

void LHList::Exchange(int a, int b)
{
	LingHuan temp1 = GetData(a);
	LingHuan temp2 = Replace(temp1, b);
	Replace(temp2, a);
}
