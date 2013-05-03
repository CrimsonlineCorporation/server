#include "TCPConnection.h"

TCPConnection::TCPConnection(const QString &host, const quint16 port, QObject* parent) :
    QTcpSocket(parent), _hostName(host), _port(port)
    {
    connect(this, &QTcpSocket::disconnected,
            this, &TCPConnection::reConnectingServer, Qt::QueuedConnection);
    void (QAbstractSocket::*errSignal)(QAbstractSocket::SocketError)  = &QAbstractSocket::error;
    connect(this, errSignal, this, &TCPConnection::showError);
    }
void TCPConnection::startConnectingServer()
    {
    QTimer::singleShot(0, this, SLOT(reConnectingServer()));
    }
void TCPConnection::showError(const QAbstractSocket::SocketError socketError) const
    {
    qWarning() << "TCP error :" << socketError;
    }
void TCPConnection::reConnectingServer()
    {
    qDebug() << QString("try connecting to \"%1\":%2").arg(_hostName).arg(_port).toLatin1().constData();
    connectToHost(_hostName, _port);
    if(waitForConnected(_waitForConnectedTimemsecs))
        qDebug() << QString("connected to \"%1\":%2").arg(_hostName).arg(_port).toLatin1().constData();
    else
        QTimer::singleShot(0, this, SLOT(reConnectingServer()));
    }
