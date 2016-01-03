#ifndef GLOBAL_H
#define GLOBAL_H

#define DATAPATH QString("./Data/")
#include<QFile>
#include<QTextStream>
#include<QString>

class DiTu
{
public:
    QString Name;
    QString Des;
    int IndexNPC[10];
    int IndexHL[10];
    int MaxLV;
    int MinLV;
    int NTask;
    int PosX;
    int PosY;
    int HLCount;
    void Save();
    void Init();
    DiTu(){
        Name=Des="空";
        for(int i=0;i<10;i++)
            IndexHL[i]=IndexNPC[i]=0;
        MaxLV=MinLV=NTask=0;
        PosX=PosY=0;
        HLCount=0;
    }
}SystemMap[26][26];
void DiTu::Save()
{
    for (int i = 0; i <= 25; i++)
        for (int j = 0; j <= 25; j++)
            if(SystemMap[i][j].Name=="")
                SystemMap[i][j].Name=SystemMap[i][j].Des="空";

    QFile file((DATAPATH+"SaveMap.str"));
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    for (int i = 0; i <= 25; i++)
        for (int j = 0; j <= 25; j++)
            in << SystemMap[i][j].Name << " " << SystemMap[i][j].Des << endl;

    QFile tmpfile(DATAPATH+"SaveMap.num");
    tmpfile.open(QIODevice::WriteOnly);
    for (int i = 0; i <= 25; i++)
        for (int j = 0; j <= 25; j++)
        {
            int a = sizeof(i);
            tmpfile.write((char *)&SystemMap[i][j].IndexNPC,sizeof(IndexNPC));
            tmpfile.write((char *)&SystemMap[i][j].IndexHL, sizeof(IndexHL));
            tmpfile.write((char *)&SystemMap[i][j].MaxLV, a);
            tmpfile.write((char *)&SystemMap[i][j].MinLV, a);
            tmpfile.write((char *)&SystemMap[i][j].NTask, a);
            tmpfile.write((char *)&SystemMap[i][j].PosX, a);
            tmpfile.write((char *)&SystemMap[i][j].PosY, a);
            tmpfile.write((char *)&SystemMap[i][j].HLCount, a);
        }
    tmpfile.close();
}

void DiTu::Init()
{
    QFile file((DATAPATH+"SaveMap.str"));
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for (int i = 0; i <= 25; i++)
        for (int j = 0; j <= 25; j++)
            in >> SystemMap[i][j].Name >> SystemMap[i][j].Des;


    file.close();
    QFile tmpfile(DATAPATH+"SaveMap.num");
    tmpfile.open(QIODevice::ReadOnly);
    for (int i = 0; i <= 25; i++)
        for (int j = 0; j <= 25; j++)
        {
            int a = sizeof(i);
            tmpfile.read((char *)&SystemMap[i][j].IndexNPC,sizeof(IndexNPC));
            tmpfile.read((char *)&SystemMap[i][j].IndexHL, sizeof(IndexHL));
            tmpfile.read((char *)&SystemMap[i][j].MaxLV, a);
            tmpfile.read((char *)&SystemMap[i][j].MinLV, a);
            tmpfile.read((char *)&SystemMap[i][j].NTask, a);
            tmpfile.read((char *)&SystemMap[i][j].PosX, a);
            tmpfile.read((char *)&SystemMap[i][j].PosY, a);
            tmpfile.read((char *)&SystemMap[i][j].HLCount, a);
        }
    tmpfile.close();
}
class HJ
{
public:
    int ID;
    QString Name;
    QString Des;
    int Energy;
    int Sour;
    int Type;
    int Turn;
    int NowTurn;
    HJ(){
        ID=Type=Turn=NowTurn=0;
        Name=Des="空";
        Energy=Sour=0;
    }
    void Save();
    void Init();
} SystemHJ[200];
void HJ::Save()
{
    QFile file((DATAPATH+"SaveHJ.str"));
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    for(int i=0;i<200;i++)
        in<<SystemHJ[i].Name<<" "<<SystemHJ[i].Des<<endl;

    QFile tmpfile( DATAPATH+"SaveHJ.num" );
    tmpfile.open(QIODevice::WriteOnly);
    for(int i=0;i<200;i++){
        int a=sizeof(i);
        tmpfile.write(( char *)&SystemHJ[i].ID,a);
        tmpfile.write(( char *)&SystemHJ[i].Energy,a);
        tmpfile.write(( char *)&SystemHJ[i].Sour,a);
        tmpfile.write(( char *)&SystemHJ[i].Type,a);
        tmpfile.write(( char *)&SystemHJ[i].Turn,a);
    }
    tmpfile.close();
}
void HJ::Init()
{
    QFile file((DATAPATH+"SaveHJ.str"));
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for(int i=0;i<200;i++)
        in>>SystemHJ[i].Name>>SystemHJ[i].Des;

    file.close();
    QFile tmpfile( DATAPATH+"SaveHJ.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=0;i<200;i++)
    {
        int a=sizeof(int);
        tmpfile.read(( char *)&SystemHJ[i].ID,a);
        tmpfile.read(( char *)&SystemHJ[i].Energy,a);
        tmpfile.read(( char *)&SystemHJ[i].Sour,a);
        tmpfile.read(( char *)&SystemHJ[i].Type,a);
        tmpfile.read(( char *)&SystemHJ[i].Turn,a);
    }
    tmpfile.close();
}

class Buff
{
public:
    int ID;
    QString Des;
    QString Name;
    int type;
    void Save();
    void Init();
    Buff(){
        ID=type=0;
        Name=Des="空";
    }
} SystemBuff[200];

void Buff::Save()
{
    QFile file((DATAPATH+"SaveBuff.str"));
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    for(int i=0;i<200;i++)
        in<<SystemBuff[i].Name<<" "<<SystemBuff[i].Des<<endl;

    QFile tmpfile( DATAPATH+"SaveBuff.num" );
    tmpfile.open(QIODevice::WriteOnly);
    for(int i=0;i<200;i++)
    {
        int a=sizeof(i);
        tmpfile.write(( char *)&SystemBuff[i].ID,a);
        tmpfile.write(( char *)&SystemBuff[i].type,a);
    }
    tmpfile.close();
}
void Buff::Init()
{
    QFile file((DATAPATH+"SaveBuff.str"));
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for(int i=0;i<200;i++)
        in>>SystemBuff[i].Name>>SystemBuff[i].Des;


    file.close();
    QFile tmpfile( DATAPATH+"SaveBuff.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=0;i<200;i++)
    {
        int a=sizeof(int);
        tmpfile.read(( char *)&SystemBuff[i].ID,a);
        tmpfile.read(( char *)&SystemBuff[i].type,a);
    }
    tmpfile.close();
}

class HunLing
{
public:
    int LV;
    QString Name;
    QString Des;
    int ID;
    int Strength;
    int Agility;
    int ATK;
    int DEF;
    int VIT;
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
    int ATK_Ski;
    int DropItem[10];
    HunLing(){
        LV=ID=0;
        Name=Des="空";
        Strength=Agility=ATK=DEF=VIT=0;
        K_Fire=K_Ice=K_Lig=K_Tox=0;
        G_Fire=G_Ice=G_Lig=G_Tox=ATK_Str=ATK_Agi=0;
        DEF_Str= DEF_Agi=VIT_Vit=DEF_Ski=0;
        ATK_Ski=0;
        for(int i=0;i<10;i++)
            DropItem[i]=0;
    }
public:
    void Save();
    void Init();
}SystemHL[200];

void HunLing::Save()
{
    QFile file((DATAPATH+"SaveHL.str"));
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    for(int i=0;i<200;i++)
        in<<SystemHL[i].Name<<" "<<SystemHL[i].Des<<endl;

    QFile tmpfile( DATAPATH+"SaveHL.num" );
    tmpfile.open(QIODevice::WriteOnly);
    for(int i=0;i<200;i++)
    {
        int a=sizeof(i);
        tmpfile.write(( char *)&SystemHL[i].ID,a);
        tmpfile.write(( char *)&SystemHL[i].Strength,a);
        tmpfile.write(( char *)&SystemHL[i].Agility,a);
        tmpfile.write(( char *)&SystemHL[i].K_Fire,a);
        tmpfile.write(( char *)&SystemHL[i].K_Ice,a);
        tmpfile.write(( char *)&SystemHL[i].K_Lig,a);
        tmpfile.write(( char *)&SystemHL[i].K_Tox,a);
        tmpfile.write(( char *)&SystemHL[i].G_Fire,a);
        tmpfile.write(( char *)&SystemHL[i].G_Ice,a);
        tmpfile.write(( char *)&SystemHL[i].G_Lig,a);
        tmpfile.write(( char *)&SystemHL[i].G_Tox,a);
        tmpfile.write(( char *)&SystemHL[i].ATK_Str,a);
        tmpfile.write(( char *)&SystemHL[i].ATK_Agi,a);
        tmpfile.write(( char *)&SystemHL[i].DEF_Str,a);
        tmpfile.write(( char *)&SystemHL[i].DEF_Agi,a);
        tmpfile.write(( char *)&SystemHL[i].VIT_Vit,a);
        tmpfile.write(( char *)&SystemHL[i].DEF_Ski,a);
        tmpfile.write(( char *)&SystemHL[i].ATK_Ski,a);
        tmpfile.write(( char *)&SystemHL[i].DropItem,sizeof(DropItem));
    }
    tmpfile.close();
}
void HunLing::Init()
{
    QFile file((DATAPATH+"SaveHL.str"));
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for(int i=0;i<200;i++)
        in>>SystemHL[i].Name>>SystemHL[i].Des;



    file.close();
    QFile tmpfile( DATAPATH+"SaveHL.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=0;i<200;i++)
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
        tmpfile.read(( char *)&SystemHL[i].ATK_Ski,a);
        tmpfile.read(( char *)&SystemHL[i].DropItem,sizeof(DropItem));
    }
    tmpfile.close();
}


class Item
{
public:
    int ID;
    QString Des;
    QString Name;
    int Type;//1战前使用,2战中使用,3不可使用
    int ATKType;//0敌人单体,1敌人全体,2我方单体,3我方全体
    int Value;
    int Str;
    int Agi;
    int Vit;
    int Ene;
    int Sour;
    int Exp;
    int Count;
    Item(){
        ID=Type=ATKType=Value=0;
        Des=Name="空";
        Str=Agi=Vit=Ene=Sour=Exp=Count=0;
    }
    void Save();
    void Init();
} SystemItem[200];
void Item::Save()
{
    QFile file((DATAPATH+"SaveItem.str"));
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    for (int i = 0; i <200; i++)
        in << SystemItem[i].Name << " " << SystemItem[i].Des << endl;

    QFile tmpfile(DATAPATH+"SaveItem.num");
    tmpfile.open(QIODevice::WriteOnly);
    for (int i = 0; i <200; i++)
    {
        int a = sizeof(i);
        tmpfile.write((char *)&SystemItem[i].ID, a);
        tmpfile.write((char *)&SystemItem[i].Type, a);
        tmpfile.write((char *)&SystemItem[i].ATKType, a);
        tmpfile.write((char *)&SystemItem[i].Value, a);
        tmpfile.write((char *)&SystemItem[i].Str, a);
        tmpfile.write((char *)&SystemItem[i].Agi, a);
        tmpfile.write((char *)&SystemItem[i].Vit, a);
        tmpfile.write((char *)&SystemItem[i].Ene, a);
        tmpfile.write((char *)&SystemItem[i].Sour, a);
        tmpfile.write((char *)&SystemItem[i].Exp, a);

    }
    tmpfile.close();
}

void Item::Init()
{
    QFile file((DATAPATH+"SaveItem.str"));
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for (int i = 0; i <200; i++)
        in >> SystemItem[i].Name >> SystemItem[i].Des;



    file.close();
    QFile tmpfile(DATAPATH+"SaveItem.num");
    tmpfile.open(QIODevice::ReadOnly);
    for (int i = 0; i <200; i++)
    {
        int a = sizeof(int);
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

    }
    tmpfile.close();
}


class Message
{
public:
    int NTask;					// 接了哪个后可以说
    QString Msg;
    int ID;
    void Save();
    void Init();
} SystemMessage[500];

void Message::Save()
{
    QFile file((DATAPATH+"SaveMessage.str"));
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    for (int i = 0; i <= 499; i++)
        in << SystemMessage[i].NTask << " " << SystemMessage[i].Msg << endl;
    file.close();
}

void Message::Init()
{
    QFile file((DATAPATH+"SaveMessage.str"));
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for (int i = 0; i <= 499; i++)
        in >> SystemMessage[i].NTask >> SystemMessage[i].Msg;

    file.close();
}


class NPC
{
public:
    QString Name;
    QString Des;
    int ID;
    int LV;
    int Ori_Strength;
    int Ori_Agility;
    int Ori_Vitality;
    int Ori_Energy;
    int Ori_Sour;
    int CanATK;
    int TaskShow;
    int LHID[10];
    int LHLV[10];
    int LGID[7];
    int LGLV[7];
    int CanTalk[20];
    int Task[10];
public:
    void Save();
    void Init();
    NPC(){
        Name=Des="空";CanATK=0;TaskShow=0;ID=LV=0;
        Ori_Strength=Ori_Agility=Ori_Vitality=Ori_Energy=Ori_Sour=0;
        for(int i=0;i<10;i++){
            LHID[i]=0;LHLV[i]=0;Task[i]=0;
        }
        for(int i=0;i<7;i++){
            LGID[i]=0;LGLV[i]=0;
        }
        for(int i=0;i<20;i++){
            CanTalk[i]=0;
        }
    }
}SystemNPC[200];

void NPC::Save()
{
    QFile file((DATAPATH+"SaveNPC.str"));
    file.open(QIODevice::WriteOnly);
    QTextStream in(&file);
    for(int i=0;i<200;i++)
        in<<SystemNPC[i].Name<<" "<<SystemNPC[i].Des<<endl;

    QFile tmpfile( DATAPATH+"SaveNPC.num" );
    tmpfile.open(QIODevice::WriteOnly);
    for(int i=0;i<200;i++)
    {
        int a=sizeof(i);
        tmpfile.write(( char *)&SystemNPC[i].ID,a);
        tmpfile.write(( char *)&SystemNPC[i].LV,a);
        tmpfile.write(( char *)&SystemNPC[i].Ori_Strength,a);
        tmpfile.write(( char *)&SystemNPC[i].Ori_Agility,a);
        tmpfile.write(( char *)&SystemNPC[i].Ori_Vitality,a);
        tmpfile.write(( char *)&SystemNPC[i].Ori_Energy,a);
        tmpfile.write(( char *)&SystemNPC[i].Ori_Sour,a);
        tmpfile.write(( char *)&SystemNPC[i].CanATK,a);
        tmpfile.write(( char *)&SystemNPC[i].TaskShow,a);
        tmpfile.write(( char *)&SystemNPC[i].LHID,sizeof(LHID));
        tmpfile.write(( char *)&SystemNPC[i].LHLV,sizeof(LHLV));
        tmpfile.write(( char *)&SystemNPC[i].LGID,sizeof(LGID));
        tmpfile.write(( char *)&SystemNPC[i].LGLV,sizeof(LGLV));
        tmpfile.write(( char *)&SystemNPC[i].CanTalk,sizeof(CanTalk));
        tmpfile.write(( char *)&SystemNPC[i].Task,sizeof(Task));
    }
    tmpfile.close();
}
void NPC::Init()
{
    QFile file((DATAPATH+"SaveNPC.str"));
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for(int i=0;i<200;i++)
        in>>SystemNPC[i].Name>>SystemNPC[i].Des;


    file.close();
    QFile tmpfile( DATAPATH+"SaveNPC.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=0;i<200;i++)
    {
        int a=sizeof(i);
        tmpfile.read(( char *)&SystemNPC[i].ID,a);
        tmpfile.read(( char *)&SystemNPC[i].LV,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Strength,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Agility,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Vitality,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Energy,a);
        tmpfile.read(( char *)&SystemNPC[i].Ori_Sour,a);
        tmpfile.read(( char *)&SystemNPC[i].CanATK,a);
        tmpfile.read(( char *)&SystemNPC[i].TaskShow,a);
        tmpfile.read(( char *)&SystemNPC[i].LHID,sizeof(LHID));
        tmpfile.read(( char *)&SystemNPC[i].LHLV,sizeof(LHLV));
        tmpfile.read(( char *)&SystemNPC[i].LGID,sizeof(LGID));
        tmpfile.read(( char *)&SystemNPC[i].LGLV,sizeof(LGLV));
        tmpfile.read(( char *)&SystemNPC[i].CanTalk,sizeof(CanTalk));
        tmpfile.read(( char *)&SystemNPC[i].Task,sizeof(Task));
    }
    tmpfile.close();
}
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
    for(int i=0;i<=199;i++)
        in<<SystemTask[i].Name<<" "<<SystemTask[i].Des<<endl;

    QFile tmpfile( DATAPATH+"SaveTask.num" );
    tmpfile.open(QIODevice::WriteOnly);
    for(int i=0;i<=199;i++)
    {
        int a=sizeof(i);
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
    for(int i=0;i<=199;i++)
        in>>SystemTask[i].Name>>SystemTask[i].Des;



    file.close();
    QFile tmpfile( DATAPATH+"SaveTask.num" );
    tmpfile.open(QIODevice::ReadOnly);
    for(int i=0;i<=199;i++)
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

    }
    tmpfile.close();
}





#endif // GLOBAL_H

