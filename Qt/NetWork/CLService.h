#pragma once
#ifndef CrimsonLineMaineService_H
#define CrimsonLineMaineService_H
#include <QtCore>
#include <QObject>
#include "tcpconnection.h"
#include "CLBattleServer.h"
/*
 * This class connect to Java server and wait commandes to create battles
 * Handle battles.
 */
class CLService : public QObject
{
    Q_OBJECT
public:
    explicit CLService(const QString &host, quint16 port, QObject *parent = NULL);
    void start();
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
    QList<CLBattleServer*> battlesList;
};      // CrimsonLineMaineService
#endif  // CrimsonLineMaineService_H
