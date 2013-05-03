#include "TCPConnection.h"

TCPConnection::TCPConnection(const QString &host, const quint16 port, QObject* parent) :
    QTcpSocket(parent), _hostName(host), _port(port)
    {
    connect(this, &QTcpSocket::disconnected,
            this, &TCPConnection::startConnectingServer, Qt::QueuedConnection);
    void (QTcpSocket::*errSignal)(QAbstractSocket::SocketError)  = &QTcpSocket::error;
    connect(this, errSignal, this, &TCPConnection::showError );
    }
void TCPConnection::startConnectingServer()
    {
    qDebug() << QString("try connecting to \"%1\":%2").arg(_hostName).arg(_port).toLatin1().constData();
    connectToHost(_hostName, _port);
    if(waitForConnected(_waitForConnectedTimemsecs))
        qDebug() << QString("connected to \"%1\":%2").arg(_hostName).arg(_port).toLatin1().constData();
    else
        QTimer::singleShot(0, this, SLOT(startConnectingServer()));
    }
void TCPConnection::showError(const QAbstractSocket::SocketError socketError) const
    {
    qWarning() << "TCP error :" << socketError;
    }
