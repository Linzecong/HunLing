
#include "Global.h"
class TaskWidget:public QWidget
{
	//Q_OBJECT
  private:
	QLineEdit *Name;
	QLineEdit *Des;
	QSpinBox *ID;
	QSpinBox *Need_ID;
	QSpinBox *MB;
	QSpinBox *NKillHL;
	QSpinBox *NKillNPC;
	QSpinBox *NTalkNPC;
    QSpinBox *NGetItem;
	QSpinBox *A_Coin;
	QSpinBox *A_Exp;
	QSpinBox *A_Item;
	QSpinBox *A_Count;
	
	QLabel *Need_ID_L;
	QLabel *MB_L;
	QLabel *NKillHL_L;
	QLabel *NKillNPC_L;
	QLabel *NTalkNPC_L;
    QLabel *NGetItem_L;
	QLabel *A_Coin_L;
	QLabel *A_Exp_L;
	QLabel *A_Item_L;
	QLabel *A_Count_L;
	QListWidget *TaskList;
	QPushButton *SaveButton;
	QVBoxLayout *MainLayout;
	QHBoxLayout *NameLayout;
	QVBoxLayout *LabelLayout;
	QVBoxLayout *SpinLayout;
	QHBoxLayout *BodyLayout;
	
  public:
    
    void Save();
    void Init();
    void read();
    void Change(){	int a=TaskList->currentRow();
	TaskList->selectedItems().first()->setText(Name->text());}
  public:
	  TaskWidget();
	 ~ TaskWidget(){}
};

void TaskWidget::read()
{
	int a=TaskList->currentRow();
	TaskList->selectedItems().first()->setText(SystemTask[a].Name);
	Name->setText(SystemTask[a].Name);
	Des->setText(SystemTask[a].Des);
	ID->setValue(a);
	Need_ID->setValue(SystemTask[a].Need_ID);
	Need_ID_L->setText("需 "+SystemTask[SystemTask[a].Need_ID].Name);
	MB->setValue(SystemTask[a].MB);
	NKillHL->setValue(SystemTask[a].NKillHL);
	NKillNPC->setValue(SystemTask[a].NKillNPC);
	NTalkNPC->setValue(SystemTask[a].NTalkNPC);
    NGetItem->setValue(SystemTask[a].NGetItem);
	A_Coin->setValue(SystemTask[a].A_Coin);
	A_Exp->setValue(SystemTask[a].A_Exp);
	A_Item->setValue(SystemTask[a].A_Item);
	A_Count->setValue(SystemTask[a].A_Count);
}
TaskWidget::TaskWidget()
{
	Name = new QLineEdit("名字");
	Des = new QLineEdit("介绍");  
    SaveButton = new QPushButton("保存");
    TaskList=new QListWidget;
	ID=new QSpinBox;
	ID->setRange(0,199);
	ID->setEnabled(false);
	
	Need_ID=new QSpinBox;
	Need_ID->setRange(0,199);
	
	MB=new QSpinBox;
    MB->setRange(0,50);
	NKillHL=new QSpinBox;
	NKillHL->setRange(0,199);
	NKillNPC=new QSpinBox;
	NKillNPC->setRange(0,199);
	NTalkNPC=new QSpinBox;
	NTalkNPC->setRange(0,199);
    NGetItem=new QSpinBox;
    NGetItem->setRange(0,199);
    A_Coin=new QSpinBox;
    A_Coin->setRange(0,999999);
    A_Coin->setSingleStep(10);
	A_Exp=new QSpinBox;
    A_Exp->setRange(0,999999);
	A_Exp->setSingleStep(10);
	A_Item=new QSpinBox;
	A_Item->setRange(0,199);
	A_Count=new QSpinBox;
	A_Count->setRange(0,20);
	
	Need_ID_L=new QLabel("需ID：");
    MB_L=new QLabel("目标");
	NKillHL_L=new QLabel("杀魂灵：");
	NKillNPC_L=new QLabel("杀NPC：");
	NTalkNPC_L=new QLabel("谈NPC：");
    NGetItem_L=new QLabel("需道具：");
	A_Coin_L=new QLabel("奖金币：");
	A_Exp_L=new QLabel("奖经验：");
	A_Item_L=new QLabel("奖道具");
	A_Count_L=new QLabel("数量：");
    
	MainLayout = new QVBoxLayout;
	NameLayout = new QHBoxLayout;
	LabelLayout = new QVBoxLayout;
	SpinLayout = new QVBoxLayout;
	BodyLayout = new QHBoxLayout;
	NameLayout->addWidget(ID);
	NameLayout->addWidget(Name);
	NameLayout->addWidget(Need_ID_L);
	NameLayout->addWidget(Need_ID);
	LabelLayout->addWidget(MB_L);
	LabelLayout->addWidget(NKillHL_L);
	LabelLayout->addWidget(NKillNPC_L);
	LabelLayout->addWidget(NTalkNPC_L);
	LabelLayout->addWidget(NGetItem_L);
	LabelLayout->addWidget(A_Coin_L);
	LabelLayout->addWidget(A_Exp_L);
	LabelLayout->addWidget(A_Item_L);
	LabelLayout->addWidget(A_Count_L);
	
	SpinLayout->addWidget(MB);
	SpinLayout->addWidget(NKillHL);
	SpinLayout->addWidget(NKillNPC);
	SpinLayout->addWidget(NTalkNPC);
	SpinLayout->addWidget(NGetItem);
	SpinLayout->addWidget(A_Coin);
	SpinLayout->addWidget(A_Exp);
	SpinLayout->addWidget(A_Item);
	SpinLayout->addWidget(A_Count);
	BodyLayout->addWidget(TaskList);
	BodyLayout->addLayout(LabelLayout);
	BodyLayout->addLayout(SpinLayout);
	MainLayout->addLayout(NameLayout);
	MainLayout->addWidget(Des);
	MainLayout->addLayout(BodyLayout);
    MainLayout->addWidget(SaveButton);
       
	this->setLayout(MainLayout);
	Init();
	connect(SaveButton, &QPushButton::clicked, this, &TaskWidget::Save);
	connect(TaskList, &QListWidget::clicked, this, &TaskWidget::Save);
	connect(TaskList, &QListWidget::clicked, this, &TaskWidget::read);
	connect(Name, &QLineEdit::textChanged, this, &TaskWidget::Change);

}
    
    void TaskWidget::Save()
    {
    	
    	int a=ID->value();
    	SystemTask[a].Name=Name->text();
    	SystemTask[a].Des=Des->text();
   	SystemTask[a].Need_ID= Need_ID->value() ;
   	SystemTask[a].MB=MB->value() ;
	SystemTask[a].NKillHL=NKillHL->value() ;
	SystemTask[a].NKillNPC=NKillNPC->value() ;
	SystemTask[a].NTalkNPC=NTalkNPC->value() ;
    SystemTask[a].NGetItem=NGetItem->value() ;
	SystemTask[a].A_Coin=A_Coin->value() ;
	SystemTask[a].A_Exp=A_Exp->value() ;
	SystemTask[a].A_Item=A_Item->value() ;
	SystemTask[a].A_Count=A_Count->value() ;
    	SystemTask[1].Save();
    }
    void TaskWidget::Init()
    {
    	TaskList->clear();
    	SystemTask[1].Init();

    	for(int i=0;i<200;i++)
    	{
    	SystemTask[i].ID=i;
    	SystemTask[i].IsFinish=0;
    	SystemTask[i].FMB=0;
    	TaskList->addItem(SystemTask[i].Name);
    	}
        SystemTask[0].IsFinish=1;

    }





