#ifndef NETWORKACCESSMANAGER_H
#define NETWORKACCESSMANAGER_H

class NetworkHTTPRequest;
class NetworkHTTPReply;
class LocalHTTPServer;

class NetworkAccessManager : public QNetworkAccessManager, boost::noncopyable
{
    Q_OBJECT

    typedef QNetworkReply * (QNetworkAccessManager::*BytePayloadRequest)
                            (const QNetworkRequest &, const QByteArray &);
    typedef QNetworkReply * (QNetworkAccessManager::*MultiPartRequest)
                            (const QNetworkRequest &, QHttpMultiPart *);

    public :
        static NetworkAccessManager & instance();

        static Q_INVOKABLE void setTimeout(size_t);

        static Q_INVOKABLE LocalHTTPServer * newLocalServer(quint16);
        static Q_INVOKABLE NetworkHTTPRequest *
        request(const QUrl & = QUrl(), const QJsonObject & = QJsonObject());

        // Convenient functions
        Q_INVOKABLE static NetworkHTTPReply *
        get(const QUrl &, const QJsonObject & = QJsonObject(), bool = true);
        Q_INVOKABLE static NetworkHTTPReply *
        head(const QUrl &, const QJsonObject & = QJsonObject(), bool = true);
        Q_INVOKABLE static NetworkHTTPReply *
        del(const QUrl &, const QJsonObject & = QJsonObject(), bool = true);
        Q_INVOKABLE static NetworkHTTPReply *
        post(const QUrl &, const QJsonObject & = QJsonObject(), 
             const QJsonObject & = QJsonObject(), bool = true);
        Q_INVOKABLE static NetworkHTTPReply *
        put(const QUrl &, const QJsonObject & = QJsonObject(), 
            const QByteArray & = QByteArray(), bool = true);

        Q_INVOKABLE static NetworkHTTPReply *
        getRequest(NetworkHTTPRequest *, bool = true);
        Q_INVOKABLE static NetworkHTTPReply *
        headRequest(NetworkHTTPRequest *, bool = true);
        Q_INVOKABLE static NetworkHTTPReply *
        delRequest(NetworkHTTPRequest *, bool = true);
        Q_INVOKABLE static NetworkHTTPReply *
        postRequest(NetworkHTTPRequest *, bool = true);
        Q_INVOKABLE static NetworkHTTPReply *
        putRequest(NetworkHTTPRequest *, bool = true);

        Q_INVOKABLE static QByteArray queryString(const QJsonObject &);
        Q_INVOKABLE static QString url(QUrl, const QJsonObject &);

    private :
        NetworkAccessManager();

        // Proxy sender
        template <class ... RequestParameters>
        NetworkHTTPReply * 
        sendRequest(QNetworkReply * (QNetworkAccessManager::* senderFunction)(RequestParameters ...),
                    const RequestParameters & ... requestParameters,
                    bool asynchronous)
        {
            auto reply = asynchronous ?
                         (this->*senderFunction)(requestParameters ...) :
                         synchronousCall(httpTimeout_, &QNetworkReply::finished,
                                         senderFunction, this, requestParameters ...);
            return new NetworkHTTPReply(reply, this); // swapping ownerships, memory is managed
        }

        static inline QNetworkRequest makeRequest(const QUrl &, const QJsonObject &); 
        static QUrlQuery makeQuery(const QJsonObject &);

        size_t httpTimeout_;
};

Constant NETWORK_ACCESS_MANAGER_OBJECT_NAME = "HTTP";
Constant DEFAULT_HTTP_TIMEOUT = 5000;

#endif // NETWORKACCESSMANAGER_H