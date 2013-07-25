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
                                  jsonToQueryString(payload),
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

QNetworkRequest NetworkAccessManager::makeRequest(const QUrl & url, 
                                                  const QJsonObject & headers)
{
    QNetworkRequest request(url);

    for(QJsonObject::const_iterator it(headers.begin()); it != headers.end(); ++ it)
        request.setRawHeader(it.key().toUtf8(), it.value().toString().toUtf8());

    return request;
}

QByteArray NetworkAccessManager::jsonToQueryString(const QJsonObject & payload)
{
    QUrlQuery query;
    for(QJsonObject::const_iterator it(payload.begin()); it != payload.end(); ++ it)
        query.addQueryItem(it.key(), it.value().toString());

    return query.toString(QUrl::FullyEncoded).toUtf8();
}