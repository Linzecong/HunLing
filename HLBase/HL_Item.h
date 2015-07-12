/*道具*/
#ifndef HL_ITEM
#define HL_ITEM

#include <QString>
#include<QList>
#include<QFile>
#include<QTextStream>

class Item{
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
    int Count;
	void Init();
    Item(){
        ID=Type=ATKType=Value=0;
        Des=Name="空";
        Str=Agi=Vit=Ene=Sour=Exp=Count=0;
    }
} SystemItem[200];

void Item::Init(){
	QFile file((DATAPATH+"SaveItem.str"));
	file.open(QIODevice::ReadOnly);
	QTextStream in(&file);
    for (int i = 0; i <200; i++)
		in >> SystemItem[i].Name >> SystemItem[i].Des;
       file.close();

	QFile tmpfile(DATAPATH+"SaveItem.num");
	tmpfile.open(QIODevice::ReadOnly);
        int a = sizeof(int);
        for (int i = 0; i <200; i++){
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
        tmpfile.read((char *)&SystemItem[i].Count, a);
	}
	tmpfile.close();
}  
/*
class ItemNode{
  public:
	Item data;
	int Count;
    ItemNode(Item a)
	{
		Count = 1;
		data = a;
	}
};

class ItemList{
  public:
    QList<ItemNode> List;
  public:
	void Remove(int a);
	int Count();
	void Insert(Item a);
	Item GetData(int a);
	int GetCount(int a);
};

void ItemList::Remove(int a){
    if(List[a].Count>1)
        List[a].Count--;
    else
        List.takeAt(a);
}

int ItemList::Count(){

    return List.size();
}

void ItemList::Insert(Item a){
    List.append(a);
}

Item ItemList::GetData(int a){

    return List[a].data;
}

int ItemList::GetCount(int a){
    return List[a].Count;

}
*/
#endif
