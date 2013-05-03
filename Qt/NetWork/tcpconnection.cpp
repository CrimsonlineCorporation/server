#include "tcpconnection.h"

TCPConnection::TCPConnection(const QString &host, const quint16 port, QObject* parent) :
    QObject(parent), _hostName(host), _port(port)
    {
    connect(&tcpSocket, &QAbstractSocket::disconnected,
            this, &TCPConnection::connectServer, Qt::QueuedConnection);
    connect(&tcpSocket, &QAbstractSocket::stateChanged,
            [](QAbstractSocket::SocketState)
                    {
                    } );
    void (QTcpSocket::*errSignal)(QAbstractSocket::SocketError)  = &QTcpSocket::error;
    connect(&tcpSocket, errSignal,
            [](const QAbstractSocket::SocketError socketError)
                    {
                    qWarning() << "TCP error :" << socketError;
                    } );
    }
void TCPConnection::connectServer()
    {
    qDebug() << QString("try connecting to \"%1\":%2").arg(_hostName).arg(_port).toLatin1().constData();
    tcpSocket.connectToHost(_hostName, _port);
    if(tcpSocket.waitForConnected(_waitForConnectedTimemsecs))
        qDebug() << QString("connected to \"%1\":%2").arg(_hostName).arg(_port).toLatin1().constData();
    else
        QTimer::singleShot(0, this, SLOT(connectServer()));
    }
