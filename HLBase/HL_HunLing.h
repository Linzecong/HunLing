
#include <QString>
	class HunLing
{
  public:
	int LV;
	int ID;
	QString Name;
	QString Des;
	int Strength;
	int Agility;
	int ATK;
	int DEF;
	int VIT;
    int VITNOW;
	int K_Fire;
	int K_Ice;
	int K_Lig;
	int K_Tox;
	int G_Fire;
	int G_Ice;
	int G_Lig;
	int G_Tox;
	int ATK_Str;
	int ATK_Agi;
	int DEF_Str;
	int DEF_Agi;
    int VIT_Vit;
	int DEF_Ski;
	HunJi ATK_Ski;
	int DropItem[10];//会掉落的道具
	void Init();
	void Update();
	
} SystemHL[200];

void HunLing::Update()//更新力量和敏捷（NPC生成灵环用）
{
		int AgiP =LV * 5 * Agility / (Agility +Strength);
		Strength = Strength + LV * 5 - AgiP;
		Agility = Agility + AgiP;
		
}

void HunLing::Init()
{
    QFile file((DATAPATH+"SaveHL.str"));
file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=1;i<=199;i++)
        in>>SystemHL[i].Name>>SystemHL[i].Des;
        for(int i=1;i<=199;i++)
        if(SystemHL[i].Name=="")
        {
        SystemHL[i].Name="未编辑";
        SystemHL[i].Des="未编辑";
        }


   file.close();
    QFile tmpfile( DATAPATH+"SaveHL.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=1;i<=199;i++)
    {
        int a=sizeof(i);
        tmpfile.read(( char *)&SystemHL[i].ID,a);
        tmpfile.read(( char *)&SystemHL[i].Strength,a);
        tmpfile.read(( char *)&SystemHL[i].Agility,a);
        tmpfile.read(( char *)&SystemHL[i].K_Fire,a);
        tmpfile.read(( char *)&SystemHL[i].K_Ice,a);
        tmpfile.read(( char *)&SystemHL[i].K_Lig,a);
        tmpfile.read(( char *)&SystemHL[i].K_Tox,a);
        tmpfile.read(( char *)&SystemHL[i].G_Fire,a);
        tmpfile.read(( char *)&SystemHL[i].G_Ice,a);
        tmpfile.read(( char *)&SystemHL[i].G_Lig,a);
        tmpfile.read(( char *)&SystemHL[i].G_Tox,a);
        tmpfile.read(( char *)&SystemHL[i].ATK_Str,a);
        tmpfile.read(( char *)&SystemHL[i].ATK_Agi,a);
        tmpfile.read(( char *)&SystemHL[i].DEF_Str,a);
        tmpfile.read(( char *)&SystemHL[i].DEF_Agi,a);
        tmpfile.read(( char *)&SystemHL[i].VIT_Vit,a);
        tmpfile.read(( char *)&SystemHL[i].DEF_Ski,a);
        int Hjtemp;
        tmpfile.read(( char *)&Hjtemp,a);
        SystemHL[i].ATK_Ski=SystemHJ[Hjtemp];
        tmpfile.read(( char *)&SystemHL[i].DropItem,sizeof(DropItem));
    }
    tmpfile.close();
}


class HLNode
{
  public:
	HunLing data;
	HLNode *link;
	  HLNode(HunLing a)
	{
		data = a;
		link = NULL;
	}
};

class HLList
{
  public:
	HLNode * first;
  public:
	HLList()
	{
		first = NULL;
	}
	HunLing GetData(int a);
	int Count();
	int AVE_ATK();
	int AVE_DEF();
	int TOL_VIT();
	HunLing Take(int a);
	void Insert(HunLing a);
	HunLing Replace(HunLing a, int b);

};

HunLing HLList::Replace(HunLing a, int b)
{
    HunLing C;
	if (first == NULL)
	{
		HLNode *temp = new HLNode(a);
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
		HLNode *del;			// 释放内存用
		HLNode *current = first;	// 指向第一个
		HLNode *temp = new HLNode(a);	// 新建要插入的节点

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


HunLing HLList::Take(int a)
{
    HunLing C;
	if (first == NULL)	
		return C;

	if (a <= 1)
	{
		HLNode *temp = first;
		first = first->link;
        C = temp->data;
		delete temp;
	}
	if (a > 1)
	{
		HLNode *del;
		HLNode *temp = first;
		for (int i = 2; i < a; i++)
			temp = temp->link;
		del = temp->link;
		temp->link = del->link;
        C = del->data;	// 保存值域
		delete del;
	}
    return C;
}

int HLList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	HLNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

void HLList::Insert(HunLing a)
{
	if (first == NULL)			// 如果为空
	{
		HLNode *newHL = new HLNode(a);
		first = newHL;			// 插入第一个
	}
	else
	{
		HLNode *newHL = new HLNode(a);
		HLNode *temp = first;
		while (temp->link != NULL)	// 遍历直到一个为空
			temp = temp->link;	// 变成下一个
		temp->link = newHL;
	}
}

HunLing HLList::GetData(int a)	// 取数据
{
	if (first == NULL)
	{
		HunLing C;
		return C;
	}
	HLNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}

int HLList::AVE_ATK()
{
	int sum = 0;
	for (int i = 1; i <= Count(); i++)
		sum += GetData(i).ATK;
	return sum / Count();
}

int HLList::AVE_DEF()
{
	int sum = 0;
	for (int i = 1; i <= Count(); i++)
		sum += GetData(i).DEF;
	return sum / Count();
}

int HLList::TOL_VIT()
{
	int sum = 0;
	for (int i = 1; i <= Count(); i++)
		sum += GetData(i).VIT;
	return sum;
}
