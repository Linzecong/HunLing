/*灵环*/

#ifndef HL_LINGHUAN
#define HL_LINGHUAN

#include <QString>
#include<QList>

class LingHuan{
  public:
	int LV;
	int ID;
	int DEF_Ski;
	QString Name;
	QString Des;
	QString Col;
    int Value;
    int Strength;
    int Agility;
    LingHuan(){
        LV=ID=DEF_Ski=0;
        Name=Des=Col="空";
        Value=Strength=Agility=0;
    }
};

/*
class LHList{
  public:
    QList<LingHuan> List;
  public:
	void Remove(int a);
	LingHuan Replace(LingHuan a, int b);
	LingHuan Take(int a);
	int Count();
	void Insert(LingHuan a);
	LingHuan GetData(int a);
	void Exchange(int a, int b);
};


LingHuan LHList::Replace(LingHuan a, int b){
    LingHuan C=List[b];
    List[b]=a;
    return C;
}

void LHList::Remove(int a){
    List.removeAt(a);
}

LingHuan LHList::Take(int a){
      return List.takeAt(a);
}

int LHList::Count(){

    return List.size();
}

void LHList::Insert(LingHuan a){

    List.append(a);
}

LingHuan LHList::GetData(int a){
    return List[a];
}

void LHList::Exchange(int a, int b){
	LingHuan temp1 = GetData(a);
	LingHuan temp2 = Replace(temp1, b);
	Replace(temp2, a);
}
*/
#endif
