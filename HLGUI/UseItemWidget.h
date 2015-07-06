
#include<QString>
#include<QDialog>
#include<QLabel>
#include<QVBoxLayout>
#include<QPushButton>
#include<QListWidget>
//#include"HLQTData/HL_Item.h"

class UseItemWidget:public QDialog
{
	public:
    ItemList* Bag;
	Item Used;
	QLabel Title;
	QPushButton Use;

	QListWidget myItemList;
	QLabel Name;
	QLabel Des;
	QLabel Value;
	QLabel Count;
	public:
    UseItemWidget(ItemList* a);
    ~UseItemWidget(){}

};


UseItemWidget::UseItemWidget(ItemList* a)
{
    Bag=a;
}
