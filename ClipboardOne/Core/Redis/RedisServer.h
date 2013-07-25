#ifndef REDISSERVER_H
#define REDISSERVER_H

class RedisClient;

class RedisServer : boost::noncopyable
{
    public :
        static RedisServer & instance();
        static bool command(const QString &);

    private :
        RedisServer();
        ~RedisServer();

        static void clean();

        QProcess process_;
        std::unique_ptr<RedisClient> master_;
};

#endif // REDISSERVER_H