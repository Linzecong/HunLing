/*魂灵*/
#ifndef HL_HUNLING
#define HL_HUNLING

#include "HL_HunJi.h"
#include<QString>
#include<QList>
#include<QFile>
#include<QTextStream>

class HunLing{
  public:
	int LV;
	int ID;
	QString Name;
	QString Des;
	int Strength;
	int Agility;
    double ATK;
    double DEF;
    double VIT;
    double VITNOW;
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
    HunLing(){
        LV=ID=0;
        Name=Des="空";
        Strength=Agility=ATK=DEF=VIT=VITNOW=0;
        K_Fire=K_Ice=K_Lig=K_Tox=0;
        G_Fire=G_Ice=G_Lig=G_Tox=ATK_Str=ATK_Agi=0;
        DEF_Str= DEF_Agi=VIT_Vit=DEF_Ski=0;

        for(int i=0;i<10;i++)
            DropItem[i]=0;
    }
} SystemHL[HLMAX];



void HunLing::Init(){
    QFile file((DATAPATH+"SaveHL.str"));
    file.open(QIODevice::ReadOnly);
      QTextStream in(&file);
         for(int i=0;i<HLMAX;i++)
        in>>SystemHL[i].Name>>SystemHL[i].Des;
       file.close();

    QFile tmpfile( DATAPATH+"SaveHL.num" );
    tmpfile.open(QIODevice::ReadOnly);
    int a=sizeof(int);
    for(int i=0;i<HLMAX;i++){
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


#endif
