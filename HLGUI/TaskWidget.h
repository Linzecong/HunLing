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
#include<Global.h>
#include<../HLBase/HL_RenWu.h>
#include<../HLBase/HL_NPC.h>

class TaskWidget:public QDialog{
private:
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
QPushButton UpDataMap;
private:
    void Finish_Click();
    void List_Click();//列表被点击时
};

TaskWidget::TaskWidget(RenWu* a){
    /*在这里处理界面*/
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
    Finish.setStyleSheet("backgrounf-image:()");//设置初始图片
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

    /*在这里处理UI逻辑*/
    Me=a;
    for(int i=0;i<a->myTaskList.size();i++)
        List.addItem(a->myTaskList[i].Name);//将任务名字添加到列表中，以后可加Icon。

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
    Task tempTask=Me->myTaskList[a];
    int i=Me->FinishTask(Me->myTaskList[a]);
    if(i==1){
        /*隐藏不再显示的NPC*/
        switch(tempTask.ID){
        case 3:
            SystemNPC[1].TaskShow=199;
            SystemNPC[2].TaskShow=199;
            break;
        case 4:
            SystemNPC[3].TaskShow=199;
            SystemNPC[5].TaskShow=199;
            break;

        }

        MessageBox::about(this,"提示","任务完成！");
        List.takeItem(a);//删除


        if(tempTask.ID==4){
            MessageBox::about(this,"故事开始！","由于邪魂宗主最后一击太过强大，村子几乎被炸毁，村民也所剩无几，A也承受不住这一击，还好没有死亡，但被邪魂宗带走了！");
            MessageBox::about(this,"故事开始！","(村子外的山头上)<br>怎么了？！声音那么大？村子着火了？！！快回去看看！（手里提着刚摘的山果回去了！）");
            /*改变主角*/

            RenWu temprenwu;

            temprenwu.LV=1;
            temprenwu.Exp_Need=180;
            temprenwu.Exp_Now=0;
            temprenwu.Name="主角";
            temprenwu.Coin=0;
            temprenwu.PosX=1;
            temprenwu.PosY=4;
            temprenwu.Ori_Agility=22;
            temprenwu.Ori_Energy=150;
            temprenwu.Ori_Strength=22;
            temprenwu.Ori_Vitality=11;
            temprenwu.Ori_Sour=1;

            LingHuan a;
            a.LV=5;
            a.ID=19;
            a.DEF_Ski=13;
            a.Name=SystemHL[19].Name;
            a.Des=SystemHL[19].Des;
            a.Col="灰";
            a.Value=0;
            a.Strength=SystemHL[19].Strength+a.LV*2;
            a.Agility=SystemHL[19].Agility+a.LV*2;
            temprenwu.LH.append(a);

            temprenwu.Bag.append(SystemItem[6]);
            temprenwu.Bag.append(SystemItem[7]);
            temprenwu.myTaskList.append(SystemTask[5]);



            *Me=temprenwu;

        }



    }
    else
        MessageBox::about(this,"提示","异常！");

    UpDataMap.click();
    Finish.setEnabled(false);
}

void TaskWidget::List_Click(){
    int a=List.currentRow();
    if(a<0)
        return;
    Task b=Me->myTaskList[a];
    Name.setText("任务名称："+b.Name);
    Des.setText("任务简介："+b.Des);
    if(b.FMB>b.MB)
        b.FMB=b.MB;
    MB_FMB.setText("任务进度："+QString::number(b.FMB)+"/"+QString::number(b.MB));
    QString str="任务奖励：<br>金钱："+QString::number(b.A_Coin)+"<br>经验："+QString::number(b.A_Exp)+"<br>";
    if(b.A_Item!=0)
    Reward.setText(str+SystemItem[b.A_Item].Name+"x"+QString::number(b.A_Count)+"个");
    else
    Reward.setText(str);

    if(GameSystem::IsTaskFinish(b))//如果任务已完成
        Finish.setEnabled(true);
}

#endif
