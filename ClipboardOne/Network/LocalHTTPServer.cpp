#include "stdafx.h"
#include "LocalHTTPServer.h"

LocalHTTPServer::LocalHTTPServer(quint16 port, QObject * parent) : QTcpServer(parent)
{
    listen(QHostAddress::LocalHost, port);
}

void LocalHTTPServer::incomingConnection(qintptr descriptor)
{
    auto client = new QTcpSocket(this);

    QObject::connect(client, &QTcpSocket::readyRead,
        [client, this] { readClient(client); });
    QObject::connect(client, &QTcpSocket::disconnected, 
                     client, &QObject::deleteLater);

    client->setSocketDescriptor(descriptor);
}

void LocalHTTPServer::readClient(QTcpSocket * socket)
{
    if(socket->canReadLine())
    {
        QString request = socket->readLine();
        QStringList tokens = request.split(REQUEST_REG_EXP);

        if(tokens.size() >= 2 && tokens[0] == GET_METHOD)
        {
            QString queryString = QUrl(tokens[1]).query();
            if(!queryString.isEmpty())
            {
                QUrlQuery query(queryString);
                Q_EMIT newQuery(pairListToMap(query.queryItems()));
            }
            respondToClient(socket);
        }
    }
}

void LocalHTTPServer::respondToClient(QTcpSocket * socket)
{
    QTextStream stream(socket);
    stream << "HTTP/1.0 200 Ok\r\n";
    socket->close();
}