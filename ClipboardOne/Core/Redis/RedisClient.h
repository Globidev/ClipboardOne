#ifndef REDISCLIENT_H
#define REDISCLIENT_H

class RedisClient : boost::noncopyable
{
    public :
        RedisClient(const char * = LOCALHOST_IP, int = REDIS_DEFAULT_PORT);

        bool connected() const;
        bool sendCommand(const QString &);

        bool set(const QString &, const QByteArray &);
        QByteArray get(const QString &);

    private :
        std::unique_ptr<redisContext> context_;
};

static const struct timeval REDIS_CONNECTION_TIMEOUT = { 2 }; // 2 seconds

#endif // REDISCLIENT_H