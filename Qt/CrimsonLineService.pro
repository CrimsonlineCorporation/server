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

#Box2d
BOX2D_WAY = e:/work/GameZZa/Box2D_v2.2.1
INCLUDEPATH += $${BOX2D_WAY}
LIBS += -L $${BOX2D_WAY}/Build/Box2D
LIBS += -l Box2D

HEADERS += \
    NetWork/CLService.h \
    NetWork/TCPConnection.h \
    NetWork/CLBattleService.h
SOURCES += \
    main.cpp \
    QtErrorMessageHandler.cpp \
    NetWork/CLService.cpp \
    NetWork/TCPConnection.cpp \
    NetWork/CLBattleService.cpp
