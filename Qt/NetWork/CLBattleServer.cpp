#include "CLBattleServer.h"
#include <QJsonDocument>

CLBattleServer::CLBattleServer(const QString &host, const quint16 port, QObject *parent) :
    TCPConnection(host, port, parent)
    {
    connect(&tcpSocket, SIGNAL(connected()), this, SLOT(writeData()));
    connect(&tcpSocket, SIGNAL(readyRead()), this, SLOT(readData()));
    }
void CLBattleServer::writeData()
    {
    QVariantMap battleServer;
    battleServer["hello"] = " i don't know what i should sent =(";
    QJsonDocument jsonDocument;
    jsonDocument.setObject(QJsonObject::fromVariantMap(battleServer));
    if(jsonDocument.isNull())
        qWarning() << "JSON serialize error";
    const QByteArray dataArrayUTF8 = (jsonDocument.isNull() ? "JSON serialize error" : jsonDocument.toJson());
    qDebug() << "writing :" << dataArrayUTF8;
    tcpSocket.write(dataArrayUTF8);
    }
void CLBattleServer::readData()
    {
    }
