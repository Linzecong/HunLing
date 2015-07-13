
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
class MsgWidget:public QWidget
{
	public:
	QSpinBox* ID;
	QSpinBox* NTask;
	QLineEdit* Msg;
	QListWidget* MsgList;
	QHBoxLayout* SpinLayout;
	QPushButton *SaveButton;
	QVBoxLayout *MainLayout;
	
	
	void Save();
	void Init();
	void read();
	void Change()
	{
		int a = MsgList->currentRow();
		MsgList->selectedItems().first()->setText(Msg->text());
	}
  public:
	MsgWidget();
	~MsgWidget()
	{
	}

};
void MsgWidget::read()
{
	int a = MsgList->currentRow();
	Msg->setText(SystemMessage[a].Msg);
	NTask->setValue(SystemMessage[a].NTask);
	ID->setValue(a);
}

MsgWidget::MsgWidget()
{
	Msg = new QLineEdit("消息");
	SaveButton = new QPushButton("保存");
	MsgList = new QListWidget;
	ID = new QSpinBox;
	ID->setRange(0, 499);
	ID->setEnabled(false);


	NTask = new QSpinBox;
	NTask->setRange(0,199);

	MainLayout = new QVBoxLayout;
    SpinLayout = new QHBoxLayout;

	SpinLayout->addWidget(ID);
	SpinLayout->addWidget(NTask);
	
	MainLayout->addLayout(SpinLayout);
	MainLayout->addWidget(Msg);
	MainLayout->addWidget(MsgList);
	MainLayout->addWidget(SaveButton);
	this->setLayout(MainLayout);
	Init();
	connect(SaveButton, &QPushButton::clicked, this, &MsgWidget::Save);
	connect(MsgList, &QListWidget::clicked, this, &MsgWidget::Save);
	connect(MsgList, &QListWidget::clicked, this, &MsgWidget::read);
	connect(Msg, &QLineEdit::textChanged, this, &MsgWidget::Change);

}
void MsgWidget::Save()
{

	int a = ID->value();
	SystemMessage[a].Msg = Msg->text();
	SystemMessage[a].NTask=NTask->value();
	SystemMessage[1].Save();
}

void MsgWidget::Init()
{
	MsgList->clear();
	SystemMessage[1].Init();
	SystemMessage[0].Msg = "请勿修改这个";

	for (int i = 0; i < 500; i++)
	{
		SystemMessage[i].ID = i;
		MsgList->addItem(SystemMessage[i].Msg);
	}


}










