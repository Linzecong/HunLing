/*魂技*/
#ifndef HL_HUNJI
#define HL_HUNJI

#include <QString>
#include <QList>
#include<QFile>
#include<QTextStream>

class HunJi{
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
    HunJi(){
        ID=Type=Turn=NowTurn=0;
        Name=Des="空";
        Energy=Sour=0;
    }
} SystemHJ[200];

void HunJi::Init(){
    QFile file((DATAPATH+"SaveHJ.str"));
      file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
        for(int i=0;i<200;i++)
        in>>SystemHJ[i].Name>>SystemHJ[i].Des;
         file.close();

    QFile tmpfile( DATAPATH+"SaveHJ.num" );
    tmpfile.open(QIODevice::ReadOnly);
    int a=sizeof(int);
    for(int i=0;i<200;i++){
    tmpfile.read(( char *)&SystemHJ[i].ID,a);
    tmpfile.read(( char *)&SystemHJ[i].Energy,a);
    tmpfile.read(( char *)&SystemHJ[i].Sour,a);
    tmpfile.read(( char *)&SystemHJ[i].Type,a);
    tmpfile.read(( char *)&SystemHJ[i].Turn,a);
    SystemHJ[i].NowTurn=0;
    }
    tmpfile.close();  
}

class Buff{
  public:
	int ID;
	QString Des;
	QString Name;
    int type;//1战前，2战中
	void Init();
    Buff(){
        ID=type=0;
        Name=Des="空";
    }
} SystemBuff[200];

void Buff::Init(){
    QFile file((DATAPATH+"SaveBuff.str"));
    file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=0;i<200;i++)
        in>>SystemBuff[i].Name>>SystemBuff[i].Des;
        file.close();

    QFile tmpfile(DATAPATH+"SaveBuff.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=0;i<200;i++){
    int a=sizeof(int);
    tmpfile.read(( char *)&SystemBuff[i].ID,a);
    tmpfile.read(( char *)&SystemBuff[i].type,a);
    }
    tmpfile.close();
}

/*
class BuffList{
  public:
    QList<Buff> List;
  public:
	void Insert(Buff a);
	void Remove(int a);
	Buff GetData(int a);
	void Clear();
	int Count();
};

void BuffList::Clear(){
    List.clear();
}


void BuffList::Remove(int a){
    List.removeAt(a);
}

int BuffList::Count(){
    return List.size();
}

void BuffList::Insert(Buff a){
    List.append(a);
}

Buff BuffList::GetData(int a){
    return List[a];
}
*/
#endif
