#pragma once
#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H
#include <QtCore>
#include <QtNetwork/QTcpSocket>
/*
 * QTcpSocket connect wrapper
 * TODO: add SSL
 */
class TCPConnection : public QObject
{
    Q_OBJECT
public:
    explicit TCPConnection(const QString &host, quint16 port, QObject *parent = NULL);
public slots:
    void connectServer();
protected:
    QTcpSocket tcpSocket;
private:
    const QString hostName;
    const quint16 _port;
    static constexpr quint16 waitForConnectedTimemsecs = 5000;
};

#endif // TCPCONNECTION_H
