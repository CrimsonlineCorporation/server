#pragma once
#ifndef TCPConnection_H
#define TCPConnection_H
#include <QtCore>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QAbstractSocket>
/*
 * QTcpSocket connect wrapper
 * TODO: add SSL
 */
class TCPConnection : public QTcpSocket
{
    Q_OBJECT
public:
    explicit TCPConnection(const QString &host, const quint16 port, QObject *parent = NULL);
public slots:
    void startConnectingServer();
protected slots:
    void showError(const SocketError socketError) const;
    void reConnectingServer();
private:
    const QString _hostName;
    const quint16 _port;
    static constexpr quint16 _waitForConnectedTimemsecs = 5000;
};      // TCPConnection
#endif  // TCPConnection_H
