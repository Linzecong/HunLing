#include<QString>
#include<QWidget>
#include<QPushButton>
#include<QHBoxLayout>
class MapButtonWidget: public QWidget
{
	public:
	QPushButton BagButton;
	QPushButton TaskButton;
	QPushButton LGButton;
	QPushButton LHButton;
	QPushButton SaveButton;
	QPushButton HelpButton;
	QPushButton QuitButton;
    QVBoxLayout* MainLayout;
    MapButtonWidget();
    ~MapButtonWidget(){}
	
};

MapButtonWidget::MapButtonWidget()
{

   MainLayout=new QVBoxLayout;
    BagButton.setText("背包");
    TaskButton.setText("任务");
    LGButton.setText("灵骨");
    LHButton.setText("灵环");
    SaveButton.setText("保存");
    HelpButton.setText("帮助");
    QuitButton.setText("退出");
    MainLayout->addWidget(&BagButton);
    MainLayout->addWidget(&TaskButton);
    MainLayout->addWidget(&LGButton);
    MainLayout->addWidget(&LHButton);
    MainLayout->addWidget(&SaveButton);
    MainLayout->addWidget(&HelpButton);
    MainLayout->addWidget(&QuitButton);
    this->setLayout(MainLayout);
}








