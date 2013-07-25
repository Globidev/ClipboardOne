#include "stdafx.h"
#include "RedisServer.h"

#include "RedisClient.h"

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

    process_.start(REDIS_SERVER_EXECUTABLE);
    process_.waitForStarted();

    master_ = std::unique_ptr<RedisClient>(new RedisClient);

    qAddPostRoutine([] { clean(); });
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