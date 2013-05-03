#pragma once
#ifndef CLBattleServer_H
#define CLBattleServer_H
#include <QtCore>
#include <QObject>
#include "tcpconnection.h"
#include <Box2D/Box2D.h>
/*
 * Battle engine with
 *  * TCPServer implementaion
 * TODO: * SciptEngine implementaion
 */
class CLBattleServer : public QObject
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
    TCPConnection tcpConnection;
    // Define world with zero gravity
    b2World world{b2Vec2(0.0f, 0.0f)};
    b2AABB worldAABB;
    void createLive();
};      // CLBattleServer_H
#endif  // CLBattleServer_H
