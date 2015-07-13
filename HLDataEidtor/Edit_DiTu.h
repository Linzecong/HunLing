#include<QString>
#include<QFile>
#include<QLineEdit>
#include<QLabel>
#include<QSpinBox>
#include<QWidget>
#include<QListWidget>
#include<QPushButton>
#include<QTextStream>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QComboBox>

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
class MapWidget:public QWidget

{
    //Q_OBJECT
  private:
    QLineEdit * Name;
    QLineEdit *Des;
    QSpinBox *PosX;
    QSpinBox *PosY;
    QSpinBox *MaxLV;
    QSpinBox *MinLV;
    QSpinBox *NTask;
    QSpinBox *HLCount;

    QSpinBox *IndexNPC1;
    QSpinBox *IndexNPC2;
    QSpinBox *IndexNPC3;
    QSpinBox *IndexNPC4;
    QSpinBox *IndexNPC5;
    QSpinBox *IndexNPC6;
    QSpinBox *IndexNPC7;
    QSpinBox *IndexNPC8;
    QSpinBox *IndexNPC9;

    QSpinBox *IndexHL1;
    QSpinBox *IndexHL2;
    QSpinBox *IndexHL3;
    QSpinBox *IndexHL4;
    QSpinBox *IndexHL5;
    QSpinBox *IndexHL6;
    QSpinBox *IndexHL7;
    QSpinBox *IndexHL8;
    QSpinBox *IndexHL9;


    QLabel *MaxLV_L;
    QLabel *MinLV_L;
    QLabel *NTask_L;
    QLabel *HLCount_L;
    QLabel *NPC_L;
    QLabel *HL_L;

    QPushButton *SaveButton;
    QVBoxLayout *MainLayout;
    QHBoxLayout *NameLayout;

    QHBoxLayout *LabelLayout;
    QHBoxLayout *SpinLayout;

    QVBoxLayout *NPCLayout;
    QVBoxLayout *HLLayout;
    QHBoxLayout *BodyLayout;

  public:

    void Save();
    void Init();
    void read();

  public:
    MapWidget();
    ~MapWidget()
    {
    }
};

void MapWidget::read()
{
    int x=PosX->value();
    int y=PosY->value();

    MaxLV->setValue(SystemMap[x][y].MaxLV);
    MinLV->setValue(SystemMap[x][y].MinLV);
    NTask->setValue(SystemMap[x][y].NTask);
    HLCount->setValue(SystemMap[x][y].HLCount);

    IndexNPC1->setValue(SystemMap[x][y].IndexNPC[1]);
    IndexNPC2->setValue(SystemMap[x][y].IndexNPC[2]);
    IndexNPC3->setValue(SystemMap[x][y].IndexNPC[3]);
    IndexNPC4->setValue(SystemMap[x][y].IndexNPC[4]);
    IndexNPC5->setValue(SystemMap[x][y].IndexNPC[5]);
    IndexNPC6->setValue(SystemMap[x][y].IndexNPC[6]);
    IndexNPC7->setValue(SystemMap[x][y].IndexNPC[7]);
    IndexNPC8->setValue(SystemMap[x][y].IndexNPC[8]);
    IndexNPC9->setValue(SystemMap[x][y].IndexNPC[9]);

    IndexHL1->setValue(SystemMap[x][y].IndexHL[1]);
    IndexHL2->setValue(SystemMap[x][y].IndexHL[2]);
    IndexHL3->setValue(SystemMap[x][y].IndexHL[3]);
    IndexHL4->setValue(SystemMap[x][y].IndexHL[4]);
    IndexHL5->setValue(SystemMap[x][y].IndexHL[5]);
    IndexHL6->setValue(SystemMap[x][y].IndexHL[6]);
    IndexHL7->setValue(SystemMap[x][y].IndexHL[7]);
    IndexHL8->setValue(SystemMap[x][y].IndexHL[8]);
    IndexHL9->setValue(SystemMap[x][y].IndexHL[9]);
    Name->setText(SystemMap[x][y].Name);
    Des->setText(SystemMap[x][y].Des);
}

MapWidget::MapWidget()
{
    Name = new QLineEdit;
    Des = new QLineEdit;
    SaveButton = new QPushButton("保存");

    PosX = new QSpinBox;
    PosY = new QSpinBox;
    PosX->setRange(0, 25);
    PosY->setRange(0, 25);


    MaxLV = new QSpinBox;
    MaxLV->setRange(1, 99);
    MinLV = new QSpinBox;
    MinLV->setRange(1,99);
    NTask = new QSpinBox;
    NTask->setRange(0,199);
    HLCount = new QSpinBox;
    HLCount->setRange(0,9);

    IndexNPC1 = new QSpinBox;
    IndexNPC2 = new QSpinBox;
    IndexNPC3 = new QSpinBox;
    IndexNPC4 = new QSpinBox;
    IndexNPC5 = new QSpinBox;
    IndexNPC6 = new QSpinBox;
    IndexNPC7 = new QSpinBox;
    IndexNPC8 = new QSpinBox;
    IndexNPC9 = new QSpinBox;

    IndexHL1 = new QSpinBox;
    IndexHL2 = new QSpinBox;
    IndexHL3 = new QSpinBox;
    IndexHL4 = new QSpinBox;
    IndexHL5 = new QSpinBox;
    IndexHL6 = new QSpinBox;
    IndexHL7 = new QSpinBox;
    IndexHL8 = new QSpinBox;
    IndexHL9 = new QSpinBox;

    IndexNPC1->setRange(0,199);
    IndexNPC2->setRange(0,199);
    IndexNPC3->setRange(0,199);
    IndexNPC4->setRange(0,199);
    IndexNPC5->setRange(0,199);
    IndexNPC6->setRange(0,199);
    IndexNPC7->setRange(0,199);
    IndexNPC8->setRange(0,199);
    IndexNPC9->setRange(0,199);
    IndexHL1->setRange(0,199);
    IndexHL2->setRange(0,199);
    IndexHL3->setRange(0,199);
    IndexHL4->setRange(0,199);
    IndexHL5->setRange(0,199);
    IndexHL6->setRange(0,199);
    IndexHL7->setRange(0,199);
    IndexHL8->setRange(0,199);
    IndexHL9->setRange(0,199);

    NPC_L = new QLabel("人物：");
    HL_L = new QLabel("魂灵：");
    MaxLV_L = new QLabel("最高：");
    MinLV_L = new QLabel("最低：");
    NTask_L = new QLabel("任务：");
    HLCount_L = new QLabel("数量：");

    NPCLayout=new QVBoxLayout;
    HLLayout=new QVBoxLayout;

    MainLayout = new QVBoxLayout;
    NameLayout = new QHBoxLayout;
    LabelLayout = new QHBoxLayout;
    SpinLayout = new QHBoxLayout;
    BodyLayout = new QHBoxLayout;

    NameLayout->addWidget(Name);
    NameLayout->addWidget(PosX);
    NameLayout->addWidget(PosY);

    NPCLayout->addWidget(NPC_L);
    NPCLayout->addWidget(IndexNPC1);
    NPCLayout->addWidget(IndexNPC2);
    NPCLayout->addWidget(IndexNPC3);
    NPCLayout->addWidget(IndexNPC4);
    NPCLayout->addWidget(IndexNPC5);
    NPCLayout->addWidget(IndexNPC6);
    NPCLayout->addWidget(IndexNPC7);
    NPCLayout->addWidget(IndexNPC8);
    NPCLayout->addWidget(IndexNPC9);

    HLLayout->addWidget(HL_L);
    HLLayout->addWidget(IndexHL1);
    HLLayout->addWidget(IndexHL2);
    HLLayout->addWidget(IndexHL3);
    HLLayout->addWidget(IndexHL4);
    HLLayout->addWidget(IndexHL5);
    HLLayout->addWidget(IndexHL6);
    HLLayout->addWidget(IndexHL7);
    HLLayout->addWidget(IndexHL8);
    HLLayout->addWidget(IndexHL9);

    LabelLayout->addWidget(MaxLV_L);
    LabelLayout->addWidget(MinLV_L);
    LabelLayout->addWidget(NTask_L);
    LabelLayout->addWidget(HLCount_L);

    SpinLayout->addWidget(MaxLV);
    SpinLayout->addWidget(MinLV);
    SpinLayout->addWidget(NTask);
    SpinLayout->addWidget(HLCount);


    BodyLayout->addLayout(NPCLayout);
    BodyLayout->addLayout(HLLayout);
    MainLayout->addLayout(NameLayout);
    MainLayout->addWidget(Des);
    MainLayout->addLayout(BodyLayout);
    MainLayout->addLayout(LabelLayout);
    MainLayout->addLayout(SpinLayout);
    MainLayout->addWidget(SaveButton);

    this->setLayout(MainLayout);
    Init();
    connect(SaveButton, &QPushButton::clicked, this, &MapWidget::Save);
   connect(PosX, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MapWidget::read);
   connect(PosY, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MapWidget::read);
    connect(Name, &QLineEdit::textEdited, this, &MapWidget::Save);
    connect(Des, &QLineEdit::textEdited, this, &MapWidget::Save);

}

void MapWidget::Save()
{

    int x=PosX->value();
    int y=PosY->value();
    SystemMap[x][y].PosX = PosX->value();
    SystemMap[x][y].PosY = PosY->value();
    SystemMap[x][y].Name = Name->text();
    SystemMap[x][y].Des = Des->text();

    SystemMap[x][y].MaxLV = MaxLV->value();
    SystemMap[x][y].MinLV = MinLV->value();
    SystemMap[x][y].NTask = NTask->value();
    SystemMap[x][y].HLCount = HLCount->value();

    SystemMap[x][y].IndexNPC[1]=IndexNPC1->value();
    SystemMap[x][y].IndexNPC[2]=IndexNPC2->value();
    SystemMap[x][y].IndexNPC[3]=IndexNPC3->value();
    SystemMap[x][y].IndexNPC[4]=IndexNPC4->value();
    SystemMap[x][y].IndexNPC[5]=IndexNPC5->value();
    SystemMap[x][y].IndexNPC[6]=IndexNPC6->value();
    SystemMap[x][y].IndexNPC[7]=IndexNPC7->value();
    SystemMap[x][y].IndexNPC[8]=IndexNPC8->value();
    SystemMap[x][y].IndexNPC[9]=IndexNPC9->value();

    SystemMap[x][y].IndexHL[1]=IndexHL1->value();
    SystemMap[x][y].IndexHL[2]=IndexHL2->value();
    SystemMap[x][y].IndexHL[3]=IndexHL3->value();
    SystemMap[x][y].IndexHL[4]=IndexHL4->value();
    SystemMap[x][y].IndexHL[5]=IndexHL5->value();
    SystemMap[x][y].IndexHL[6]=IndexHL6->value();
    SystemMap[x][y].IndexHL[7]=IndexHL7->value();
    SystemMap[x][y].IndexHL[8]=IndexHL8->value();
    SystemMap[x][y].IndexHL[9]=IndexHL9->value();



    SystemMap[1][1].Save();
}

void MapWidget::Init()
{

    SystemMap[1][1].Init();



}


