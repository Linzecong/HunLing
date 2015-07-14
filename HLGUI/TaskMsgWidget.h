/*用于显示能接受的NPC任务*/

#ifndef TASKMSGWIDGET
#define TASKMSGWIDGET

#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
#include<../HLBase/HL_Task.h>
#include<../HLBase/HL_RenWu.h>
class TaskMsgWidget: public QDialog{
	public:
    RenWu* Me;//自己的任务列表
    QList<Task> tempTask;//能接受的任务列表
    QListWidget List;
    QLabel Title;
	QLabel Name;
	QLabel Des;
	QLabel MB_FMB;
	QLabel Reward;
	QPushButton Except;
    QVBoxLayout* Layout1;
    QVBoxLayout* Layout2;
    QVBoxLayout* MainLayout;

	public:
    TaskMsgWidget(RenWu* a,QList<Task> b);
    void Except_Click();
    void List_Click();
    ~TaskMsgWidget(){}
};

TaskMsgWidget::TaskMsgWidget(RenWu* a, QList<Task> b){
    Layout1=new QVBoxLayout;
    Layout2=new QVBoxLayout;
    MainLayout=new QVBoxLayout;
    tempTask=b;
    Me=a;

    for(int i=0;i<tempTask.size();i++)
        List.addItem(tempTask[i].Name);

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
    MainLayout->addWidget(&Except);
    connect(&Except,&QPushButton::clicked,this,&Except_Click);
    connect(&List,&QListWidget::clicked,this,&List_Click);
    this->setLayout(MainLayout);
}

void TaskMsgWidget::Except_Click(){
    int a=List.currentRow();
    if(a<0)
        return;
    Me->myTaskList.append(tempTask[a]);
    Except.setEnabled(false);
    QMessageBox::about(this,"提示","接受成功！");
    List.takeItem(a);
    tempTask.takeAt(a);
}

void TaskMsgWidget::List_Click(){
    Except.setEnabled(true);
    int a=List.currentRow();
    Task b=tempTask[a];
    Name.setText("任务名称："+b.Name);
    Des.setText("任务简介："+b.Des);
    MB_FMB.setText("任务进度："+QString::number(b.FMB)+"/"+QString::number(b.MB));
    Reward.setText("任务奖励：<br>金钱："+QString::number(b.A_Coin)+"<br>经验："+QString::number(b.A_Exp)+"<br>道具："+SystemItem[b.A_Item].Name+" * "+QString::number(b.A_Count)+"个");
}

#endif
