#include<QString>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>


class DataWidget: public QWidget
{
	public:
	RenWu Me;
	QLabel Title;
	QLabel Level;
	QLabel Exp;
	QLabel LingHuan;//颜色
	QLabel Strength;
	QLabel Agility;
	QLabel Vitality;
	QLabel Energy;
	QLabel Sour;
    BuffWidget* myBuff;
    QVBoxLayout* MainLayout;
public:
DataWidget(RenWu a, QWidget *parent);
~DataWidget(){}
void UpDate(RenWu a);
};

DataWidget::DataWidget(RenWu a,QWidget *parent): QWidget(parent)
{
     MainLayout=new QVBoxLayout;
    Me=a;
    Title.setText("人物信息：");
    Level.setText("等级："+QString::number(Me.LV)+"级");
    Exp.setText("经验："+QString::number(Me.Exp_Now)+"/"+QString::number(Me.Exp_Need));
    for(int i=1;i<=Me.LH.Count();i++)
    LingHuan.setText(LingHuan.text()+Me.LH.GetData(i).Col);
    Strength.setText("力量："+QString::number(Me.Strength)+"("+QString::number(Me.Ori_Strength)+")");
    Agility.setText("敏捷："+QString::number(Me.Agility)+"("+QString::number(Me.Ori_Agility)+")");
    Vitality.setText("体力："+QString::number(Me.Vitality)+"("+QString::number(Me.Ori_Vitality)+")");
    Energy.setText("魂力："+QString::number(Me.Energy)+"("+QString::number(Me.Ori_Energy)+")");
    Sour.setText("灵力："+QString::number(Me.Sour)+"("+QString::number(Me.Ori_Sour)+")");
    myBuff=new BuffWidget(Me.myBuffList);
    MainLayout->addWidget(&Title);
    MainLayout->addWidget(&Level);
    MainLayout->addWidget(&Exp);
    MainLayout->addWidget(&LingHuan);
    MainLayout->addWidget(&Strength);
    MainLayout->addWidget(&Agility);
    MainLayout->addWidget(&Vitality);
    MainLayout->addWidget(&Energy);
    MainLayout->addWidget(&Sour);
    MainLayout->addWidget(myBuff);
    this->setLayout(MainLayout);

}

void DataWidget::UpDate(RenWu a)
{
    Me=a;
    Title.setText("人物信息：");
    Level.setText("等级："+QString::number(Me.LV)+"级");
    Exp.setText("经验："+QString::number(Me.Exp_Now)+"/"+QString::number(Me.Exp_Need));
    for(int i=1;i<=Me.LH.Count();i++)
    LingHuan.setText(LingHuan.text()+Me.LH.GetData(i).Col);
    Strength.setText("力量："+QString::number(Me.Strength)+"("+QString::number(Me.Ori_Strength)+")");
    Agility.setText("敏捷："+QString::number(Me.Agility)+"("+QString::number(Me.Ori_Agility)+")");
    Vitality.setText("体力："+QString::number(Me.Vitality)+"("+QString::number(Me.Ori_Vitality)+")");
    Energy.setText("魂力："+QString::number(Me.Energy)+"("+QString::number(Me.Ori_Energy)+")");
    Sour.setText("灵力："+QString::number(Me.Sour)+"("+QString::number(Me.Ori_Sour)+")");
    myBuff->UpDate(Me.myBuffList);


}








