#include <QString>
#include <QTime>
#include<QFile>

double pow(double a,double n)//次方
{
int sum=1;
for(int i=1;i<=n;i++)
sum=sum*a;
return sum;
}
int GetNumber(int a, int b)//获得随机数
{
    QTime t;

    t= QTime::currentTime();

    qsrand(t.msec()+t.second()*1000);

    int sum=a + qrand() % (b - a);
return sum;
}
class DiTu
{
	public:
	QString Name;
	QString Des;
	int IndexNPC[10];//会出现的NPC
	int IndexHL[10];//会出现的魂兽
	int MaxLV;
	int MinLV;
	int NTask;//到这里需要完成哪个任务
	int PosX;
	int PosY;
	int HLCount;//魂兽会出现的最大数量
	void Init();
}SystemMap[26][26];

void DiTu::Init()
{
    QFile file(DATAPATH+"SaveMap.str");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    for (int i = 0; i <= 25; i++)
        for (int j = 0; j <= 25; j++)
        in >> SystemMap[i][j].Name >> SystemMap[i][j].Des;

    for (int i = 0; i <= 25; i++)
        for (int j = 0; j <= 25; j++)
        if (SystemMap[i][j].Name == "")
        {
            SystemMap[i][j].Name = "未编辑";
            SystemMap[i][j].Des = "未编辑";
        }


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














