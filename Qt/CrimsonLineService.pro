#################################################################################
## CrimsonLine TCP service
## Features:
## * create battles
## * battles
#################################################################################

##qt libs
TEMPLATE    = app
VERSION     = 0.1
QT += core network
QT -= gui
CONFIG      += exceptions
#add C++11
QMAKE_CXXFLAGS += -std=c++0x


TARGET = CrimsonLineService
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    NetWork/tcpconnection.cpp \
    NetWork/CLBattleService.cpp \
    NetWork/CLBattleServer.cpp

#Box2d
BOX2D_WAY = e:/work/GameZZa/Box2D_v2.2.1
INCLUDEPATH += $${BOX2D_WAY}
LIBS += -L $${BOX2D_WAY}/Build/Box2D
LIBS += -l Box2D

HEADERS += \
    NetWork/tcpconnection.h \
    NetWork/CLBattleService.h \
    NetWork/CLBattleServer.h