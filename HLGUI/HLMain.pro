QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HLMain
TEMPLATE = app

SOURCES += main.cpp

HEADERS  += \
    BeginWidget.h \
    ItemWidget.h \
    LGWidget.h \
    LHWidget.h \
    MapHLWidget.h \
    MapNPCWidget.h \
    TaskWidget.h \
    TimeWidget.h \
    FightWidget.h \
    MainWidget.h \
    MapWidget.h \
    HLQTData/HL_DiTu.h \
    HLQTData/HL_FightSystem.h \
    HLQTData/HL_GameSystem.h \
    HLQTData/HL_HunJi.h \
    HLQTData/HL_HunLing.h \
    HLQTData/HL_Item.h \
    HLQTData/HL_LingGu.h \
    HLQTData/HL_LingHuan.h \
    HLQTData/HL_NPC.h \
    HLQTData/HL_RenWu.h \
    HLQTData/HL_Task.h \
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
    ../HLBase/HL_Task.h

RESOURCES +=
