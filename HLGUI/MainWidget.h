#include<QString>
#include<QWidget>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
#include<QKeyEvent>
#include<QMessageBox>

class MainWidget:public QWidget
{
	public:
    GameSystem* Game;
	DataWidget* Data_Widget;
	TimeWidget* Time_Widget;
	MapWidget* Map_Widget;
	ItemWidget* Item_Widget;
	LGWidget* LG_Widget;
	LHWidget* LH_Widget;
    TaskWidget* Task_Widget;
	MapButtonWidget* MapButton_Widget;
    MessageWidget* Message_Widget;

    QVBoxLayout* Layout1;
    QHBoxLayout* MainLayout;

	public:
    MainWidget();
    ~MainWidget()
    {

    }

    void Quit();
	void Save();
    void Help();
	void ShowItem();
    void ShowTask();
	void ShowLG();
	void ShowLH();
    void xia();
    void shang();
    void zuo();
    void you();
    void Get(){Game->Me=God;Map_Widget->Me=God;}


protected:
    void keyPressEvent(QKeyEvent *e);

};

MainWidget::MainWidget()
{
    Layout1=new QVBoxLayout;
    MainLayout=new QHBoxLayout;
Game=new GameSystem;
God=Game->Me;
Data_Widget=new DataWidget(Game->Me,this);
Time_Widget=new TimeWidget(this);
Item_Widget=new ItemWidget(Game->Me);
LG_Widget=new LGWidget(Game->Me);
LH_Widget=new LHWidget(Game->Me);
Task_Widget=new TaskWidget(Game->Me);
MapButton_Widget=new MapButtonWidget;
Message_Widget=new MessageWidget("欢迎游戏");
Map_Widget=new MapWidget(SystemMap[0][0],Game->Me);

Layout1->addWidget(Map_Widget);
Layout1->addWidget(Message_Widget);
Layout1->addWidget(Time_Widget);
MainLayout->addWidget(Data_Widget);
MainLayout->addLayout(Layout1);
MainLayout->addWidget(MapButton_Widget);

connect(&MapButton_Widget->QuitButton,QPushButton::clicked,this,MainWidget::Quit);
connect(&MapButton_Widget->SaveButton,QPushButton::clicked,this,MainWidget::Save);
connect(&MapButton_Widget->HelpButton,QPushButton::clicked,this,MainWidget::Help);
connect(&MapButton_Widget->BagButton,QPushButton::clicked,this,MainWidget::ShowItem);
connect(&MapButton_Widget->TaskButton,QPushButton::clicked,this,MainWidget::ShowTask);
connect(&MapButton_Widget->LGButton,QPushButton::clicked,this,MainWidget::ShowLG);
connect(&MapButton_Widget->LHButton,QPushButton::clicked,this,MainWidget::ShowLH);
for(int i=1;i<=9;i++)
{
connect(&Map_Widget->MapHL[i]->n,QPushButton::clicked,this,MainWidget::Get);
connect(&Map_Widget->MapNPC[i]->n,QPushButton::clicked,this,MainWidget::Get);
}




this->setLayout(MainLayout);

}

void MainWidget::Quit()
{
    this->close();
}

void MainWidget::Save()
{

}

void MainWidget::Help()
{
    QMessageBox::about(this,"帮助","Help");
    Map_Widget->MapHL[1]->n.click();
}

void MainWidget::ShowItem()
{
    Item_Widget->exec();
    Item_Widget->Me.Bag=Item_Widget->Bag;
    Game->Me=Item_Widget->Me;
    Data_Widget->UpDate(Game->Me);
}

void MainWidget::ShowTask()
{
    Task_Widget->exec();
    Game->Me=Task_Widget->Me;
    Data_Widget->UpDate(Game->Me);

}

void MainWidget::ShowLG()
{
    LG_Widget->exec();
    Game->Me=LG_Widget->Me;
    Data_Widget->UpDate(Game->Me);

}

void MainWidget::ShowLH()
{
    LH_Widget->exec();
    Game->Me=LH_Widget->Me;
    Data_Widget->UpDate(Game->Me);
}

void MainWidget::keyPressEvent(QKeyEvent *e)
{

                int key = e->key();
                if (Qt::Key_S == key)
                xia();
                if (Qt::Key_W == key)
                shang();
                if (Qt::Key_A == key)
                zuo();
                if (Qt::Key_D == key)
                you();

}


void MainWidget::xia()
{
  Map_Widget->UpDate(SystemMap[0][1],Game->Me);

}
void MainWidget::shang(){}
void MainWidget::zuo(){}
void MainWidget::you(){}









