
#include <QString>
#include <QList>
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


class BuffList
{
  public:
    QList<Buff> List;
  public:
	BuffList()
	{

	}
	void Insert(Buff a);
	void Remove(int a);
	Buff GetData(int a);
	void Clear();
	int Count();
};

void BuffList::Clear()
{
    List.clear();
}


void BuffList::Remove(int a)
{
    List.removeAt(a);
}

int BuffList::Count()
{
    return List.size();
}

void BuffList::Insert(Buff a)
{
    List.append(a);
}

Buff BuffList::GetData(int a)	// 取数据
{
    return List[a];
}
