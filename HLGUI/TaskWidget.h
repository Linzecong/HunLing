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
    QListWidget List;
    QLabel Name;
    QLabel Des;
    QLabel MB_FMB;
    QLabel Reward;
    PushButton Finish;
    PushButton Close;

	public:
    TaskWidget(RenWu *a);
    ~TaskWidget(){}
	void Finish_Click();
    void List_Click();
};

TaskWidget::TaskWidget(RenWu* a){
    List.setFocusPolicy(Qt::NoFocus);
    this->setWindowFlags (Qt::CustomizeWindowHint);
    this->setFixedSize(355,320);

    List.setParent(this);
    Name.setParent(this);
    Des.setParent(this);
    MB_FMB.setParent(this);
    Close.setParent(this);
    Reward.setParent(this);
    Finish.setParent(this);

    this->setObjectName("task");
    Finish.setObjectName("function");
    Close.setObjectName("close");

    List.setGeometry(5,5,200,258);
    Name.setGeometry(210,0,145,30);
    MB_FMB.setGeometry(210,31,145,30);
    Reward.setGeometry(210,62,145,162);
    Reward.setAlignment(Qt::AlignLeft|Qt::AlignTop);
    Finish.setGeometry(210,200,135,30);
    Close.setGeometry(210,233,135,30);

    Des.setGeometry(5,252,355,50);

    Des.setWordWrap(true);







    Me=a;
    for(int i=0;i<a->myTaskList.size();i++)
        List.addItem(a->myTaskList[i].Name);//将任务名字添加到列表中
    Name.setText("任务名称：");
    Des.setText("任务简介：");
    MB_FMB.setText("任务进度：");
    Reward.setText("任务奖励：<br>");
    Finish.setText("完成！");
    Close.setText("关闭");
    Finish.setEnabled(false);


    connect(&Finish,&QPushButton::clicked,this,&Finish_Click);
    connect(&List,&QListWidget::clicked,this,&List_Click);
    connect(&Close,&QPushButton::clicked,this,&close);

}

void TaskWidget::Finish_Click(){
    int a=List.currentRow();
    int i=Me->FinishTask(Me->myTaskList[a]);
    if(i==1){
    MessageBox::about(this,"提示","任务完成！");
    List.takeItem(a);//删除
    }
    else
    MessageBox::about(this,"提示","异常！");

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
