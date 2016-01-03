#ifndef NEWTASK_H
#define NEWTASK_H

#include <QDialog>
#include "Global.h"
#include "ui_Newtask.h"

namespace Ui {
class NewTask;
}

class NewTask : public QDialog
{

public:
    NewTask();
    ~NewTask();
    void Save();
    void BoxChange1(){
                if(ui->NeedKillHL->currentIndex()==0)
                    return;

        ui->NeedKillNPC->setCurrentIndex(0);
        ui->NeedTalkNPC->setCurrentIndex(0);
        ui->NeedGetItem->setCurrentIndex(0);
    }
    void BoxChange2(){
        if(ui->NeedKillNPC->currentIndex()==0)
            return;
        ui->NeedKillHL->setCurrentIndex(0);
        ui->NeedTalkNPC->setCurrentIndex(0);
        ui->NeedGetItem->setCurrentIndex(0);
    }
    void BoxChange3(){
        if(ui->NeedTalkNPC->currentIndex()==0)
            return;
        ui->NeedKillHL->setCurrentIndex(0);
        ui->NeedKillNPC->setCurrentIndex(0);
        ui->NeedGetItem->setCurrentIndex(0);
    }
    void BoxChange4(){
        if(ui->NeedGetItem->currentIndex()==0)
            return;
        ui->NeedKillHL->setCurrentIndex(0);
        ui->NeedKillNPC->setCurrentIndex(0);
        ui->NeedTalkNPC->setCurrentIndex(0);
    }

    void SetData();

public:
    Task tempTask;


private:
    Ui::NewTask *ui;
};


NewTask::NewTask() :ui(new Ui::NewTask){
    ui->setupUi(this);

    for(int i=1;i<200;i++){
        if(SystemTask[i].MB==0){
            tempTask.ID=i;
            break;
        }
    }

    ui->ID->setValue(tempTask.ID);
    ui->Name->setText(tempTask.Name);
    ui->Des->setText(tempTask.Des);

    int stop=0;
    ui->NeedTask->addItem("0：无需任务");
    while(true){
        stop++;
        if(SystemTask[stop].MB!=0)
            ui->NeedTask->addItem(QString::number(stop)+"："+SystemTask[stop].Name);
        else
            break;
    }

    ui->Target->setValue(tempTask.MB);

    ui->A_Coin->setValue(tempTask.A_Coin);
    ui->A_Exp->setValue(tempTask.A_Exp);
    ui->A_Count->setValue(tempTask.A_Count);

    SetData();


    connect(ui->NeedKillHL,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&NewTask::BoxChange1);
    connect(ui->NeedKillNPC,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&NewTask::BoxChange2);
    connect(ui->NeedTalkNPC,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&NewTask::BoxChange3);
    connect(ui->NeedGetItem,static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),this,&NewTask::BoxChange4);

}

NewTask::~NewTask()
{
    delete ui;
}

void NewTask::Save(){
tempTask.ID=ui->ID->value();
tempTask.Name=ui->Name->text();
tempTask.Des=ui->Des->text();
tempTask.Need_ID=ui->NeedTask->currentIndex();
tempTask.MB=ui->Target->value();
tempTask.NKillHL=ui->NeedKillHL->currentIndex();
tempTask.NKillNPC=ui->NeedKillNPC->currentIndex();
tempTask.NTalkNPC=ui->NeedTalkNPC->currentIndex();
tempTask.NGetItem=ui->NeedGetItem->currentIndex();
tempTask.A_Coin=ui->A_Coin->value();
tempTask.A_Exp=ui->A_Exp->value();
tempTask.A_Count=ui->A_Count->value();
tempTask.A_Item=ui->A_Item->currentIndex();
}

void NewTask::SetData(){
    ui->NeedKillHL->clear();
    ui->NeedKillNPC->clear();
    ui->NeedTalkNPC->clear();
    ui->NeedGetItem->clear();
    ui->A_Item->clear();

    int stop=0;
    ui->NeedKillHL->addItem("0：NULL");
    while(true){
        stop++;
        if(SystemHL[stop].Strength!=0)
            ui->NeedKillHL->addItem(QString::number(stop)+"："+SystemHL[stop].Name);
        else
            break;
    }
    stop=0;
    ui->NeedKillNPC->addItem("0：NULL");
    while(true){
        stop++;
        if(SystemNPC[stop].Ori_Strength!=0)
            ui->NeedKillNPC->addItem(QString::number(stop)+"："+SystemNPC[stop].Name);
        else
            break;
    }
    stop=0;
    ui->NeedTalkNPC->addItem("0：NULL");
    while(true){
        stop++;
        if(SystemNPC[stop].Ori_Strength!=0)
            ui->NeedTalkNPC->addItem(QString::number(stop)+"："+SystemNPC[stop].Name);
        else
            break;
    }
    stop=0;
    ui->NeedGetItem->addItem("0：NULL");
    while(true){
        stop++;
        if(SystemItem[stop].Type!=0)
            ui->NeedGetItem->addItem(QString::number(stop)+"："+SystemItem[stop].Name);
        else
            break;
    }



    stop=0;
    ui->A_Item->addItem("0：无");
    while(true){
        stop++;
        if(SystemItem[stop].Type!=0)
            ui->A_Item->addItem(QString::number(stop)+"："+SystemItem[stop].Name);
        else
            break;
    }
}

#endif // NEWTASK_H
