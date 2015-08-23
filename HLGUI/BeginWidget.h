/*开始界面*/
#ifndef BEGINWIDGET
#define BEGINWIDGET
#include<QSound>
#include<QString>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QVBoxLayout>
#include<MainWidget.h>
#include<QDialog>


class BeginWidget :public QWidget{
	public:
	QLabel Title;
	QLabel Text;
    PushButton Begin;
    PushButton Quit;
    QVBoxLayout MainLayout;
    MainWidget Main_W;
	public:
	BeginWidget();
	~BeginWidget(){}
	void Begin_Click();


};

BeginWidget::BeginWidget(){

this->setObjectName("Widget");
this->setWindowFlags(Qt::CustomizeWindowHint);
    this->setFixedSize(QSize(1000,480));
    Title.setText("魂灵师");
    Text.setText("这就是魂灵师……");
    Begin.setText("开始游戏");
    Quit.setText("退出");
    //MainLayout.addWidget(&Title);
   // MainLayout.addWidget(&Text);
    MainLayout.addWidget(&Begin);
    MainLayout.addWidget(&Quit);
    this->setLayout(&MainLayout);
    connect(&Begin,&QPushButton::clicked,this,&BeginWidget::Begin_Click);

    connect(&Quit,&QPushButton::clicked,this,&BeginWidget::close);
}

void BeginWidget::Begin_Click(){
   // QSound::play(DATAPATH+"6112.wav");
     QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
     animation->setDuration(1000);
     animation->setStartValue(1);
     animation->setEndValue(0);
     animation->start();


    //Main_W.setGeometry(this->geometry());

    QPropertyAnimation *animation1 = new QPropertyAnimation(&Main_W, "windowOpacity");
     animation1->setDuration(1000);
     animation1->setStartValue(0);
     animation1->setEndValue(1);
     animation1->start();

/*开场白*/
     QFile file1((DATAPATH+"global.sav"));
   file1.open(QIODevice::ReadOnly);
   QTextStream in1(&file1);
   int temp=0;
     in1>>temp;
     file1.close();
temp=0;//!!!!
     if(temp==0){
         MessageBox::about(this,"介绍","世界背景:这是一个充满玄幻色彩的世界。人们拥有特殊的力量，叫做魂力和灵力，通过这些力量，他们可以与魂灵联系，控制魂灵，甚至杀死魂灵，后来人们发现利用这种力量可以把魂灵变成灵环，像手镯一样带在手上，魂灵和灵力也储存在其中，这样就不用把魂灵带在身边！后来也约定俗成，尽量不把自己的魂灵暴露出来，而是戴在手上！魂灵原本主宰着这片大陆，但某一天，一只猴子聪明的发现了如何使用树枝去插鱼。就这样慢慢的进化成人类，人类的足迹遍布大陆。一些没有灵智的魂灵就只能当魂灵，慢慢修炼，通常人类修炼一年，魂灵就要修炼十年，人类能活100岁，但并不是每一个魂灵都能活1000岁，当然一些有少许灵智的魂灵能成功突破，活到千岁以上，也只是个别而已，他们都成为了魂灵们的首领。人类修为达到一定程度，也能突破年龄限制，活的更久！世界是一片完整的大陆，大概有5000万人口，这个世界文明的发展只有唐朝水平，世界由一个个村子城堡组成，但他们对自身能力的理解却非常清楚，比如他们的灵环。他们经过千年的积累，终于在灵环，魂灵方面有所突破，他们有自己的测量工具，可以测出自己的力量。他们还把跟他们生活在一起的魂灵的一切信息记录下来。当然，有些特别强大的魂灵，人们还无法探究。不过人们依然在努力！这个世界由三个帝国统治着，分别是A帝国，B帝国，C帝国，他们之间相处得还是很和平，A帝国在世界左上方，B帝国在右上方，C帝国在下方，占地面积几乎一样。但是每个帝国的发展方向又不一样。A帝国因为拥有一座火山，拥有特别的火系魂灵，他们似乎还与之交流过，所以另外两个帝国也不敢轻举妄动。B帝国拥有大面积的森林，魂灵种类是最多的，目前帝国还无法探进森林内部。C帝国因为海岸线广阔，对海洋的探索比较多，但是海洋里到底有多少魂灵，也无法统计！除了帝国，这个世界也有许多大大小小的宗派，他们大都隐匿起来，很少与世俗接触。帝国的力量来源，宗派也占了一大部分。A帝国因为有A宗和B宗，实力也特别强大，其中A宗拥有2000年历史。当时世界还是只有一个统治者，因为A宗的出现，使远方的一些魂灵师惧怕。因为A宗对那座火山的研究非常透彻，获得了一些能力。某一天，那座火山喷发了，使当地人民死伤无数，人们无知，认为是A宗搞的坏事，于是远方的魂灵师纷纷组织起宗派，与之对抗，后来远方魂灵师因为有帝国的支持，获得了胜利，但是帝国也无法攻入A宗内部，所以世界分为两个部分。后来A宗沉迷于魂灵的力量，和对火山的好奇，那一片地方也由另一个统治者统治，称为A帝国。一千年后，人们对魂灵的了解越来越深，对魂灵的需求也越来越大，于是魂灵的数量也越来越少，在东北方的大森林更是突出！东北的百姓和魂灵师开始意识到重要性，呼吁人们少点捕猎，但是南方的人民却不听，于是引发了魂灵们的反击，在森林内部的魂灵也出来与人类作战，也从那一次露面后，森林内部的魂灵也就没出现过了。因此另一片大陆也分为两部分，就是B帝国与C帝国。慢慢和平的发展到今天。大大小小的宗派也建立起来了！");

     }


     QFile file((DATAPATH+"global.sav"));
   file.open(QIODevice::WriteOnly);
   QTextStream in(&file);
     in<<1<<endl;
     file.close();



    Main_W.show();

}

#endif
