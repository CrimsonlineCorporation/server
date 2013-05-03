#include "CLService.h"
#include <QIODevice>
#include <QJsonDocument>
#include <QVariant>
#include <QMap>
#include <QHostAddress>

CLService::CLService(const QString &host, quint16 port, QObject* parent) :
    QObject(parent), tcpConnection(host, port, parent)
    {
    connect(&tcpConnection, &TCPConnection::connected, this, &CLService::writeData);
    connect(&tcpConnection, &TCPConnection::readyRead, this, &CLService::readData);
    }
void CLService::start()
    {
    tcpConnection.startConnectingServer();
    }
void CLService::writeData()
    {
    QVariantMap battleServerInfo;
    battleServerInfo.insert(JSONKey_countBattles,  QThread::idealThreadCount());
    QJsonDocument jsonDocument;
    jsonDocument.setObject(QJsonObject::fromVariantMap(battleServerInfo));
    if(jsonDocument.isNull())
        qWarning() << "JSON serialize error";
    const QByteArray dataArrayUTF8 = (jsonDocument.isNull() ? "JSON serialize error" : jsonDocument.toJson());
    qDebug() << "writing :" << dataArrayUTF8;
    tcpConnection.write(dataArrayUTF8);
    }
void CLService::readData()
    {
    const QByteArray jsonText = tcpConnection.readAll();
    QJsonParseError jsonError ;
    const QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonText, &jsonError);
    if(!jsonDocument.isNull())
        {
        const QJsonObject connectJsonObject = jsonDocument.object();
        const QString readenHostName = connectJsonObject.value(JSONKey_connectAddress).toString();
        const QHostAddress host(readenHostName);
        const QString battleConnectHost =
                ((host==QHostAddress::LocalHost || host==QHostAddress::Null)
                 ? tcpConnection.peerName() : readenHostName);
        bool ok;
        const quint64 battleConnectPort = connectJsonObject.value(JSONKey_connectPort).toVariant().toULongLong(&ok);
        Q_ASSERT(ok==true);
        CLBattleServer* const newBattle = new CLBattleServer(battleConnectHost, battleConnectPort, this);
        battlesList << newBattle;
        QTimer::singleShot(0, newBattle, SLOT(startConnectingServer()));
        }
    else
        sendError(QString("JSON error in %2 symb of \"%1\": - err :\"%3\"").arg(QString(jsonText)).
                arg(jsonError.offset).arg(jsonError.errorString()));
    }
void CLService::sendError(const QString &errMessage)
    {
    qWarning() << errMessage;
    QJsonDocument jsonDocument;
    QVariantMap errInfo;
    errInfo.insert(JSONKey_error,  QThread::idealThreadCount());
    jsonDocument.setObject(QJsonObject::fromVariantMap(errInfo));
    if(jsonDocument.isNull())
        qWarning() << "JSON serialize error";
    tcpConnection.write(jsonDocument.toJson());
    }
