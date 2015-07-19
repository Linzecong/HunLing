/*任务列表，用于显示已接受的任务*/

#ifndef TASKWIDGET
#define TASKWIDGET

#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
#include<../HLBase/HL_RenWu.h>
class TaskWidget:public QDialog{
	public:
    RenWu* Me;//用于读取任务列表
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
    TaskWidget(RenWu *a);
    ~TaskWidget(){}
	void Finish_Click();
    void List_Click();
};

TaskWidget::TaskWidget(RenWu* a){
    Layout1=new QVBoxLayout;
    MainLayout=new QHBoxLayout;
    Me=a;
    for(int i=0;i<a->myTaskList.size();i++)
        List.addItem(a->myTaskList[i].Name);//将任务名字添加到列表中
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
    connect(&Finish,&QPushButton::clicked,this,&Finish_Click);
    connect(&List,&QListWidget::clicked,this,&List_Click);

}

void TaskWidget::Finish_Click(){
    int a=List.currentRow();
    int i=Me->FinishTask(Me->myTaskList[a]);
    if(i==1){
    QMessageBox::about(this,"提示","任务完成！");
    List.takeItem(a);//删除
    }
    else
    QMessageBox::about(this,"提示","异常！");

    Finish.setEnabled(false);
}

void TaskWidget::List_Click(){
    int a=List.currentRow();
    Task b=Me->myTaskList[a];
    Name.setText("任务名称："+b.Name);
    Des.setText("任务简介："+b.Des);
    if(b.FMB>b.MB)
        b.FMB=b.MB;
    MB_FMB.setText("任务进度："+QString::number(b.FMB)+"/"+QString::number(b.MB));
    Reward.setText("任务奖励：<br>金钱："+QString::number(b.A_Coin)+"<br>经验："+QString::number(b.A_Exp)+"<br>"+SystemItem[b.A_Item].Name+"x"+QString::number(b.A_Count)+"个");

    if(GameSystem::IsTaskFinish(b))//如果任务已完成
        Finish.setEnabled(true);
}

#endif
