/*地图*/
#ifndef HL_DITU
#define HL_DITU

#define SAVEPATH QString("./Save/")
#define DATAPATH QString("./Data/")
#define MAPMAX 26
#define HJMAX 500
#define BUFFMAX 200
#define HLMAX 500
#define ITEMMAX 200
#define NPCMAX 200
#define MSGMAX 1000
#define TASKMAX 500

#include <QString>
#include <QTime>
#include<QFile>
#include<QTextStream>

double pow(double a,double n){//次方
    int sum=1;
    for(int i=1;i<=n;i++)
        sum=sum*a;
    return sum;
}

int GetNumber(int a, int b){//获得随机数
    if(a>=b)
        return a;
    int sum=a + qrand() % (b - a);
    return sum;
}

class DiTu{
public:
    QString Name="空";
    QString Des="空";
    int IndexNPC[10]{0,0,0,0,0,0,0,0,0,0};//会出现的NPC
    int IndexHL[10]{0,0,0,0,0,0,0,0,0,0};//会出现的魂兽
    int MaxLV=0;
    int MinLV=0;
    int NTask=0;//到这里需要完成哪个任务
    int PosX=0;
    int PosY=0;
    int HLCount=0;//魂兽会出现的最大数量
    static void Init();
}SystemMap[MAPMAX][MAPMAX];

void DiTu::Init(){
    QFile file(DATAPATH+"SaveMap.str");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for (int i = 0; i < MAPMAX; i++)
        for (int j = 0; j < MAPMAX; j++)
            in >> SystemMap[i][j].Name >> SystemMap[i][j].Des;

    file.close();
    QFile tmpfile(DATAPATH+"SaveMap.num");
    tmpfile.open(QIODevice::ReadOnly);
    for (int i = 0; i < MAPMAX; i++)
        for (int j = 0; j < MAPMAX; j++){
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

#endif












