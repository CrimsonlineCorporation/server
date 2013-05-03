#include "tcpconnection.h"

TCPConnection::TCPConnection(const QString &host, const quint16 port, QObject* parent) :
    QObject(parent), hostName(host), _port(port)
    {
    connect(&tcpSocket, &QTcpSocket::disconnected,
            this, &TCPConnection::connectServer, Qt::QueuedConnection);
    connect(&tcpSocket, &QTcpSocket::error,
            [=](const QAbstractSocket::SocketError)
                    {
                    qWarning() << "TCP error :" << socketError;
                    } );
    }
void TCPConnection::connectServer()
    {
    qDebug() << QString("try connecting to \"%1\":%2").arg(hostName).arg(_port).toLatin1().constData();
    tcpSocket.connectToHost(hostName, _port);
    if(tcpSocket.waitForConnected(waitForConnectedTimemsecs))
        qDebug() << QString("connected to \"%1\":%2").arg(hostName).arg(_port).toLatin1().constData();
    else
        QTimer::singleShot(0, this, SLOT(connectServer()));
    }
