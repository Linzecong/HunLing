#include<QString>
#include "Global.h"






class HLWidget:public QWidget

{
    // Q_OBJECT
  private:
    QLineEdit * Name;
    QLineEdit *Des;


    QSpinBox* ID;
    QSpinBox* Strength;
    QSpinBox* Agility;
    QSpinBox* K_Fire;
    QSpinBox* K_Ice;
    QSpinBox* K_Lig;
    QSpinBox* K_Tox;
    QSpinBox* G_Fire;
    QSpinBox* G_Ice;
    QSpinBox* G_Lig;
    QSpinBox* G_Tox;
    QSpinBox* ATK_Str;
    QSpinBox* ATK_Agi;
    QSpinBox* DEF_Str;
    QSpinBox* DEF_Agi;
    QSpinBox* VIT_Vit;
    QSpinBox* DEF_Ski;
    QSpinBox* ATK_Ski;
    QSpinBox* DropItem[10];


    QLabel* Fire_L;
    QLabel* Ice_L;
    QLabel* Lig_L;
    QLabel* Tox_L;
    QLabel* ATK_Str_L;
    QLabel* ATK_Agi_L;
    QLabel* DEF_Str_L;
    QLabel* DEF_Agi_L;
    QLabel* VIT_Vit_L;
    QLabel* DropItem_L;


    QListWidget *HLList;

    QPushButton *SaveButton;

    QVBoxLayout *MainLayout;
    QHBoxLayout *NameLayout;
    QHBoxLayout *DesLayout;

    QVBoxLayout *SpinLayout;
    QHBoxLayout *BodyLayout;

    QHBoxLayout *LabelLayout;
    QHBoxLayout *KSpinLayout;
    QHBoxLayout *GSpinLayout;
    QHBoxLayout *PointLayout_L;
    QHBoxLayout *PointLayout_S;



  public:

    void Save();
    void Init();
    void read();
    void Change()
    {
        int a = HLList->currentRow();
        HLList->selectedItems().first()->setText(Name->text());
    }
  public:
    HLWidget();
    ~HLWidget()
    {
    }
};

void HLWidget::read()
{
    int a=HLList->currentRow();
    Name->setText(SystemHL[a].Name);
    Des->setText(SystemHL[a].Des);
    ID->setValue(a);
    Strength->setValue(SystemHL[a].Strength);
    Agility->setValue(SystemHL[a].Agility);
    K_Fire->setValue(SystemHL[a].K_Fire);
    K_Ice->setValue(SystemHL[a].K_Ice);
    K_Lig->setValue(SystemHL[a].K_Lig);
    K_Tox->setValue(SystemHL[a].K_Tox);
    G_Fire->setValue(SystemHL[a].G_Fire);
    G_Ice->setValue(SystemHL[a].G_Ice);
    G_Lig->setValue(SystemHL[a].G_Lig);
    G_Tox->setValue(SystemHL[a].G_Tox);
    ATK_Str->setValue(SystemHL[a].ATK_Str);
    ATK_Agi->setValue(SystemHL[a].ATK_Agi);
    DEF_Str->setValue(SystemHL[a].DEF_Str);
    DEF_Agi->setValue(SystemHL[a].DEF_Agi);
    VIT_Vit->setValue(SystemHL[a].VIT_Vit);
    DEF_Ski->setValue(SystemHL[a].DEF_Ski);
    ATK_Ski->setValue(SystemHL[a].ATK_Ski);
    for(int j=1;j<=9;j++)
    DropItem[j]->setValue(SystemHL[a].DropItem[j]);
}

HLWidget::HLWidget()
{
    Name = new QLineEdit("名字");
    Des = new QLineEdit("介绍");
    SaveButton = new QPushButton("保存");
    HLList=new QListWidget;
    ID=new QSpinBox;
    ID->setRange(0,199);
    ID->setEnabled(false);

    Strength=new QSpinBox;
    Agility=new QSpinBox;
    K_Fire=new QSpinBox;
    K_Ice=new QSpinBox;
    K_Lig=new QSpinBox;
    K_Tox=new QSpinBox;
    G_Fire=new QSpinBox;
    G_Ice=new QSpinBox;
    G_Lig=new QSpinBox;
    G_Tox=new QSpinBox;
    ATK_Str=new QSpinBox;
    ATK_Agi=new QSpinBox;
    DEF_Str=new QSpinBox;
    DEF_Agi=new QSpinBox;
    VIT_Vit=new QSpinBox;
    DEF_Ski=new QSpinBox;
    ATK_Ski=new QSpinBox;
    for(int j=1;j<=9;j++)
    DropItem[j]=new QSpinBox;

    Fire_L=new QLabel("火：");
    Ice_L=new QLabel("冰：");
    Lig_L=new QLabel("电：");
    Tox_L=new QLabel("毒：");
    ATK_Str_L=new QLabel("攻力：");
    ATK_Agi_L=new QLabel("攻敏：");
    DEF_Str_L=new QLabel("防力");
    DEF_Agi_L=new QLabel("防敏");
    VIT_Vit_L=new QLabel("生体");
    DropItem_L=new QLabel("掉落：");


    Strength->setRange(0,50);
    Agility->setRange(0,50);
    K_Fire->setRange(0,50);
    K_Ice->setRange(0,50);
    K_Lig->setRange(0,50);
    K_Tox->setRange(0,50);
    G_Fire->setRange(0,50);
    G_Ice->setRange(0,50);
    G_Lig->setRange(0,50);
    G_Tox->setRange(0,50);
    ATK_Str->setRange(0,50);
    ATK_Agi->setRange(0,50);
    DEF_Str->setRange(0,50);
    DEF_Agi->setRange(0,50);
    VIT_Vit->setRange(0,50);
    DEF_Ski->setRange(1,199);
    ATK_Ski->setRange(1,199);
    for(int j=1;j<=9;j++)
    DropItem[j]->setRange(0,199);



    MainLayout=new QVBoxLayout;
    NameLayout=new QHBoxLayout;
    DesLayout=new QHBoxLayout;
    SpinLayout=new QVBoxLayout ;
    BodyLayout=new QHBoxLayout;
    LabelLayout=new QHBoxLayout;
    KSpinLayout=new QHBoxLayout;
    GSpinLayout=new QHBoxLayout;
    PointLayout_L=new QHBoxLayout;
    PointLayout_S=new QHBoxLayout;

    NameLayout->addWidget(ID);
    NameLayout->addWidget(Name);
    NameLayout->addWidget(Strength);
    NameLayout->addWidget(Agility);

    DesLayout->addWidget(Des);
    DesLayout->addWidget(ATK_Ski);
    DesLayout->addWidget(DEF_Ski);
    SpinLayout->addWidget(DropItem_L);
    for(int j=1;j<=9;j++)
    SpinLayout->addWidget(DropItem[j]);

    BodyLayout->addWidget(HLList);
    BodyLayout->addLayout(SpinLayout);

    LabelLayout->addWidget(Fire_L);
    LabelLayout->addWidget(Ice_L);
    LabelLayout->addWidget(Lig_L);
    LabelLayout->addWidget(Tox_L);

    KSpinLayout->addWidget(K_Fire);
    KSpinLayout->addWidget(K_Ice);
    KSpinLayout->addWidget(K_Lig);
    KSpinLayout->addWidget(K_Tox);
    GSpinLayout->addWidget(G_Fire);
    GSpinLayout->addWidget(G_Ice);
    GSpinLayout->addWidget(G_Lig);
    GSpinLayout->addWidget(G_Tox);


    PointLayout_L->addWidget(ATK_Str_L);
    PointLayout_L->addWidget(ATK_Agi_L);
    PointLayout_L->addWidget(DEF_Str_L);
    PointLayout_L->addWidget(DEF_Agi_L);
    PointLayout_L->addWidget(VIT_Vit_L);

    PointLayout_S->addWidget(ATK_Str);
    PointLayout_S->addWidget(ATK_Agi);
    PointLayout_S->addWidget(DEF_Str);
    PointLayout_S->addWidget(DEF_Agi);
    PointLayout_S->addWidget(VIT_Vit);



    MainLayout->addLayout(NameLayout);
    MainLayout->addLayout(DesLayout);
    MainLayout->addLayout(BodyLayout);
    MainLayout->addLayout(LabelLayout);
    MainLayout->addLayout(KSpinLayout);
    MainLayout->addLayout(GSpinLayout);
    MainLayout->addLayout(PointLayout_L);
    MainLayout->addLayout(PointLayout_S);
    MainLayout->addWidget(SaveButton);

    this->setLayout(MainLayout);
    Init();
    connect(SaveButton, &QPushButton::clicked, this, &HLWidget::Save);
    connect(HLList, &QListWidget::clicked, this, &HLWidget::Save);
    connect(HLList, &QListWidget::clicked, this, &HLWidget::read);
    connect(Name, &QLineEdit::textChanged, this, &HLWidget::Change);

}


void HLWidget::Save()
{

    int a=ID->value();
    SystemHL[a].Name=Name->text();
    SystemHL[a].Des=Des->text();
    SystemHL[a].Strength=Strength->value();
    SystemHL[a].Agility=Agility->value();
    SystemHL[a].K_Fire=K_Fire->value();
    SystemHL[a].K_Ice=K_Ice->value();
    SystemHL[a].K_Lig=K_Lig->value();
    SystemHL[a].K_Tox=K_Tox->value();
    SystemHL[a].G_Fire=G_Fire->value();
    SystemHL[a].G_Ice=G_Ice->value();
    SystemHL[a].G_Lig=G_Lig->value();
    SystemHL[a].G_Tox=G_Tox->value();
    SystemHL[a].ATK_Str=ATK_Str->value();
    SystemHL[a].ATK_Agi=ATK_Agi->value();
    SystemHL[a].DEF_Str=DEF_Str->value();
    SystemHL[a].DEF_Agi=DEF_Agi->value();
    SystemHL[a].VIT_Vit=VIT_Vit->value();
    SystemHL[a].DEF_Ski=DEF_Ski->value();
    SystemHL[a].ATK_Ski=ATK_Ski->value();
    for(int j=1;j<=9;j++)
    SystemHL[a].DropItem[j]=DropItem[j]->value();
    SystemHL[1].Save();
}
void HLWidget::Init()
{
    HLList->clear();
    SystemHL[1].Init();

    for(int i=0;i<200;i++)
    {
    SystemHL[i].ID=i;
    HLList->addItem(SystemHL[i].Name);
    }

}








