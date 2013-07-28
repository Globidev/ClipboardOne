#include "stdafx.h"
#include "RedisServer.h"

#include "RedisClient.h"

#include "Core/Settings.h"

RedisServer::RedisServer()
{
    QObject::connect(&process_, &QProcess::readyReadStandardOutput, [this]
    {
        qDebug() << process_.readAllStandardOutput();
    });

    QObject::connect(&process_, &QProcess::readyReadStandardError, [this]
    {
        qDebug() << process_.readAllStandardError();
    });

    process_.setWorkingDirectory(Settings::directory());

    QStringList arguments;
    arguments << QDir(QDir::currentPath()).filePath(REDIS_SERVER_CONF_FILE);

    process_.start(REDIS_SERVER_EXECUTABLE, arguments);
    process_.waitForStarted();

    master_.reset(new RedisClient);

    qAddPostRoutine(clean);
}

RedisServer::~RedisServer()
{
    
}

RedisServer & RedisServer::instance()
{
    static RedisServer redisServer;
    return redisServer;
}

void RedisServer::clean()
{
    auto & self = instance();
    self.master_->sendCommand(REDIS_SHUTDOWN_COMMAND);
    self.process_.waitForFinished();
}

bool RedisServer::command(const QString & commandString)
{
    return instance().master_->sendCommand(commandString);
}