#include<QFile>
#include<QTextStream>
#include <QString>
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

class TaskNode
{
  public:
	Task data;
	TaskNode *link;
	  TaskNode(Task a)
	{
		data = a;
		link = NULL;
	}
};


class TaskList
{
  public:
	TaskNode * first;
  public:
	TaskList()
	{
		first = NULL;
	}
	Task TakeByIndex(int a);
	Task TakeByID(int a);
	int Count();
	void Insert(Task a);
	Task GetData(int a);
};

Task TaskList::TakeByIndex(int a)
{
            Task C;
	if (first == NULL)
		return C;

	if (a <= 1)
	{
		TaskNode *temp = first;
		first = first->link;
        C = temp->data;
		delete temp;
	}
	if (a > 1)
	{
		TaskNode *del;
		TaskNode *temp = first;
		for (int i = 2; i < a; i++)
			temp = temp->link;
		del = temp->link;
		temp->link = del->link;
        C = del->data;	// 保存值域
		delete del;
	}
    return C;
}

Task TaskList::TakeByID(int a)
{
	TaskNode *del;
	if (first == NULL)
	{
		Task C;
		return C;
	}
	if (first->data.ID == a)
	{
		del = first;
		Task A1 = first->data;	// 保存值域
		first = first->link;
		delete del;
		return A1;
	}



	TaskNode *temp = first;
	for (int i = 2; i <= Count(); i++)
	{
		if (temp->link->data.ID == a)
			break;
		temp = temp->link;
	}
	del = temp->link;
	temp->link = del->link;
	Task A1 = del->data;		// 保存值域
	delete del;
	return A1;
}




int TaskList::Count()
{
	int sum = 0;
	if (first == NULL)			// 是否空
		return 0;

	TaskNode *temp = first;
	while (temp != NULL)		// 不空就++
	{
		sum++;
		temp = temp->link;		// 变成下一个
	}
	return sum;
}

void TaskList::Insert(Task a)
{
	if (first == NULL)			// 如果为空
	{
		TaskNode *newTask = new TaskNode(a);
		first = newTask;		// 插入第一个
	}
	else
	{
		TaskNode *newTask = new TaskNode(a);
		TaskNode *temp = first;
		while (temp->link != NULL)	// 遍历直到一个为空
			temp = temp->link;	// 变成下一个
		temp->link = newTask;
	}
}

Task TaskList::GetData(int a)	// 取数据
{
	if (first == NULL)
	{
		Task C;
		return C;
	}
	TaskNode *temp = first;		// 从第一个开始
	for (int i = 2; i <= a; i++)	// 从第二个开始遍历
		temp = temp->link;		// 变成下一个
	return temp->data;
}
