#ifndef NETWORKHTTPREPLY_H
#define NETWORKHTTPREPLY_H

class NetworkHTTPReply : public QObject
{
    Q_OBJECT

    public :
        // non explicit by design
        NetworkHTTPReply(QNetworkReply *, QObject * = nullptr);

        Q_INVOKABLE int status();

        Q_INVOKABLE QByteArray rawData();
        Q_INVOKABLE QJsonObject json();

        Q_SIGNAL void finished(int status);

    private :
        QNetworkReply * reply_;
        QByteArray data_;
};

#endif // NETWORKHTTPREPLY_H