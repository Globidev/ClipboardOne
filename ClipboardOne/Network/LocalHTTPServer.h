#ifndef LOCALHTTPSERVER_H
#define LOCALHTTPSERVER_H

class LocalHTTPServer : public QTcpServer
{
    Q_OBJECT

    public :
        LocalHTTPServer(quint16, QObject * = nullptr);

        Q_INVOKABLE bool isListening() const { return QTcpServer::isListening(); }

        Q_SIGNAL void newQuery(const QVariantMap &);

    protected :
        virtual void incomingConnection(qintptr);

    private :
        void readClient(QTcpSocket *);
        inline void respondToClient(QTcpSocket *);
};

Constant REQUEST_REG_EXP = QRegExp("[ \r\n][ \r\n]*");
Constant GET_METHOD = "GET";

#endif // LOCALHTTPSERVER_H