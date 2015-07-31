/*魂技*/
#ifndef HL_HUNJI
#define HL_HUNJI

#include <QString>
#include <QList>
#include<QFile>
#include<QTextStream>

enum ATKTYPE
{
    ENEMYSINGLE=0,
    ENEMYTEAM=1,
    MYSIGLE=2,
    MYTEAM=3

};

class HunJi{
  public:
	int ID;
	QString Name;
	QString Des;
    int  Energy;
    int Sour;
    ATKTYPE Type;//0敌人单体,1敌人全体,2我方单体,3我方全体
	int Turn;
	int NowTurn;
	void Init();
    HunJi(){
        ID=Turn=NowTurn=0;
        Name=Des="空";
        Energy=Sour=0;
    }
} SystemHJ[HJMAX];

void HunJi::Init(){
    QFile file((DATAPATH+"SaveHJ.str"));
      file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
        for(int i=0;i<HJMAX;i++)
        in>>SystemHJ[i].Name>>SystemHJ[i].Des;
         file.close();

    QFile tmpfile( DATAPATH+"SaveHJ.num" );
    tmpfile.open(QIODevice::ReadOnly);
    int a=sizeof(int);
    for(int i=0;i<HJMAX;i++){
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
} SystemBuff[BUFFMAX];

void Buff::Init(){
    QFile file((DATAPATH+"SaveBuff.str"));
    file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=0;i<BUFFMAX;i++)
        in>>SystemBuff[i].Name>>SystemBuff[i].Des;
        file.close();

    QFile tmpfile(DATAPATH+"SaveBuff.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=0;i<BUFFMAX;i++){
    int a=sizeof(int);
    tmpfile.read(( char *)&SystemBuff[i].ID,a);
    tmpfile.read(( char *)&SystemBuff[i].type,a);
    }
    tmpfile.close();
}

#endif
