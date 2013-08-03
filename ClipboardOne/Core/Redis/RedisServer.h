#ifndef REDISSERVER_H
#define REDISSERVER_H

#include "GUI/Logger/LogEntry.h"

class RedisClient;

class RedisServer : boost::noncopyable
{
    typedef std::function<QByteArray ()> ByteArrayGetter;

    public :
        static RedisServer & instance();
        static bool command(const QString &);

    private :
        RedisServer();
        ~RedisServer();

        static void clean();
        static void logOutput(const ByteArrayGetter &, LogEntry::Type);

        QProcess process_;
        std::unique_ptr<RedisClient> master_;
};

Constant REDIS_SERVER_CONF_FILE = "redis_config.conf";

#endif // REDISSERVER_H