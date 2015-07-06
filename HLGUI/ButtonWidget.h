#include<QString>
#include<QDialog>
#include<QPushButton>
#include<QHBoxLayout>
class ButtonWidget: public QDialog
{
	public:
	int type;
	QPushButton BagButton;
	QPushButton ATKButton;
	QPushButton LGButton;
	QPushButton SkillButton;
	QPushButton JumpButton;
	QPushButton HelpButton;
    QHBoxLayout MainLayout;
    ButtonWidget();
    ~ButtonWidget(){}
};

ButtonWidget::ButtonWidget()
{
    BagButton.setText("背包");
    ATKButton.setText("攻击");
    LGButton.setText("灵骨");
    SkillButton.setText("技能");
    JumpButton.setText("跳过");
    HelpButton.setText("帮助");
    MainLayout.addWidget(&ATKButton);
    MainLayout.addWidget(&LGButton);
    MainLayout.addWidget(&SkillButton);
    MainLayout.addWidget(&BagButton);
    MainLayout.addWidget(&JumpButton);
    MainLayout.addWidget(&HelpButton);
    this->setLayout(&MainLayout);

}