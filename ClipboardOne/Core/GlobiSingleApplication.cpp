#include "stdafx.h"
#include "GlobiSingleApplication.h"

GlobiSingleApplication::GlobiSingleApplication(int & argc, char ** argv, const QString & id) : 
    QApplication(argc, argv), appId_(id), outStream_(&appSocket_)
{
    appSocket_.connectToServer(appId_);
    isAlreadyRunning_ = appSocket_.waitForConnected();

    appServer_.listen(appId_);
    QObject::connect(&appServer_, &QLocalServer::newConnection, 
                     this, &GlobiSingleApplication::onNewConnection);
}

GlobiSingleApplication::~GlobiSingleApplication()
{
    appServer_.close();
}

bool GlobiSingleApplication::isAlreadyRunning() const
{
    return isAlreadyRunning_;
}

void GlobiSingleApplication::onNewConnection()
{
    otherAppSocket_ = appServer_.nextPendingConnection();
    if(otherAppSocket_)
    {
        QObject::connect(otherAppSocket_, &QLocalSocket::readyRead,
                         this, &GlobiSingleApplication::onReadyRead);
    }
}

void GlobiSingleApplication::sendMessage(const QString & message)
{
    outStream_ << message;
    outStream_.flush();
}

void GlobiSingleApplication::onReadyRead()
{
    Q_EMIT messageRceived(otherAppSocket_->readAll());
}
