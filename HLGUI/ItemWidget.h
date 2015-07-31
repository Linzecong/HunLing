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
    RenWu* Me;

    PushButton Use;
    PushButton Close;
    QListWidget Item_List;
	QLabel Name;
	QLabel Des;
	QLabel Value;
	QLabel Count;

	public:
    ItemWidget(RenWu* a);
    ~ItemWidget(){}
	void Use_Click();
    void UpDate();
    void UpDateList();
    void change(){Use.setEnabled(true);}
};

ItemWidget::ItemWidget(RenWu* a){
    this->setObjectName("item");
    Use.setObjectName("function");
    Close.setObjectName("close");

    Item_List.setFocusPolicy(Qt::NoFocus);
    this->setWindowFlags (Qt::CustomizeWindowHint);
    this->setFixedSize(305,255);
    Use.setParent(this);
    Close.setParent(this);
    Item_List.setParent(this);
    Name.setParent(this);
    Des.setParent(this);
    Value.setParent(this);
    Count.setParent(this);

    Item_List.setGeometry(5,5,200,200);
    Name.setGeometry(210,0,100,42);
    Value.setGeometry(210,45,100,42);
    Count.setGeometry(210,90,100,42);
    Use.setGeometry(210,135,90,30);
    Close.setGeometry(210,173,90,30);

    Des.setGeometry(5,193,300,50);
Des.setWordWrap(true);



    Me=a;

    Use.setText("使用");
    Close.setText("关闭");
    Use.setEnabled(false);
    for(int i=0;i<Me->Bag.size();i++){
        QIcon icon;
        QPixmap pix;
        pix.load("./Data/背景.jpg");
        icon.addPixmap(pix);
      QListWidgetItem* item=new QListWidgetItem(icon,Me->Bag[i].Name,&Item_List);
      Item_List.addItem(item);
    }



    Name.setText("名字：");
    Des.setText("作用：");
    Value.setText("价值：");
    Count.setText("数量：");


    connect(&Item_List,&QListWidget::clicked,this,&ItemWidget::UpDate);
    connect(&Use,&QPushButton::clicked,this,&ItemWidget::Use_Click);
    connect(&Item_List,&QListWidget::clicked,this,&ItemWidget::change);
    connect(&Close,&QPushButton::clicked,this,&ItemWidget::close);


}

void ItemWidget::Use_Click(){

    int temp=Item_List.currentRow();


    if(Me->Bag[temp].Type==1){
    MessageBox::about(NULL,"提示","使用成功！");
    Me->UseItem(Me->Bag[temp]);

    UpDateList();
    return;
    }
    if(Me->Bag[temp].Type==2)
        MessageBox::about(this,"提示","此道具只能战斗中使用！");
    if(Me->Bag[temp].Type==3)
       MessageBox::about(this,"提示","此道具不能使用！");

}

void ItemWidget::UpDate(){
     int temp=Item_List.currentRow();
     if(temp<0){
         Name.setText("名字：");
         Des.setText("作用：");
         Value.setText("价值：");
         Count.setText("数量：");
         Use.setEnabled(false);
         return;
     }
     Name.setText(Me->Bag[temp].Name);
     Des.setText("作用："+Me->Bag[temp].Des);
     Value.setText("价值："+QString::number(Me->Bag[temp].Value));
     Count.setText("数量："+QString::number(Me->Bag[temp].Count));
}

void ItemWidget::UpDateList(){
     Item_List.clear();
     for(int i=0;i<Me->Bag.size();i++)
       Item_List.addItem(Me->Bag[i].Name);
     Use.setEnabled(false);
     UpDate();
}

#endif







