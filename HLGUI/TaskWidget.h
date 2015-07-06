#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
//#include"HLQTData/HL_Task.h"
//#include"HLQTData/HL_RenWu.h"
//#include<TaskMsgWidget.h>
#include<QListWidget>

class TaskWidget:public QDialog
{
	public:
    RenWu Me;
	QLabel Title;

    QListWidget List;
    QLabel Name;
    QLabel Des;
    QLabel MB_FMB;
    QLabel Reward;
    QPushButton Finish;
    QVBoxLayout* Layout1;
    QHBoxLayout* MainLayout;

	public:
    TaskWidget(RenWu a);
    ~TaskWidget(){}
	void Finish_Click();
    void ListClick();
};

TaskWidget::TaskWidget(RenWu a)
{
    Layout1=new QVBoxLayout;
   MainLayout=new QHBoxLayout;
    Me=a;
    for(int i=1;i<=a.myTaskList.Count();i++)
        List.addItem(a.myTaskList.GetData(i).Name);
    Title.setText("任务列表");
    Name.setText("任务名称：");
    Des.setText("任务简介：");
    MB_FMB.setText("任务进度：");
    Reward.setText("任务奖励：<br>");
    Finish.setText("完成！");
    Finish.setEnabled(false);
    Layout1->addWidget(&Name);
    Layout1->addWidget(&Des);
    Layout1->addWidget(&MB_FMB);
    Layout1->addWidget(&Reward);
    Layout1->addWidget(&Finish);
    MainLayout->addWidget(&Title);
    MainLayout->addWidget(&List);
    MainLayout->addLayout(Layout1);

    this->setLayout(MainLayout);

}

void TaskWidget::Finish_Click()
{
    int a=List.currentRow()+1;
    int b=Me.myTaskList.GetData(a).ID;
    Me.FinishTask(SystemTask[b]);
    QMessageBox::about(this,"提示","任务完成！");

}

void TaskWidget::ListClick()
{
    int a=List.currentRow()+1;
    Task b=Me.myTaskList.GetData(a);
    Name.setText("任务名称："+b.Name);
    Des.setText("任务简介："+b.Des);
    MB_FMB.setText("任务进度："+QString::number(b.FMB)+"/"+QString::number(b.MB));
    Reward.setText("任务奖励：<br>金钱："+QString::number(b.A_Coin)+"<br>经验："+QString::number(b.A_Exp)+"<br>"+SystemItem[b.A_Item].Name+"x"+QString::number(b.A_Count)+"个");
    if(b.MB>=b.FMB)
        Finish.setEnabled(true);


}
