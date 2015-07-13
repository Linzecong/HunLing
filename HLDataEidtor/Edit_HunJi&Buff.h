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

class SkillWidget:public QWidget

{
    // Q_OBJECT
  private:
    QLineEdit * Name_HJ;
    QLineEdit *Des_HJ;
    QLineEdit * Name_Buff;
    QLineEdit *Des_Buff;

    QSpinBox *ID_HJ;
    QSpinBox *Type_HJ;
    QSpinBox *Energy_HJ;
    QSpinBox *Sour_HJ;
    QSpinBox *Turn_HJ;

    QSpinBox *ID_Buff;
    QSpinBox *type_Buff;


    QLabel *Type_HJ_L;
    QLabel *Energy_HJ_L;
    QLabel *Sour_HJ_L;
    QLabel *Turn_HJ_L;

    QLabel *ID_Buff_L;
    QLabel *type_Buff_L;


    QListWidget *HJList;
    QListWidget *BuffList;

    QPushButton *SaveButton;
    QVBoxLayout *MainLayout;

    QHBoxLayout *NameLayout_HJ;
    QHBoxLayout *NameLayout_Buff;
    QVBoxLayout *LabelLayout_HJ;
    QVBoxLayout *LabelLayout_Buff;
    QVBoxLayout *SpinLayout_HJ;
    QVBoxLayout *SpinLayout_Buff;

    QHBoxLayout *BodyLayout_HJ;
    QHBoxLayout *BodyLayout_Buff;

  public:

    void Save();
    void Init();
    void read();
    void Change()
    {
        int a = HJList->currentRow();
        HJList->selectedItems().first()->setText(Name_HJ->text());
         a = BuffList->currentRow();
        BuffList->selectedItems().first()->setText(Name_Buff->text());
    }
  public:
    SkillWidget();
    ~SkillWidget()
    {
    }
};

void SkillWidget::read()
{
    int a = HJList->currentRow();
    Name_HJ->setText(SystemHJ[a].Name);
    Des_HJ->setText(SystemHJ[a].Des);
    ID_HJ->setValue(a);
    Type_HJ->setValue(SystemHJ[a].Type);
    Energy_HJ->setValue(SystemHJ[a].Energy);
    Sour_HJ->setValue(SystemHJ[a].Sour);
    Turn_HJ->setValue(SystemHJ[a].Turn);


    a = BuffList->currentRow();
    Name_Buff->setText(SystemBuff[a].Name);
    Des_Buff->setText(SystemBuff[a].Des);
    ID_Buff->setValue(a);
    type_Buff->setValue(SystemBuff[a].type);

}


SkillWidget::SkillWidget()
{
    Name_HJ = new QLineEdit("名字");
    Des_HJ = new QLineEdit("介绍");
    Name_Buff = new QLineEdit("名字");
    Des_Buff = new QLineEdit("介绍");
    SaveButton = new QPushButton("保存");
    HJList = new QListWidget;
    BuffList = new QListWidget;
    ID_Buff = new QSpinBox;
    ID_Buff->setRange(0, 199);
    ID_Buff->setEnabled(false);
    ID_HJ = new QSpinBox;
    ID_HJ->setRange(0, 199);
    ID_HJ->setEnabled(false);

    Type_HJ = new QSpinBox;
    Type_HJ->setRange(1, 5);
    type_Buff = new QSpinBox;
    type_Buff->setRange(1, 5);

    Energy_HJ = new QSpinBox;
    Energy_HJ->setRange(0, 1000);
    Energy_HJ->setSingleStep(10);

    Sour_HJ = new QSpinBox;
    Sour_HJ->setRange(0, 50);
    Turn_HJ = new QSpinBox;
    Turn_HJ->setRange(0, 20);



    Type_HJ_L = new QLabel("类型：");
    Energy_HJ_L = new QLabel("魂力：");
    Sour_HJ_L = new QLabel("灵力：");
    Turn_HJ_L = new QLabel("回合：");

    type_Buff_L = new QLabel("类型：");



    MainLayout = new QVBoxLayout;

    NameLayout_HJ = new QHBoxLayout;
    NameLayout_Buff = new QHBoxLayout;
    LabelLayout_Buff = new QVBoxLayout;
    LabelLayout_HJ = new QVBoxLayout;
    SpinLayout_Buff = new QVBoxLayout;
    SpinLayout_HJ = new QVBoxLayout;
    BodyLayout_Buff = new QHBoxLayout;
    BodyLayout_HJ = new QHBoxLayout;
    NameLayout_HJ->addWidget(ID_HJ);
    NameLayout_HJ->addWidget(Name_HJ);
    NameLayout_Buff->addWidget(ID_Buff);
    NameLayout_Buff->addWidget(Name_Buff);
    LabelLayout_HJ->addWidget(Type_HJ_L);
    LabelLayout_HJ->addWidget(Energy_HJ_L);
    LabelLayout_HJ->addWidget(Sour_HJ_L);
    LabelLayout_HJ->addWidget(Turn_HJ_L);

    LabelLayout_Buff->addWidget(type_Buff_L);

    SpinLayout_HJ->addWidget(Type_HJ);
    SpinLayout_HJ->addWidget(Energy_HJ);
    SpinLayout_HJ->addWidget(Sour_HJ);
    SpinLayout_HJ->addWidget(Turn_HJ);
    SpinLayout_Buff->addWidget(type_Buff);


    BodyLayout_HJ->addWidget(HJList);
    BodyLayout_HJ->addLayout(LabelLayout_HJ);
    BodyLayout_HJ->addLayout(SpinLayout_HJ);

    BodyLayout_Buff->addWidget(BuffList);
    BodyLayout_Buff->addLayout(LabelLayout_Buff);
    BodyLayout_Buff->addLayout(SpinLayout_Buff);

    MainLayout->addLayout(NameLayout_HJ);
    MainLayout->addWidget(Des_HJ);
    MainLayout->addLayout(BodyLayout_HJ);
    MainLayout->addLayout(NameLayout_Buff);
    MainLayout->addWidget(Des_Buff);
    MainLayout->addLayout(BodyLayout_Buff);
    MainLayout->addWidget(SaveButton);

    this->setLayout(MainLayout);
      Init();
    connect(SaveButton, &QPushButton::clicked, this, &SkillWidget::Save);
    connect(HJList, &QListWidget::clicked, this, &SkillWidget::Save);
    connect(HJList, &QListWidget::clicked, this, &SkillWidget::read);
    connect(Name_HJ, &QLineEdit::textChanged, this, &SkillWidget::Change);

    connect(BuffList, &QListWidget::clicked, this, &SkillWidget::Save);
    connect(BuffList, &QListWidget::clicked, this, &SkillWidget::read);
    connect(Name_Buff, &QLineEdit::textChanged, this, &SkillWidget::Change);

}

void SkillWidget::Save()
{

    int a = ID_HJ->value();
    SystemHJ[a].Name = Name_HJ->text();
    SystemHJ[a].Des = Des_HJ->text();
    SystemHJ[a].Type = Type_HJ->value();
    SystemHJ[a].Energy = Energy_HJ->value();
    SystemHJ[a].Sour = Sour_HJ->value();
    SystemHJ[a].Turn = Turn_HJ->value();
    a = ID_Buff->value();
    SystemBuff[a].Name = Name_Buff->text();
    SystemBuff[a].Des = Des_Buff->text();
    SystemBuff[a].type = type_Buff->value();

    SystemHJ[1].Save();
    SystemBuff[1].Save();
}

void SkillWidget::Init()
{
    
    SystemHJ[1].Init();

    for (int i = 0; i < 200; i++)
    {
        SystemHJ[i].ID = i;
        HJList->addItem(SystemHJ[i].Name);
    }

    
    SystemBuff[1].Init();

    for (int i = 0; i < 200; i++)
    {
        SystemBuff[i].ID = i;
        BuffList->addItem(SystemBuff[i].Name);
    }

HJList->setCurrentRow(1);
      BuffList->setCurrentRow(1);
  
}












