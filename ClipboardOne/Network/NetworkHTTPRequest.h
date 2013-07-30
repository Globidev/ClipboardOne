#ifndef NETWORKHTTPREQUEST_H
#define NETWORKHTTPREQUEST_H

class NetworkHTTPRequest : public QObject, public QNetworkRequest
{
    Q_OBJECT

    public :
        Q_INVOKABLE NetworkHTTPRequest(const QUrl & = QUrl(), 
                                       const QJsonObject & = QJsonObject());

        QHttpMultiPart * multiPart() const;
        QJsonObject headers() const;

        Q_INVOKABLE void setUrl(const QUrl &);
        Q_INVOKABLE void setHeaders(const QJsonObject &);
        Q_INVOKABLE void addPart(const QJsonObject &, const QByteArray &);
        Q_INVOKABLE void setContentType(QHttpMultiPart::ContentType);

    private :
        std::unique_ptr<QHttpMultiPart> multiPart_;
};

#endif // NETWORKHTTPREQUEST_H