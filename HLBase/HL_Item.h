
#include <QString>
	class Item
{
  public:
	int ID;
	QString Des;
	QString Name;
    int Type; //1战前使用,2战中使用,3不可使用
	int Value;
	//会永久增加的数值
	int Str;
	int Agi;
	int Vit;
	int Ene;
	int Sour;
	int Exp;
	void Init();
} SystemItem[200];

void Item::Init()
{
	QFile file((DATAPATH+"SaveItem.str"));
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
	for (int i = 1; i <= 199; i++)
		in >> SystemItem[i].Name >> SystemItem[i].Des;
	for (int i = 1; i <= 199; i++)
		if (SystemItem[i].Name == "")
		{
			SystemItem[i].Name = "未编辑";
			SystemItem[i].Des = "未编辑";
		}


	file.close();
	QFile tmpfile(DATAPATH+"SaveItem.num");
	tmpfile.open(QIODevice::ReadOnly);
	for (int i = 1; i <= 199; i++)
	{
		int a = sizeof(int);
		tmpfile.read((char *)&SystemItem[i].ID, a);
		tmpfile.read((char *)&SystemItem[i].Type, a);
		tmpfile.read((char *)&SystemItem[i].Value, a);
		tmpfile.read((char *)&SystemItem[i].Str, a);
		tmpfile.read((char *)&SystemItem[i].Agi, a);
		tmpfile.read((char *)&SystemItem[i].Vit, a);
		tmpfile.read((char *)&SystemItem[i].Ene, a);
		tmpfile.read((char *)&SystemItem[i].Sour, a);
		tmpfile.read((char *)&SystemItem[i].Exp, a);

	}
	tmpfile.close();
}  

class ItemNode
{
  public:
	Item data;
	int Count;
	ItemNode *link;
	  ItemNode(Item a)
	{
		Count = 1;
		data = a;
		link = NULL;
	}
};

class ItemList
{
  public:
	ItemNode * first;
  public:
	ItemList()
	{
		first = NULL;
	}
	void Remove(int a);
	int Count();
	void Insert(Item a);
	Item GetData(int a);
	int GetCount(int a);
};

void ItemList::Remove(int a)
{
	if (first == NULL)
		return;

	if (a <= 1)
	{
		if (first->Count > 1)
			first->Count--;
		else
		{
			ItemNode *temp = first;
			first = first->link;
			delete temp;
		}
	}
	if (a > 1)
	{
		ItemNode *del;
		ItemNode *temp = first;
		for (int i = 2; i < a; i++)
			temp = temp->link;
		del = temp->link;
		if (del->Count > 1)
			del->Count--;
		else
		{
			temp->link = del->link;
			delete del;
		}
	}
}

int ItemList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	ItemNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

void ItemList::Insert(Item a)
{
	if (first == NULL)			// 如果为空
	{
		ItemNode *newItem = new ItemNode(a);
		first = newItem;		// 插入第一个
	}
	else
	{
		ItemNode *temp = first;
		while (temp != NULL)	// 遍历直到一个为空
		{
			if (temp->data.ID == a.ID)
			{
				temp->Count++;
				break;
			}
			else
				temp = temp->link;	// 变成下一个
		}
		if (temp == NULL)
		{
			ItemNode *newItem = new ItemNode(a);
			temp = newItem;
		}
	}
}

Item ItemList::GetData(int a)	// 取数据
{
	if (first == NULL)
	{
		Item C;
		return C;
	}
	ItemNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}

int ItemList::GetCount(int a)
{
	if (first == NULL)
		return 0;

	ItemNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->Count;

}
