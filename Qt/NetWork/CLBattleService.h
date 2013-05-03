#pragma once
#ifndef CLBattleService_H
#define CLBattleService_H
#include <QtCore>
#include <QObject>
#include "tcpconnection.h"
#include <Box2D/Box2D.h>
/*
 * Battle engine with
 *  * TCPServer implementaion
 * TODO: * SciptEngine implementaion
 */
class CLBattleService : public QObject
{
    Q_OBJECT
public:
    explicit CLBattleService(const QString &host, const quint16 port, QObject* parent = NULL);
    inline void start();
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
};      // CLBattleService
void CLBattleService::start()
    {
    tcpConnection.startConnectingServer();
    }
#endif  // CLBattleService_H
