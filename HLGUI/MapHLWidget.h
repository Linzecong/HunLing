
#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPushButton>
#include<QMessageBox>
class MapHLWidget: public QWidget
{
	public:
    RenWu Me;
    LHList EnemyList;
    QLabel Head;
	QLabel Name;
	QLabel LV;
	QLabel Count;
	QPushButton Attack;
    QPushButton n;
    QVBoxLayout* MainLayout;
	public:
    void Attack_Click();
    MapHLWidget(RenWu temp,LHList EnemyList);
    MapHLWidget(){}
    ~MapHLWidget(){}


	
	
};

MapHLWidget::MapHLWidget(RenWu temp, LHList EnemyList)
{
    MainLayout=new QVBoxLayout;
    Me=temp;
 //   Head.setPixmap(QPixmap::load(""));
    Name.setText(EnemyList.GetData(1).Name);
    LV.setText("等级："+QString::number(EnemyList.GetData(1).LV));
   // Count.setText("数量："+QString::number(GetNumber(1,SystemMap[Me.PosX][Me.PosY].HLCount)));
    Count.setText("数量："+QString::number(GetNumber(1,9)));
    Attack.setText("攻击");
    MainLayout->addWidget(&Head);
    MainLayout->addWidget(&Name);
    MainLayout->addWidget(&LV);
    MainLayout->addWidget(&Count);
    MainLayout->addWidget(&Attack);

    connect(&Attack,QPushButton::clicked,this,MapHLWidget::Attack_Click);
    this->setLayout(MainLayout);
}
void MapHLWidget::Attack_Click()
{
    Me=God;
    NPC tempNPC=GameSystem::CreateNPC(EnemyList);
    FightWidget* Battle=new FightWidget(Me,tempNPC);
    Battle->setWindowFlags(Qt::FramelessWindowHint);
    Battle->exec();
    if(Battle->WinOrLose==1)
    {
        Me=Battle->Me;
    Me.Exp_Now+=Battle->Reward.Exp;
    Me.Coin+=Battle->Reward.Coin;
    for(int i=1;i<=Battle->Reward.Item.Count();i++)
        for(int j=1;j<=Battle->Reward.Item.GetCount(i);j++)
    Me.Bag.Insert(Battle->Reward.Item.GetData(i));

    for(int i=1;i<=Battle->Reward.LG.Count();i++)
    Me.LGBag.Insert(Battle->Reward.LG.GetData(i));

    for(int i=1;i<=Battle->Reward.LH.Count();i++)
    Me.LHBag.Insert(Battle->Reward.LH.GetData(i));
    int UL=Me.UpdateLV();
    if(UL>0)
        QMessageBox::about(this,"提示","恭喜！你升级了！");
    Me.UpdateBuff();
        this->setEnabled(false);
    }

    God=Me;
    delete Battle;

    n.click();


}
