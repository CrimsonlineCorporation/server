/****************************************************************************
**
** Copyright (C) 2011-2013 CONCERN CSRI ELEKTROPRIBOR, JSC and/or its subsidiary(-ies).
** All rights reserved.
** Contact: CONCERN CSRI ELEKTROPRIBOR (http://www.elektropribor.spb.ru/)
** Authors contacts:
**        Elisey Zamakhov (EliseyZamahov@gmail.com)
**
** This file is part of the Rakurs-4 applications.
**
**
**
** Created 14.03.2012 by Zamakhov_EY.
****************************************************************************/
#include <iostream>
#include <QObject>
#include <QtCore>
/*
 * Stop macro for Win
 */
#if defined(Q_OS_WIN) && defined(QT_DEBUG)
    #define INTERAPT() DebugBreak();
#elif defined(QT_DEBUG)
#define INTERAPT() static_assert("no interapting for platform");
#else
#define INTERAPT() qt_noop();
#endif

inline QString messageToStr(const QString& typeString, const QMessageLogContext &context, const QString& msgStr)
    {
    const QFileInfo fileInfo(context.file);
    return QString("%1%2 (%3 %4:%5)").
            arg(typeString).arg(msgStr).arg(context.function).arg(fileInfo.fileName()).arg(context.line);
    }
inline QString messageToStr(const QtMsgType type, const QMessageLogContext &context, const QString& msgStr)
    {
    switch (type)
        {//QtDebugMsg is at end of function
        case QtWarningMsg:
            return messageToStr(QLatin1Literal("Warning : "), context, msgStr);
        case QtCriticalMsg:
            return messageToStr(QLatin1Literal("Critical : "), context, msgStr);
        case QtFatalMsg://only in debug (not release mode)
            return messageToStr(QLatin1Literal("FatalMsg : "), context, msgStr);
        default:
            break;
        }
    //QtDebugMsg
    return messageToStr(QLatin1Literal(""), context, msgStr);
    }
//void WriteToFileLog(QtMsgType type, const char *cmsg)
void WriteToFileLog(QtMsgType type, const QMessageLogContext &context,const QString& msgStr)
    {
    if(msgStr == "QIODevice::open: File access not specified") {
        INTERAPT();
        return;
        }
    static const QString logFileWay = qApp->applicationName() + QLatin1Literal(".log");
    QFile errFile(logFileWay);
    if(!errFile.open(QIODevice::WriteOnly |QIODevice::Append | QIODevice::Text)){
        fprintf(stderr, "errfile not opened\n" );
        INTERAPT();
        return;
        }
    QTextStream errStream(&errFile);
    errStream << QDateTime::currentDateTime().toString(Qt::SystemLocaleShortDate) << QLatin1Char(' ');
    errStream << messageToStr(type, context, msgStr) << endl;
    }

void MessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msgStr) {
    static QMutex fileWriteMuteq;
    //lock for writing
    const QMutexLocker locker(&fileWriteMuteq);
    WriteToFileLog(type, context, msgStr);
#ifdef RakursUnitTesting
    if(type == QtDebugMsg) return;
#endif
    const std::wstring outUnicodeStr = messageToStr(type, context, msgStr).toStdWString();
#ifdef QT_DEBUG
    std::cout << QString::fromStdWString(outUnicodeStr).toLocal8Bit().constData() << std::endl << std::flush;
    if(type == QtFatalMsg || type == QtCriticalMsg || msgStr.contains("FAIL!")) INTERAPT();
#else
    std::wclog << outUnicodeStr << std::endl << std::flush;
#endif
    }
