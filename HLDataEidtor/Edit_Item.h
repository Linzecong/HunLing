
class Item
{
  public:
	int ID;
	QString Des;
	QString Name;
	int Type;
    int ATKType;//0敌人单体,1敌人全体,2我方单体,3我方全体
	int Value;
	int Str;
	int Agi;
	int Vit;
	int Ene;
	int Sour;
	int Exp;
	void Save();
	void Init();
} SystemItem[200];
void Item::Save()
{
    QFile file((DATAPATH+"SaveItem.str"));
	file.open(QIODevice::WriteOnly);
	QTextStream in(&file);
	for (int i = 1; i <= 199; i++)
		in << SystemItem[i].Name << " " << SystemItem[i].Des << endl;

    QFile tmpfile(DATAPATH+"SaveItem.num");
	tmpfile.open(QIODevice::WriteOnly);
	for (int i = 1; i <= 199; i++)
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
	for (int i = 1; i <= 199; i++)
		in >> SystemItem[i].Name >> SystemItem[i].Des;
	for (int i = 1; i <= 199; i++)
		if (SystemItem[i].Name == "")
		{
			SystemItem[i].Name = "未编辑";
			SystemItem[i].Des = "未编辑";
		}


	file.close();
    QFile tmpfile(DATAPATH+"SaveItem.num");
	tmpfile.open(QIODevice::ReadOnly);
	for (int i = 1; i <= 199; i++)
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
  class ItemWidget:public QWidget

{
	// Q_OBJECT
  private:
	QLineEdit * Name;
	QLineEdit *Des;
	QSpinBox *ID;
	QSpinBox *Type;
    QSpinBox *ATKType;
	QSpinBox *Value;
	QSpinBox *Str;
	QSpinBox *Agi;
	QSpinBox *Vit;
	QSpinBox *Ene;
	QSpinBox *Sour;
	QSpinBox *Exp;

	QLabel *Type_L;
    QLabel *ATKType_L;
	QLabel *Value_L;
	QLabel *Str_L;
	QLabel *Agi_L;
	QLabel *Vit_L;
	QLabel *Ene_L;
	QLabel *Sour_L;
	QLabel *Exp_L;

	QListWidget *ItemList;
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
	void Change()
	{
		int a = ItemList->currentRow();
		ItemList->selectedItems().first()->setText(Name->text());
	}
  public:
	ItemWidget();
	~ItemWidget()
	{
	}
};

void ItemWidget::read()
{
	int a = ItemList->currentRow();
	ItemList->selectedItems().first()->setText(SystemItem[a].Name);
	Name->setText(SystemItem[a].Name);
	Des->setText(SystemItem[a].Des);
	ID->setValue(a);
	Type->setValue(SystemItem[a].Type);
    ATKType->setValue(SystemItem[a].ATKType);
	Value->setValue(SystemItem[a].Value);
	Str->setValue(SystemItem[a].Str);
	Agi->setValue(SystemItem[a].Agi);
	Vit->setValue(SystemItem[a].Vit);
	Ene->setValue(SystemItem[a].Ene);
	Sour->setValue(SystemItem[a].Sour);
	Exp->setValue(SystemItem[a].Exp);
}


ItemWidget::ItemWidget()
{
	Name = new QLineEdit("名字");
	Des = new QLineEdit("介绍");
	SaveButton = new QPushButton("保存");
	ItemList = new QListWidget;
	ID = new QSpinBox;
	ID->setRange(0, 199);
	ID->setEnabled(false);


	Type = new QSpinBox;
    Type->setRange(1, 3);
    ATKType = new QSpinBox;
    ATKType->setRange(0, 3);
	Value = new QSpinBox;
	Value->setRange(0, 50000);
	Value->setSingleStep(50);
	Str = new QSpinBox;
	Str->setRange(0, 20);
	Agi = new QSpinBox;
	Agi->setRange(0, 20);
	Vit = new QSpinBox;
	Vit->setRange(0, 20);
	Ene = new QSpinBox;
	Ene->setRange(0, 1000);
	Ene->setSingleStep(10);
	Exp = new QSpinBox;
	Exp->setRange(0, 5000);
	Exp->setSingleStep(100);
	Sour = new QSpinBox;
	Sour->setRange(0, 20);


	Type_L = new QLabel("类型：");
    ATKType_L = new QLabel("0敌单2我单");
	Value_L = new QLabel("价值：");
	Str_L = new QLabel("力量：");
	Agi_L = new QLabel("敏捷：");
	Vit_L = new QLabel("体力：");
	Ene_L = new QLabel("魂力：");
	Sour_L = new QLabel("灵力：");
	Exp_L = new QLabel("经验：");

	MainLayout = new QVBoxLayout;
	NameLayout = new QHBoxLayout;
	LabelLayout = new QVBoxLayout;
	SpinLayout = new QVBoxLayout;
	BodyLayout = new QHBoxLayout;
	NameLayout->addWidget(ID);
	NameLayout->addWidget(Name);
	LabelLayout->addWidget(Type_L);
    LabelLayout->addWidget(ATKType_L);
	LabelLayout->addWidget(Value_L);
	LabelLayout->addWidget(Str_L);
	LabelLayout->addWidget(Agi_L);
	LabelLayout->addWidget(Vit_L);
	LabelLayout->addWidget(Ene_L);
	LabelLayout->addWidget(Sour_L);
	LabelLayout->addWidget(Exp_L);

	SpinLayout->addWidget(Type);
    SpinLayout->addWidget(ATKType);
	SpinLayout->addWidget(Value);
	SpinLayout->addWidget(Str);
	SpinLayout->addWidget(Agi);
	SpinLayout->addWidget(Vit);
	SpinLayout->addWidget(Ene);
	SpinLayout->addWidget(Sour);
	SpinLayout->addWidget(Exp);

	BodyLayout->addWidget(ItemList);
	BodyLayout->addLayout(LabelLayout);
	BodyLayout->addLayout(SpinLayout);
	MainLayout->addLayout(NameLayout);
	MainLayout->addWidget(Des);
	MainLayout->addLayout(BodyLayout);
	MainLayout->addWidget(SaveButton);

	this->setLayout(MainLayout);
	Init();
	connect(SaveButton, &QPushButton::clicked, this, &ItemWidget::Save);
	connect(ItemList, &QListWidget::clicked, this, &ItemWidget::Save);
	connect(ItemList, &QListWidget::clicked, this, &ItemWidget::read);
	connect(Name, &QLineEdit::textChanged, this, &ItemWidget::Change);

}

void ItemWidget::Save()
{

	int a = ID->value();
	SystemItem[a].Name = Name->text();
	SystemItem[a].Des = Des->text();
	SystemItem[a].Type = Type->value();
    SystemItem[a].ATKType = ATKType->value();
	SystemItem[a].Value = Value->value();
	SystemItem[a].Str = Str->value();
	SystemItem[a].Agi = Agi->value();
	SystemItem[a].Vit = Vit->value();
	SystemItem[a].Ene = Ene->value();
	SystemItem[a].Sour = Sour->value();
	SystemItem[a].Exp = Exp->value();
	SystemItem[1].Save();
}

void ItemWidget::Init()
{
	ItemList->clear();
	SystemItem[1].Init();
	SystemItem[0].Name = "请勿修改这个";
	SystemItem[0].Des = "请勿修改这个";
	for (int i = 0; i < 200; i++)
	{
		SystemItem[i].ID = i;
		ItemList->addItem(SystemItem[i].Name);
	}


}


