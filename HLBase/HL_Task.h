#include<QFile>
#include<QTextStream>
#include <QString>
#include<QList>
	class Task
{
  public:
	QString Name;
	QString Des;
	int ID;
	int Need_ID;
	int IsFinish;
	int MB;
	int FMB;
	int NKillHL;
	int NKillNPC;
	int NTalkNPC;
	int NGetItem;
	int A_Coin;
	int A_Exp;
	int A_Item;
	int A_Count;
	public:
	Task()
	{
	ID=0;
	Des="空";
	Need_ID=0;
	Name="空";
    IsFinish=0;
	MB=0;
	FMB=0;
	NKillHL=0;
	NKillNPC=0;
	NTalkNPC=0;
    NGetItem=0;
	A_Coin=0;
	A_Exp=0;
	A_Item=0;
	A_Count=0;
	}
    void Save();
    void Init();
} SystemTask[200];
void Task::Save()
{
		QFile file((DATAPATH+"SaveTask.str"));
file.open(QIODevice::WriteOnly);
      QTextStream in(&file);
         for(int i=1;i<=199;i++)
    	in<<SystemTask[i].Name<<" "<<SystemTask[i].Des<<endl;
file.close();
	 QFile tmpfile( DATAPATH+"SaveTask.num" );  
    tmpfile.open(QIODevice::WriteOnly);
    for(int i=1;i<=199;i++)
    {
    int a=sizeof(int);
    tmpfile.write(( char *)&SystemTask[i].ID,a);
    tmpfile.write(( char *)&SystemTask[i].Need_ID,a);
    tmpfile.write(( char *)&SystemTask[i].IsFinish,a);
    tmpfile.write(( char *)&SystemTask[i].MB,a);
    tmpfile.write(( char *)&SystemTask[i].FMB,a);
    tmpfile.write(( char *)&SystemTask[i].NKillHL,a);
    tmpfile.write(( char *)&SystemTask[i].NKillNPC,a);
    tmpfile.write(( char *)&SystemTask[i].NTalkNPC,a);
    tmpfile.write(( char *)&SystemTask[i].NGetItem,a);
    tmpfile.write(( char *)&SystemTask[i].A_Coin,a);
    tmpfile.write(( char *)&SystemTask[i].A_Exp,a);
    tmpfile.write(( char *)&SystemTask[i].A_Item,a);
    tmpfile.write(( char *)&SystemTask[i].A_Count,a);
 
    }
    tmpfile.close();  
}
void Task::Init()
{
	QFile file((DATAPATH+"SaveTask.str"));
file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=1;i<=199;i++)
    	in>>SystemTask[i].Name>>SystemTask[i].Des;
      

   file.close();
    QFile tmpfile( DATAPATH+"SaveTask.num" );  
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=1;i<=199;i++)
    {
    int a=sizeof(int); 
	tmpfile.read(( char *)&SystemTask[i].ID,a);
	tmpfile.read(( char *)&SystemTask[i].Need_ID,a);
	tmpfile.read(( char *)&SystemTask[i].IsFinish,a);
	tmpfile.read(( char *)&SystemTask[i].MB,a);
	tmpfile.read(( char *)&SystemTask[i].FMB,a);
	tmpfile.read(( char *)&SystemTask[i].NKillHL,a);
	tmpfile.read(( char *)&SystemTask[i].NKillNPC,a);
	tmpfile.read(( char *)&SystemTask[i].NTalkNPC,a);
	tmpfile.read(( char *)&SystemTask[i].NGetItem,a);
	tmpfile.read(( char *)&SystemTask[i].A_Coin,a);
	tmpfile.read(( char *)&SystemTask[i].A_Exp,a);
	tmpfile.read(( char *)&SystemTask[i].A_Item,a);
	tmpfile.read(( char *)&SystemTask[i].A_Count,a);
 SystemTask[i].IsFinish=0;//important
    }
    tmpfile.close();  
}




class TaskList
{
  public:
    QList<Task> List;
  public:
	TaskList()
	{

	}
	Task TakeByIndex(int a);
	Task TakeByID(int a);
	int Count();
	void Insert(Task a);
	Task GetData(int a);
};

Task TaskList::TakeByIndex(int a)
{

    return List.takeAt(a);
}

Task TaskList::TakeByID(int a)
{
    for(int i=1;i<=Count();i++)
    {
        if(List[i].ID==a)
    return List[i];
        }
    return SystemTask[0];
}




int TaskList::Count()
{

    return List.size();
}

void TaskList::Insert(Task a)
{
    List.append(a);
}

Task TaskList::GetData(int a)	// 取数据
{

    return List[a];
}
