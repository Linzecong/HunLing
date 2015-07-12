/*灵骨*/
#ifndef HL_LINGGU
#define HL_LINGGU

#include <QString>
#include<QList>
#include "HL_HunJi.h"
class LingGu{
  public:
	int LV;
	int ID;
	QString Name;
	int Type;
	double Value;
	double Strength;
	double Agility;
	int DEF_Ski;
    HunJi ATK_Ski;
	double Add_Str;
	double Add_Agi;
    LingGu(){
        LV=ID=0;
        Name="空";
        Type=Value=Strength=Agility=0;
        DEF_Ski=0;
        ATK_Ski=SystemHJ[0];
        Add_Str=Add_Agi=0;
    }
    void clear();
};
void LingGu::clear(){
        LV=ID=0;
        Name="空";
        Type=Value=Strength=Agility=0;
        DEF_Ski=0;
        ATK_Ski=SystemHJ[0];
        Add_Str=Add_Agi=0;
    }

class LGList{
  public:
	LingGu Head;
	LingGu Body;
	LingGu LHand;
	LingGu RHand;
	LingGu LLeg;
	LingGu RLeg;
};



class LGBagList{
  public:
    QList<LingGu> List;

	void Insert(LingGu a);
	void Remove(int a);
	LingGu GetData(int a);
	LingGu Take(int a);
	int Count();
};
int LGBagList::Count(){
    return List.size();
}
void LGBagList::Remove(int a){
    List.removeAt(a);
}

LingGu LGBagList::Take(int a){
    return List.takeAt(a);
}


void LGBagList::Insert(LingGu a){
    List.append(a);
}

LingGu LGBagList::GetData(int a){
    return List[a];
}

#endif
