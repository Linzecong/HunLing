
#include <QString>
#include<QList>
	class Item
{
  public:
	int ID;
	QString Des;
	QString Name;
    int Type; //1战前使用,2战中使用,3不可使用
    int ATKType;//0敌人单体,1敌人全体,2我方单体,3我方全体
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
        tmpfile.read((char *)&SystemItem[i].ATKType, a);
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

	  ItemNode(Item a)
	{
		Count = 1;
		data = a;
	}
};

class ItemList
{
  public:
    QList<ItemNode> List;
  public:
	ItemList()
	{
	}
	void Remove(int a);
	int Count();
	void Insert(Item a);
	Item GetData(int a);
	int GetCount(int a);
};

void ItemList::Remove(int a)
{
    if(List[a].Count>1)
        List[a].Count--;
    else
        List.takeAt(a);
}

int ItemList::Count()
{

    return List.size();
}

void ItemList::Insert(Item a)
{
    List.append(a);
}

Item ItemList::GetData(int a)	// 取数据
{

    return List[a].data;
}

int ItemList::GetCount(int a)
{
    return List[a].Count;

}
