#include "CLBattleService.h"
#include <QIODevice>
#include <QJsonDocument>
#include <QVariant>
#include <QHostAddress>

CLBattleService::CLBattleService(const QString &hostName, quint16 port, QObject* parent) :
    TCPConnection(hostName, port, parent)
    {
    connect(&tcpSocket, &QTcpSocket::connected, this, &CLBattleService::writeData);
    connect(&tcpSocket, &QTcpSocket::readyRead, this, &CLBattleService::readData);
    }
void CLBattleService::writeData()
    {
    QVariantMap battleServerInfo;
    battleServerInfo.insert(JSONKey_countBattles,  QThread::idealThreadCount());
    QJsonDocument jsonDocument;
    jsonDocument.setObject(QJsonObject::fromVariantMap(battleServerInfo));
    if(jsonDocument.isNull())
        qWarning() << "JSON serialize error";
    const QByteArray dataArrayUTF8 = (jsonDocument.isNull() ? "JSON serialize error" : jsonDocument.toJson());
    qDebug() << "writing :" << dataArrayUTF8;
    tcpSocket.write(dataArrayUTF8);
    }
void CLBattleService::readData()
    {
    const auto jsonText = tcpSocket.readAll();
    QJsonParseError jsonError ;
    const QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonText, &jsonError);
    if(!jsonDocument.isNull())
        {
        const QJsonObject connectJsonObject = jsonDocument.object();
        const QString readenHostName = connectJsonObject.value(JSONKey_connectAddress).toString();
        const QHostAddress host(readenHostName);
        const QString battleConnectHost =
                ((host==QHostAddress::LocalHost || host==QHostAddress::Null)
                 ? tcpSocket.peerName() : readenHostName);
        bool ok;
        const quint64 battleConnectPort = connectJsonObject.value(JSONKey_connectPort).toVariant().toULongLong(&ok);
        if(ok){
            CLBattleServer* newBattle = new CLBattleServer(battleConnectHost, battleConnectPort, this);
            battlesList << newBattle;
            newBattle->connectServer();
            }
        else
            warning(QString("wrong convert ") + JSONKey_connectPort);
        }
    else
        warning(QString("parse JSON error in %2 symb of \"%1\": - err :\"%3\"").arg(QString(jsonText)).
                arg(jsonError.offset).arg(jsonError.errorString()));
    }


void CLBattleService::warning(const QString &errMessage)
    {
    qWarning() << errMessage;

    QJsonDocument jsonDocument;
    QVariantMap errInfo;
    errInfo.insert(JSONKey_countBattles,  QThread::idealThreadCount());
    jsonDocument.setObject(QJsonObject::fromVariantMap(errInfo));
    if(jsonDocument.isNull())
        qWarning() << "JSON serialize error";
    tcpSocket.write(jsonDocument.toJson());
    }
