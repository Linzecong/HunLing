
#include <QString>
#include<QList>
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


class LHBagList
{
  public:
    QList<LingHuan> List;
  public:
	LHBagList()
	{
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
    QList<LingHuan> List;
  public:
	LHList()
{
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
    List.removeAt(a);
}

LingHuan LHBagList::Take(int a)
{
    return List.takeAt(a);
}

int LHBagList::Count()
{

    return List.size();
}

void LHBagList::Insert(LingHuan a)
{
    List.append(a);
}

LingHuan LHBagList::GetData(int a)	// 取数据
{

    return List[a];
}


LingHuan LHList::Replace(LingHuan a, int b)
{
    LingHuan C=List[b];
    List[b]=a;
    return C;
}

void LHList::Remove(int a)
{
    List.removeAt(a);
}

LingHuan LHList::Take(int a)
{
      return List.takeAt(a);
}

int LHList::Count()
{

    return List.size();
}

void LHList::Insert(LingHuan a)
{

    List.append(a);
}

LingHuan LHList::GetData(int a)	// 取数据
{
    return List[a];
}

void LHList::Exchange(int a, int b)
{
	LingHuan temp1 = GetData(a);
	LingHuan temp2 = Replace(temp1, b);
	Replace(temp2, a);
}
