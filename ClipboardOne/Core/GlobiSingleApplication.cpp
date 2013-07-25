#include "stdafx.h"
#include "GlobiSingleApplication.h"

GlobiSingleApplication::GlobiSingleApplication(int & argc, char ** argv, const QString & id) : 
    QApplication(argc, argv), _appId(id), _outStream(&_appSocket)
{
    _appSocket.connectToServer(_appId);
    _isAlreadyRunning = _appSocket.waitForConnected();

    _appServer.listen(_appId);
    QObject::connect(&_appServer, &QLocalServer::newConnection, 
                     this, &GlobiSingleApplication::onNewConnection);
}

GlobiSingleApplication::~GlobiSingleApplication()
{
    _appServer.close();
}

bool GlobiSingleApplication::isAlreadyRunning() const
{
    return _isAlreadyRunning;
}

void GlobiSingleApplication::onNewConnection()
{
    _otherAppSocket = _appServer.nextPendingConnection();
    if(_otherAppSocket)
    {
        QObject::connect(_otherAppSocket, &QLocalSocket::readyRead,
                         this, &GlobiSingleApplication::onReadyRead);
    }
}

void GlobiSingleApplication::sendMessage(const QString & message)
{
    _outStream << message;
    _outStream.flush();
}

void GlobiSingleApplication::onReadyRead()
{
    emit messageRceived(_otherAppSocket->readAll());
}
