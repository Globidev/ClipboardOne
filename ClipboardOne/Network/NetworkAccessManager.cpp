#include "stdafx.h"
#include "NetworkAccessManager.h"

#include "NetworkHTTPReply.h"
#include "LocalHTTPServer.h"

NetworkAccessManager & NetworkAccessManager::instance()
{
    static NetworkAccessManager networkAccessManager;
    return networkAccessManager;
}

NetworkAccessManager::NetworkAccessManager() : QNetworkAccessManager(),
    httpTimeout_(DEFAULT_HTTP_TIMEOUT)
{
    setObjectName(NETWORK_ACCESS_MANAGER_OBJECT_NAME);
}

void NetworkAccessManager::setTimeout(size_t timeout)
{
    instance().httpTimeout_ = timeout;
}

LocalHTTPServer * NetworkAccessManager::newLocalServer(quint16 port)
{
    return new LocalHTTPServer(port, &instance());
}

NetworkHTTPReply * NetworkAccessManager::get(const QUrl & url,
                                             const QJsonObject & headers,
                                             bool asynchronous)
{
    return instance().sendRequest(&QNetworkAccessManager::get,
                                  makeRequest(url, headers),
                                  asynchronous);
}

NetworkHTTPReply * NetworkAccessManager::head(const QUrl & url,
                                              const QJsonObject & headers,
                                              bool asynchronous)
{
    return instance().sendRequest(&QNetworkAccessManager::head,
                                  makeRequest(url, headers),
                                  asynchronous);
}

NetworkHTTPReply * NetworkAccessManager::del(const QUrl & url,
                                             const QJsonObject & headers,
                                             bool asynchronous)
{
    return instance().sendRequest(&QNetworkAccessManager::deleteResource,
                                  makeRequest(url, headers),
                                  asynchronous);
}

NetworkHTTPReply * NetworkAccessManager::post(const QUrl & url,
                                              const QJsonObject & headers,
                                              const QJsonObject & payload,
                                              bool asynchronous)
{
    return instance().sendRequest(static_cast<BytePayloadRequest>(&QNetworkAccessManager::post),
                                  makeRequest(url, headers),
                                  queryString(payload),
                                  asynchronous);
}

NetworkHTTPReply * NetworkAccessManager::put(const QUrl & url,
                                             const QJsonObject & headers,
                                             const QByteArray & payload,
                                             bool asynchronous)
{
    return instance().sendRequest(static_cast<BytePayloadRequest>(&QNetworkAccessManager::put),
                                  makeRequest(url, headers), 
                                  payload,
                                  asynchronous);
}

QByteArray NetworkAccessManager::queryString(const QJsonObject & dict)
{
    QUrlQuery query = makeQuery(dict);
    return query.toString(QUrl::FullyEncoded).toUtf8();
}

QString NetworkAccessManager::url(QUrl url, const QJsonObject & dict)
{
    url.setQuery(makeQuery(dict));
    return url.toString(QUrl::FullyEncoded);
}

QUrlQuery NetworkAccessManager::makeQuery(const QJsonObject & dict)
{
    QUrlQuery query;

    for(QJsonObject::ConstIterator it(dict.begin()); it != dict.end(); ++ it)
        query.addQueryItem(it.key(), it.value().toString());

    return query;
}

QNetworkRequest NetworkAccessManager::makeRequest(const QUrl & url, 
                                                  const QJsonObject & headers)
{
    QNetworkRequest request(url);

    for(QJsonObject::const_iterator it(headers.begin()); it != headers.end(); ++ it)
        request.setRawHeader(it.key().toUtf8(), it.value().toString().toUtf8());

    return request;
}