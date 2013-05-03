#pragma once
#ifndef CrimsonLineMaineService_H
#define CrimsonLineMaineService_H
#include <QtCore>
#include <QObject>
#include "tcpconnection.h"
#include "CLBattleService.h"
/*
 * This class connect to Java server and wait commandes to create battles
 * Handle battles.
 */
class CLService : public QObject
{
    Q_OBJECT
public:
    explicit CLService(const QString &host, quint16 port, QObject *parent = NULL);
    inline void start();
    static constexpr auto JSONKey_countBattles      = "countBattles";
    static constexpr auto JSONKey_connectAddress    = "connectAddress";
    static constexpr auto JSONKey_connectPort       = "connectPort";
    static constexpr auto JSONKey_error             = "error";
protected slots:
    void writeData();
    void readData();
private:
    TCPConnection tcpConnection;
    void sendError(const QString& str);
    QList<CLBattleService*> battlesList;
};      // CrimsonLineMaineService
void CLService::start()
    {
    tcpConnection.startConnectingServer();
    }
#endif  // CrimsonLineMaineService_H
