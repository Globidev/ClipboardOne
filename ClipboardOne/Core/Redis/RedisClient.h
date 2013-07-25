#ifndef REDISCLIENT_H
#define REDISCLIENT_H

class RedisClient : boost::noncopyable
{
    public :
        RedisClient(const char * = LOCALHOST_IP, int = REDIS_DEFAULT_PORT);
        ~RedisClient();

        bool connected() const;
        bool sendCommand(const QString &);

        bool set(const QString &, const QByteArray &);
        QByteArray get(const QString &);

    private :
        redisContext * context_;
};

#endif // REDISCLIENT_H