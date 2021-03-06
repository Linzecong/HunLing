#include "Global.h"

class NPCWidget:public QWidget

{
    // Q_OBJECT
  private:
    QLineEdit * Name;
    QLineEdit *Des;


    QSpinBox* ID;
    QSpinBox* LV;
    QSpinBox* Ori_Strength;
    QSpinBox* Ori_Agility;
    QSpinBox* Ori_Vitality;
    QSpinBox* Ori_Energy;
    QSpinBox* Ori_Sour;
    QSpinBox* CanATK;
    QSpinBox* TaskShow;
    QSpinBox* LHID[10];
    QSpinBox* LHLV[10];
    QSpinBox* LGID[7];
    QSpinBox* LGLV[7];
    QSpinBox* CanTalk[20];
    QSpinBox* Task[10];

    QLabel* Ori_Strength_L;
    QLabel* Ori_Agility_L;
    QLabel* Ori_Vitality_L;
    QLabel* Ori_Energy_L;
    QLabel* Ori_Sour_L;

   QLabel* Message;
   QLabel* Task_L;
    QLabel* LHID_L;
    QLabel* LHLV_L;
    QLabel* LGID_L;
    QLabel* LGLV_L;
    QLabel* Head;
    QLabel* Body;
    QLabel* LHand;
    QLabel* RHand;
    QLabel* LLeg;
    QLabel* RLeg;



    QListWidget *NPCList;
    QWidget *LHLGWidget;

    QPushButton *SaveButton;
    QPushButton *LHLGButton;

    QVBoxLayout *MainLayout;
    QHBoxLayout *MainLayoutLHLG;
    QHBoxLayout *NameLayout;
    QHBoxLayout *DesLayout;

    QVBoxLayout *SpinLayout1;
    QVBoxLayout *SpinLayout2;
    QVBoxLayout *SpinLayout3;

    QHBoxLayout *BodyLayout;
    QHBoxLayout *LabelLayout1;
    QHBoxLayout *SpinLayout4;
    QHBoxLayout *ButtonLayout;

    QVBoxLayout *LabelLayout2;

    QVBoxLayout *SpinLayoutLHID;
    QVBoxLayout *SpinLayoutLHLV;
    QVBoxLayout *SpinLayoutLGID;
    QVBoxLayout *SpinLayoutLGLV;



  public:

    void Save();
    void ShowWidget(){LHLGWidget->show();}
    void Init();
    void read();
    void Change()
    {
        int a = NPCList->currentRow();
        NPCList->selectedItems().first()->setText(Name->text());
    }
  public:
    NPCWidget();
    ~NPCWidget()
    {
    }
};

void NPCWidget::read()
{


    int a=NPCList->currentRow();
    Name->setText(SystemNPC[a].Name);
    Des->setText(SystemNPC[a].Des);
    ID->setValue(a);

    LV->setValue(SystemNPC[a].LV);
    Ori_Strength->setValue(SystemNPC[a].Ori_Strength);
    Ori_Agility->setValue(SystemNPC[a].Ori_Agility);
    Ori_Vitality->setValue(SystemNPC[a].Ori_Vitality);
    Ori_Energy->setValue(SystemNPC[a].Ori_Energy);
    Ori_Sour->setValue(SystemNPC[a].Ori_Sour);
    CanATK->setValue(SystemNPC[a].CanATK);
    TaskShow->setValue(SystemNPC[a].TaskShow);
    for(int j=1;j<=9;j++)
    {
    LHID[j]->setValue(SystemNPC[a].LHID[j]);
    LHLV[j]->setValue(SystemNPC[a].LHLV[j]);
    Task[j]->setValue(SystemNPC[a].Task[j]);
    }
    for(int j=1;j<=6;j++)
    {
    LGID[j]->setValue(SystemNPC[a].LGID[j]);
    LGLV[j]->setValue(SystemNPC[a].LGLV[j]);
    }
    for(int j=1;j<=19;j++)
    CanTalk[j]->setValue(SystemNPC[a].CanTalk[j]);



}

NPCWidget::NPCWidget()
{
    Name = new QLineEdit("名字");
    Des = new QLineEdit("介绍");
    SaveButton = new QPushButton("保存");
    LHLGButton = new QPushButton("LHLG");
    NPCList=new QListWidget;
    ID=new QSpinBox;
    ID->setRange(0,199);
    ID->setEnabled(false);

    LV=new QSpinBox;
    Ori_Strength=new QSpinBox;
    Ori_Agility=new QSpinBox;
    Ori_Vitality=new QSpinBox;
    Ori_Energy=new QSpinBox;
    Ori_Sour=new QSpinBox;
    CanATK=new QSpinBox;
    TaskShow=new QSpinBox;
    for(int j=1;j<=9;j++)
    {
    LHID[j]=new QSpinBox;
    LHLV[j]=new QSpinBox;
    Task[j]=new QSpinBox;
    }
    for(int j=1;j<=6;j++)
    {
    LGID[j]=new QSpinBox;
    LGLV[j]=new QSpinBox;
    }
    for(int j=1;j<=19;j++)
    CanTalk[j]=new QSpinBox;

    Ori_Strength->setRange(0,450);
    Ori_Agility->setRange(10,450);
    Ori_Vitality->setRange(10,450);
    Ori_Energy->setRange(100,5000);
    Ori_Sour->setRange(0,1000);
    CanATK->setRange(0,1);
    TaskShow->setRange(0,200);
    for(int j=1;j<=9;j++)
    {
    LHID[j]->setRange(0,199);
    LHLV[j]->setRange(0,99);
    Task[j]->setRange(0,199);
    }
    for(int j=1;j<=6;j++)
    {
    LGID[j]->setRange(0,199);
    LGLV[j]->setRange(0,99);
    }
    for(int j=1;j<=19;j++)
    CanTalk[j]->setRange(0,500);


   Task_L=new QLabel("任务：");
     Message=new QLabel("消息：");

    Ori_Strength_L=new QLabel("力量：");
    Ori_Agility_L=new QLabel("敏捷：");
    Ori_Vitality_L=new QLabel("体力：");
    Ori_Energy_L=new QLabel("魂力：");
    Ori_Sour_L=new QLabel("灵力：");

    LHID_L=new QLabel("LHID：");
    LHLV_L=new QLabel("LHLV：");
    LGID_L=new QLabel("LGID：");
    LGLV_L=new QLabel("LGLV：");
    Head=new QLabel("头部：");
    Body=new QLabel("躯干：");
    LHand=new QLabel("左臂：");
    RHand=new QLabel("右臂：");
    LLeg=new QLabel("左腿：");
    RLeg=new QLabel("右腿：");



    NPCList=new QListWidget;
    LHLGWidget=new QWidget;

    SaveButton=new QPushButton;
    LHLGButton=new QPushButton;





    MainLayout=new QVBoxLayout;
    MainLayoutLHLG=new QHBoxLayout;
    NameLayout=new QHBoxLayout;
    DesLayout=new QHBoxLayout;

    SpinLayout1=new QVBoxLayout;
    SpinLayout2=new QVBoxLayout;
    SpinLayout3=new QVBoxLayout;
    SpinLayout4=new QHBoxLayout;
    ButtonLayout=new QHBoxLayout;
    BodyLayout=new QHBoxLayout;
    LabelLayout1=new QHBoxLayout;
    LabelLayout2=new QVBoxLayout;

   
    SpinLayoutLHID=new QVBoxLayout;
    SpinLayoutLHLV=new QVBoxLayout;
    SpinLayoutLGID=new QVBoxLayout;
    SpinLayoutLGLV=new QVBoxLayout;





    NameLayout->addWidget(ID);
    NameLayout->addWidget(Name);
    NameLayout->addWidget(LV);


    DesLayout->addWidget(Des);
    DesLayout->addWidget(CanATK);
    DesLayout->addWidget(TaskShow);

SpinLayout1->addWidget(Message);
    for(int j=1;j<=9;j++)
    SpinLayout1->addWidget(CanTalk[j]);
    for(int j=10;j<=19;j++)
    SpinLayout2->addWidget(CanTalk[j]);
    SpinLayout3->addWidget(Task_L);
    for(int j=1;j<=9;j++)
    SpinLayout3->addWidget(Task[j]);


    LabelLayout1->addWidget(Ori_Strength_L);
    LabelLayout1->addWidget(Ori_Agility_L);
    LabelLayout1->addWidget(Ori_Vitality_L);
    LabelLayout1->addWidget(Ori_Energy_L);
    LabelLayout1->addWidget(Ori_Sour_L);

    SpinLayout4->addWidget(Ori_Strength);
    SpinLayout4->addWidget(Ori_Agility);
    SpinLayout4->addWidget(Ori_Vitality);
    SpinLayout4->addWidget(Ori_Energy);
    SpinLayout4->addWidget(Ori_Sour);

    ButtonLayout->addWidget(SaveButton);
    ButtonLayout->addWidget(LHLGButton);

    BodyLayout->addWidget(NPCList);
    BodyLayout->addLayout(SpinLayout1);
    BodyLayout->addLayout(SpinLayout2);
    BodyLayout->addLayout(SpinLayout3);


    MainLayout->addLayout(NameLayout);
    MainLayout->addLayout(DesLayout);
    MainLayout->addLayout(BodyLayout);
    MainLayout->addLayout(LabelLayout1);
    MainLayout->addLayout(SpinLayout4);
    MainLayout->addLayout(ButtonLayout);
   
   SpinLayoutLHID->addWidget(LHID_L);
    SpinLayoutLHLV->addWidget(LHLV_L);
    for(int i=1;i<=9;i++)
    {
    SpinLayoutLHID->addWidget(LHID[i]);
    SpinLayoutLHLV->addWidget(LHLV[i]);
    }
//    SpinLayoutLGID->addWidget(LGID_L);
//    SpinLayoutLGLV->addWidget(LGLV_L);
      for(int i=1;i<=6;i++)
    {
    SpinLayoutLGID->addWidget(LGID[i]);
    SpinLayoutLGLV->addWidget(LGLV[i]);
    }
LabelLayout2->addWidget(Head);
LabelLayout2->addWidget(Body);
LabelLayout2->addWidget(LHand);
LabelLayout2->addWidget(RHand);
LabelLayout2->addWidget(LLeg);
LabelLayout2->addWidget(RLeg);
    MainLayoutLHLG->addLayout(SpinLayoutLHID);
    MainLayoutLHLG->addLayout(SpinLayoutLHLV);
    MainLayoutLHLG->addLayout(LabelLayout2);
    MainLayoutLHLG->addLayout(SpinLayoutLGID);
    MainLayoutLHLG->addLayout(SpinLayoutLGLV);



    this->setLayout(MainLayout);
    LHLGWidget->setLayout(MainLayoutLHLG);
    Init();

    connect(SaveButton, &QPushButton::clicked, this, &NPCWidget::Save);
    connect(LHLGButton, &QPushButton::clicked, this, &NPCWidget::ShowWidget);
    connect(NPCList, &QListWidget::clicked, this, &NPCWidget::Save);
    connect(NPCList, &QListWidget::clicked, this, &NPCWidget::read);
    connect(Name, &QLineEdit::textChanged, this, &NPCWidget::Change);

}



void NPCWidget::Save()
{
    int a=ID->value();
    SystemNPC[a].Name=Name->text();
    SystemNPC[a].Des=Des->text();
    SystemNPC[a].LV=LV->value();
    SystemNPC[a].Ori_Strength=Ori_Strength->value();
    SystemNPC[a].Ori_Agility=Ori_Agility->value();
    SystemNPC[a].Ori_Vitality=Ori_Vitality->value();
    SystemNPC[a].Ori_Energy=Ori_Energy->value();
    SystemNPC[a].Ori_Sour=Ori_Sour->value();
    SystemNPC[a].CanATK=CanATK->value();
    SystemNPC[a].TaskShow=TaskShow->value();

    for(int j=1;j<=9;j++)
    {
    SystemNPC[a].LHID[j]=LHID[j]->value();
    SystemNPC[a].LHLV[j]=LHLV[j]->value();
    SystemNPC[a].Task[j]=Task[j]->value();
    }
    for(int j=1;j<=6;j++)
    {
    SystemNPC[a].LGID[j]=LGID[j]->value();
    SystemNPC[a].LGLV[j]=LGLV[j]->value();
    }
    for(int j=1;j<=19;j++)
    SystemNPC[a].CanTalk[j]=CanTalk[j]->value();
    SystemNPC[1].Save();
}
void NPCWidget::Init()
{
    NPCList->clear();
    SystemNPC[1].Init();


    for(int i=0;i<200;i++)
    {
    SystemNPC[i].ID=i;
    NPCList->addItem(SystemNPC[i].Name);
    }

}





