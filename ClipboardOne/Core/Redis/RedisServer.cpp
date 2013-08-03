#include "stdafx.h"
#include "RedisServer.h"

#include "RedisClient.h"

#include "Core/Settings.h"

#include "GUI/Logger/Logger.h"

RedisServer::RedisServer()
{
    ByteArrayGetter readStdout = std::bind(&QProcess::readAllStandardOutput, &process_);
    ByteArrayGetter readStderr = std::bind(&QProcess::readAllStandardError, &process_);

    DefaultFunctor logStdout = std::bind(logOutput, readStdout, LogEntry::Type::Output);
    DefaultFunctor logStderr = std::bind(logOutput, readStderr, LogEntry::Type::Error);

    QObject::connect(&process_, &QProcess::readyReadStandardOutput, logStdout);
    QObject::connect(&process_, &QProcess::readyReadStandardError, logStderr);

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

void RedisServer::logOutput(const ByteArrayGetter & messageGetter,
                            LogEntry::Type type)
{
    for(auto & output : messageGetter().split('\n'))
    {
        if(output.size())
            Logger::log(output.mid(25), type, LogEntry::Scope::Redis);
    }
};