
#include <QString>
#include <QList>
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



class HLList
{
  public:
    QList<HunLing> List;
  public:
	HLList()
	{

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
    HunLing C=List[b];
    List[b]=a;
    return C;
}


HunLing HLList::Take(int a)
{
   return List.takeAt(a);
}

int HLList::Count()
{
    return List.size();
}

void HLList::Insert(HunLing a)
{
    List.append(a);
}

HunLing HLList::GetData(int a)	// 取数据
{

    return List[a];
}

int HLList::AVE_ATK()
{
	int sum = 0;
    for (int i = 1; i <=Count(); i++)
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
