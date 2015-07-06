#include<QString>
#include<QWidget>
#include<QLabel>
#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QPushButton>
class MapWidget: public QWidget
{
	public:
    DiTu Map;
    RenWu Me;
    NPCList NPC_List;
    LHList Enemy_List;
    MapHLWidget* MapHL[10];
    MapNPCWidget* MapNPC[10];
	QLabel Title;
    QHBoxLayout* Layout1;
    QHBoxLayout* Layout2;
    QVBoxLayout* MainLayout;
	public:
    MapWidget(DiTu a,RenWu b);
    ~MapWidget()
    {

    }

    void UpDate(DiTu a,RenWu b);



};

MapWidget::MapWidget(DiTu a,RenWu b)
{
    Layout1=new QHBoxLayout;
    Layout2=new QHBoxLayout;
    MainLayout=new QVBoxLayout;
    Map=a;
    Me=b;

    NPC_List=GameSystem::CanShowList(Map,&Me);
    Enemy_List=GameSystem::CreateLHList(Map);
    for(int i=1;i<=NPC_List.Count();i++)
        MapNPC[i]=new MapNPCWidget(Me,NPC_List.GetData(i));
    for(int i=NPC_List.Count();i<9;i++)
        MapNPC[i+1]=new MapNPCWidget();

    for(int i=1;i<=Enemy_List.Count();i++)
        MapHL[i]=new MapHLWidget(Me,Enemy_List);
    for(int i=Enemy_List.Count();i<9;i++)
        MapHL[i+1]=new MapHLWidget();

    Title.setText(Map.Name);
    for(int i=1;i<=9;i++)
    Layout1->addWidget(MapHL[i]);
    for(int i=1;i<=9;i++)
    Layout2->addWidget(MapNPC[i]);
    MainLayout->addWidget(&Title);
    MainLayout->addLayout(Layout1);
    MainLayout->addLayout(Layout2);
    this->setLayout(MainLayout);







}

void MapWidget::UpDate(DiTu a,RenWu b)
{


    Map=a;
    Me=b;

    NPC_List=GameSystem::CanShowList(Map,&Me);
    Enemy_List=GameSystem::CreateLHList(Map);
    for(int i=1;i<=NPC_List.Count();i++)
        MapNPC[i]=new MapNPCWidget(Me,NPC_List.GetData(i));
    for(int i=NPC_List.Count();i<9;i++)
        MapNPC[i+1]=new MapNPCWidget();

    for(int i=1;i<=Enemy_List.Count();i++)
        MapHL[i]=new MapHLWidget(Me,Enemy_List);
    for(int i=Enemy_List.Count();i<9;i++)
        MapHL[i+1]=new MapHLWidget();

    Title.setText(Map.Name);


}
















