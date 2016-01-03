QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += multimedia
TARGET = HLMain
TEMPLATE = app
CONFIG+=c++14
SOURCES += main.cpp

HEADERS  += \
    BeginWidget.h \
    ItemWidget.h \
    LGWidget.h \
    LHWidget.h \
    MapHLWidget.h \
    MapNPCWidget.h \
    TaskWidget.h \
    FightWidget.h \
    MainWidget.h \
    MapWidget.h \
    ../HLBase/HL_DiTu.h \
    ../HLBase/HL_FightSystem.h \
    ../HLBase/HL_GameSystem.h \
    ../HLBase/HL_HunJi.h \
    ../HLBase/HL_HunLing.h \
    ../HLBase/HL_Item.h \
    ../HLBase/HL_LingGu.h \
    ../HLBase/HL_LingHuan.h \
    ../HLBase/HL_NPC.h \
    ../HLBase/HL_RenWu.h \
    ../HLBase/HL_Task.h \
    Global.h

RESOURCES +=
