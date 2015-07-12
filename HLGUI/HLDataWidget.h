/*用于显示魂灵详细信息*/

#ifndef HLDATAWIDGET
#define HLDATAWIDGET

#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<../HLBase/HL_HunLing.h>
#include<../HLBase/HL_HunJi.h>

class HLDataWidget: public QDialog{
	public:
	HunLing tempHL;
	QLabel Name;
	QLabel Des;
	QLabel Strength;
	QLabel Agility;
	QLabel ATK;
	QLabel DEF;
	QLabel VIT;
	QLabel K_Fire;
	QLabel K_Ice;
	QLabel K_Lig;
	QLabel K_Tox;
	QLabel G_Fire;
	QLabel G_Ice;
	QLabel G_Lig;
	QLabel G_Tox;
	QLabel DEF_Ski;
	QLabel ATK_Ski;
    QVBoxLayout MainLayout;
	public:
    void setData(HunLing a);
    HLDataWidget(HunLing a);
	~HLDataWidget(){}
};

HLDataWidget::HLDataWidget(HunLing a){
    tempHL=a;
    Name.setText("名字："+a.Name);
    Des.setText("介绍："+a.Des);
    Strength.setText("力量："+a.Strength);
    Agility.setText("敏捷："+a.Agility);
    ATK.setText("攻击力："+a.ATK);
    DEF.setText("防御力："+a.DEF);
    VIT.setText("生命力："+a.VIT);
    K_Fire.setText("火抗："+a.K_Fire);
    K_Ice.setText("冰抗："+a.K_Ice);
    K_Lig.setText("电抗："+a.K_Lig);
    K_Tox.setText("毒抗："+a.K_Tox);
    G_Fire.setText("火焰伤害："+a.G_Fire);
    G_Ice.setText("冰冷伤害："+a.G_Ice);
    G_Lig.setText("电击伤害："+a.G_Lig);
    G_Tox.setText("毒素伤害："+a.G_Tox);
    ATK_Ski.setText("攻击技能：<br>"+SystemHJ[a.DEF_Ski].Name+"："+SystemHJ[a.DEF_Ski].Des);
    DEF_Ski.setText("防御技能：<br>"+SystemBuff[a.DEF_Ski].Name+"："+SystemBuff[a.DEF_Ski].Des);
    MainLayout.addWidget(&Name);
    MainLayout.addWidget(&Des);
    MainLayout.addWidget(&Strength);
    MainLayout.addWidget(&Agility);
    MainLayout.addWidget(&ATK);
    MainLayout.addWidget(&DEF);
    MainLayout.addWidget(&VIT);
    MainLayout.addWidget(&K_Fire);
    MainLayout.addWidget(&K_Ice);
    MainLayout.addWidget(&K_Lig);
    MainLayout.addWidget(&K_Tox);
    MainLayout.addWidget(&G_Fire);
    MainLayout.addWidget(&G_Ice);
    MainLayout.addWidget(&G_Lig);
    MainLayout.addWidget(&G_Tox);
    MainLayout.addWidget(&ATK_Ski);
    MainLayout.addWidget(&DEF_Ski);
    this->setLayout(&MainLayout);
}

void HLDataWidget::setData(HunLing a){
    tempHL=a;
    Name.setText("名字："+a.Name);
    Des.setText("介绍："+a.Des);
    Strength.setText("力量："+a.Strength);
    Agility.setText("敏捷："+a.Agility);
    ATK.setText("攻击力："+a.ATK);
    DEF.setText("防御力："+a.DEF);
    VIT.setText("生命力："+a.VIT);
    K_Fire.setText("火抗："+a.K_Fire);
    K_Ice.setText("冰抗："+a.K_Ice);
    K_Lig.setText("电抗："+a.K_Lig);
    K_Tox.setText("毒抗："+a.K_Tox);
    G_Fire.setText("火焰伤害："+a.G_Fire);
    G_Ice.setText("冰冷伤害："+a.G_Ice);
    G_Lig.setText("电击伤害："+a.G_Lig);
    G_Tox.setText("毒素伤害："+a.G_Tox);
    ATK_Ski.setText("攻击技能：<br>"+SystemHJ[a.DEF_Ski].Name+"："+SystemHJ[a.DEF_Ski].Des);
    DEF_Ski.setText("防御技能：<br>"+SystemBuff[a.DEF_Ski].Name+"："+SystemBuff[a.DEF_Ski].Des);
}

#endif







