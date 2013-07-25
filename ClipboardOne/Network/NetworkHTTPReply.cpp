#include "stdafx.h"
#include "NetworkHTTPReply.h"

NetworkHTTPReply::NetworkHTTPReply(QNetworkReply * reply,
                                   QObject * parent) : QObject(parent),
    reply_(reply)
{
    reply_->setParent(this); // Taking ownership of the reply makes more sense
                             // from a conceptual point of view

    auto onFinished = [this]
    {
        data_ = reply_->readAll();
        Q_EMIT finished(status());
    };

    if(reply_->isFinished()) onFinished();
    else QObject::connect(reply_, &QNetworkReply::finished, onFinished);
}

int NetworkHTTPReply::status()
{
    return reply_->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
}

QByteArray NetworkHTTPReply::rawData()
{
    return data_;
}

QJsonObject NetworkHTTPReply::json()
{
    return QJsonDocument::fromJson(data_).object();
}