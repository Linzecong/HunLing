/*显示背包*/

#ifndef ITEMWIDGET
#define ITEMWIDGET

#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QPixmap>
#include<QPushButton>
#include<QListWidget>
#include<QMessageBox>
#include<../HLBase/HL_RenWu.h>
#include<../HLBase/HL_Item.h>

class ItemWidget:public QDialog{
	public:
    QList<Item*> Bag;
    RenWu* Me;
	QLabel Title;
	QPushButton Use;
    QListWidget Item_List;
	QLabel Name;
	QLabel Des;
	QLabel Value;
	QLabel Count;
    QHBoxLayout* MainLayout;
    QVBoxLayout* LabelLayout;
	public:
    ItemWidget(RenWu* a);
    ~ItemWidget(){}
	void Use_Click();
    void UpDate();
    void UpDateList();
    void change(){Use.setEnabled(true);}
};

ItemWidget::ItemWidget(RenWu* a){
    MainLayout=new QHBoxLayout;
    LabelLayout=new QVBoxLayout;
    Me=a;
    for(int i=0;i<a->Bag.size();i++)
    Bag.append(&Me->Bag[i]);
    Title.setText("背包");
    Use.setText("使用");
    Use.setEnabled(false);
    for(int i=0;i<Bag.size();i++)
      Item_List.addItem(Bag[i]->Name);

    Name.setText("名字：");
    Des.setText("作用：");
    Value.setText("价值：");
    Count.setText("数量：");
    LabelLayout->addWidget(&Name);
    LabelLayout->addWidget(&Des);
    LabelLayout->addWidget(&Value);
    LabelLayout->addWidget(&Count);
    LabelLayout->addWidget(&Use);
    MainLayout->addWidget(&Title);
    MainLayout->addWidget(&Item_List);
    MainLayout->addLayout(LabelLayout);
    connect(&Item_List,&Item_List.clicked,this,&ItemWidget::UpDate);
    connect(&Use,&Use.clicked,this,&ItemWidget::Use_Click);
    connect(&Item_List,&QListWidget::currentRowChanged,this,&ItemWidget::change);
    this->setLayout(MainLayout);
}

void ItemWidget::Use_Click(){
    int temp=Item_List.currentRow();

    Item a=*(Bag[temp]);
    if(a.Type==1){
    Bag.removeAt(temp);
    Me->UseItem(a);
    QMessageBox::about(this,"提示","使用成功！");
    }
    if(a.Type==2)
        QMessageBox::about(this,"提示","此道具只能战斗中使用！");
    if(a.Type==3)
       QMessageBox::about(this,"提示","此道具不能使用！");
    UpDateList();
}

void ItemWidget::UpDate(){
     int temp=Item_List.currentRow();
     Item a=*(Bag[temp]);
     Name.setText("名字："+a.Name);
     Des.setText("作用："+a.Des);
     Value.setText("价值："+a.Value);
     Count.setText("数量："+Bag[temp]->Count);
}

void ItemWidget::UpDateList(){
     Item_List.clear();
     for(int i=0;i<Bag.size();i++)
       Item_List.addItem(Bag[i]->Name);
}

#endif







