
#include <QString>
	class HunJi
{
  public:
	int ID;
	QString Name;
	QString Des;
	double Energy;
	double Sour;
    int Type;//0敌人单体,1敌人全体,2我方单体,3我方全体
	int Turn;
	int NowTurn;
	void Init();
} SystemHJ[200];

void HunJi::Init()
{
    QFile file((DATAPATH+"SaveHJ.str"));
file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=1;i<=199;i++)
        in>>SystemHJ[i].Name>>SystemHJ[i].Des;
        for(int i=1;i<=199;i++)
        if(SystemHJ[i].Name=="")
        {
        SystemHJ[i].Name="未编辑";
        SystemHJ[i].Des="未编辑";
        }
      

   file.close();
    QFile tmpfile( DATAPATH+"SaveHJ.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=1;i<=199;i++)
    {
    int a=sizeof(int);
    tmpfile.read(( char *)&SystemHJ[i].ID,a);
    tmpfile.read(( char *)&SystemHJ[i].Energy,a);
    tmpfile.read(( char *)&SystemHJ[i].Sour,a);
    tmpfile.read(( char *)&SystemHJ[i].Type,a);
    tmpfile.read(( char *)&SystemHJ[i].Turn,a);
    SystemHJ[i].NowTurn=0;
    }
    tmpfile.close();  
}

class Buff
{
  public:
	int ID;
	QString Des;
	QString Name;
    int type;//1战前，2战中
	void Init();
} SystemBuff[200];

void Buff::Init()
{
    QFile file((DATAPATH+"SaveBuff.str"));
file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=1;i<=199;i++)
        in>>SystemBuff[i].Name>>SystemBuff[i].Des;
        for(int i=1;i<=199;i++)
        if(SystemBuff[i].Name=="")
        {
        SystemBuff[i].Name="未编辑";
        SystemBuff[i].Des="未编辑";
        }


   file.close();
    QFile tmpfile( DATAPATH+"SaveBuff.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=1;i<=199;i++)
    {
    int a=sizeof(int);
    tmpfile.read(( char *)&SystemBuff[i].ID,a);
    tmpfile.read(( char *)&SystemBuff[i].type,a);
    }
    tmpfile.close();
}

class BuffNode
{
  public:
	Buff data;
	BuffNode *link;
	  BuffNode(Buff a)
	{
		data = a;
		link = NULL;
	}
};

class BuffList
{
  public:
	BuffNode * first;
  public:
	BuffList()
	{
		first = NULL;
	}
	void Insert(Buff a);
	void Remove(int a);
	Buff GetData(int a);
	void Clear();
	int Count();
};

void BuffList::Clear()
{
	for (int i = 1; i <= Count(); i++)
		Remove(1);
}


void BuffList::Remove(int a)
{
	if (first == NULL)
		return;

	if (a <= 1)
	{
		BuffNode *temp = first;
		first = first->link;
		delete temp;
	}
	if (a > 1)
	{
		BuffNode *del;
		BuffNode *temp = first;
		for (int i = 2; i < a; i++)
			temp = temp->link;
		del = temp->link;
		temp->link = del->link;
		delete del;
	}
}

int BuffList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	BuffNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

void BuffList::Insert(Buff a)
{
	if (first == NULL)			// 如果为空
	{
		BuffNode *newBuff = new BuffNode(a);
		first = newBuff;		// 插入第一个
	}
	else
	{
		BuffNode *newBuff = new BuffNode(a);
		BuffNode *temp = first;
		while (temp->link != NULL)	// 遍历直到一个为空
			temp = temp->link;	// 变成下一个
		temp->link = newBuff;
	}
}

Buff BuffList::GetData(int a)	// 取数据
{
	if (first == NULL)
	{
		Buff C;
		return C;
	}
	BuffNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}
