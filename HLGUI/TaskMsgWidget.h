#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
//#include"HLQTData/HL_Task.h"
class TaskMsgWidget: public QDialog
{
	public:
    TaskList* Me;
    TaskList tempTask;
    QListWidget List;
    QLabel Title;
	QLabel Name;
	QLabel Des;
	QLabel MB_FMB;
	QLabel Reward;
	QPushButton Except;
    QVBoxLayout* Layout1;
    QHBoxLayout* Layout2;
    QVBoxLayout* MainLayout;

	public:
    TaskMsgWidget(TaskList a,TaskList* b);
    void Except_Click();
    void ListClick();
    ~TaskMsgWidget(){}
	
};

TaskMsgWidget::TaskMsgWidget(TaskList a,TaskList* b)
{
    Layout1=new QVBoxLayout;
    Layout2=new QHBoxLayout;
    MainLayout=new QVBoxLayout;

    tempTask=a;
    Me=b;
    for(int i=1;i<=tempTask.Count();i++)
        List.addItem(tempTask.GetData(i).Name);
    Title.setText("任务列表：");
    Name.setText("任务名称：");
    Des.setText("任务简介：");
    MB_FMB.setText("任务进度：");
    Reward.setText("任务奖励：<br>");
    Except.setText("接受！");
    Layout1->addWidget(&Title);
    Layout1->addWidget(&List);
    Layout2->addWidget(&Name);
    Layout2->addWidget(&Des);
    Layout2->addWidget(&MB_FMB);
    Layout2->addWidget(&Reward);
    MainLayout->addLayout(Layout1);
    MainLayout->addLayout(Layout2);
    this->setLayout(MainLayout);
}

void TaskMsgWidget::Except_Click()
{
    int a=List.currentRow()+1;
    int b=tempTask.GetData(a).ID;
    Me->Insert(SystemTask[b]);
    Except.setEnabled(false);
    QMessageBox::about(this,"提示","接受成功！");
    this->close();

}

void TaskMsgWidget::ListClick()
{
    int a=List.currentRow()+1;
    Task b=tempTask.GetData(a);
    Name.setText("任务名称："+b.Name);
    Des.setText("任务简介："+b.Des);
    MB_FMB.setText("任务进度："+QString::number(b.FMB)+"/"+QString::number(b.MB));
    Reward.setText("任务奖励：<br>金钱："+QString::number(b.A_Coin)+"<br>经验："+QString::number(b.A_Exp)+"<br>"+SystemItem[b.A_Item].Name+"x"+QString::number(b.A_Count)+"个");
}
