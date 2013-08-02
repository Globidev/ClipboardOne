#include "stdafx.h"
#include "NetworkHTTPRequest.h"

NetworkHTTPRequest::NetworkHTTPRequest(const QUrl & url,
                                       const QJsonObject & headers) : 
    QObject(), QNetworkRequest(),
    multiPart_(new QHttpMultiPart)
{
    setUrl(url);
    setHeaders(headers);
}

QHttpMultiPart * NetworkHTTPRequest::multiPart() const
{
    return multiPart_.get();
}

QJsonObject NetworkHTTPRequest::headers() const
{
    QJsonObject headers;
    for(const auto & headerName : rawHeaderList())
        headers.insert(headerName, QString(rawHeader(headerName)));
    return headers;
}

void NetworkHTTPRequest::setUrl(const QUrl & url)
{
    QNetworkRequest::setUrl(url);
}

void NetworkHTTPRequest::setHeaders(const QJsonObject & headers)
{
    for(QJsonObject::ConstIterator it(headers.begin()); it != headers.end(); ++ it)
        setRawHeader(it.key().toUtf8(), it.value().toString().toUtf8());
}

void NetworkHTTPRequest::addPart(const QJsonObject & headers, 
                                 const QByteArray & data)
{
    QHttpPart part;
    part.setBody(data);

    for(QJsonObject::ConstIterator it(headers.begin()); it != headers.end(); ++ it)
        part.setRawHeader(it.key().toUtf8(), it.value().toString().toUtf8());

    multiPart_->append(part);
}

void NetworkHTTPRequest::setContentType(int type)
{
    qDebug() << ((QHttpMultiPart::ContentType)type == QHttpMultiPart::FormDataType);
    multiPart_->setContentType((QHttpMultiPart::ContentType)type);
}