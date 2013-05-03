#pragma once
#ifndef CLBattleServer_H
#define CLBattleServer_H
#include <QtCore>
#include <QObject>
#include "tcpconnection.h"
/*
 * Battle engine with
 *  * TCPServer implementaion
 * TODO: * Box2d implementaion
 * TODO: * SciptEngine implementaion
 */
class CLBattleServer : public TCPConnection
{
    Q_OBJECT
public:
    explicit CLBattleServer(const QString &host, const quint16 port,
                            QObject* parent = NULL);

    static constexpr auto SendType_ID   = "sendType";
    static constexpr auto BATTLE_ID     = "battleId";
    static constexpr auto PLAYERS_NUM   = "playersNum";
    static constexpr auto MONSTERS_NUM  = "monstersNum";
protected slots:
    void writeData();
    void readData();
private:
};      //CLBattleServer_H
#endif  // CLBattleServer_H
