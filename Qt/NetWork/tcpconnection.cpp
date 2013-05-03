#include "tcpconnection.h"

TCPConnection::TCPConnection(const QString &host, quint16 port, QObject* parent) :
    QObject(parent), hostName(host), _port(port)
    {
    connect(&tcpSocket, SIGNAL(disconnected()), this, SLOT(connectServer()), Qt::QueuedConnection);
    connect(&tcpSocket, &QTcpSocket::error,
            [=](const QAbstractSocket::SocketError)
                    {
                    qWarning() << "connect error :" << socketError;
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
