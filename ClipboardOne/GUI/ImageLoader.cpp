#include "stdafx.h"
#include "ImageLoader.h"

#include "Network/NetworkAccessManager.h"
#include "Network/NetworkHTTPReply.h"

ImageLoader & ImageLoader::instance()
{
    static ImageLoader imageLoader;
    return imageLoader;
}

ImageLoader::ImageLoader() : QObject()
{
    setObjectName(IMAGE_LOADER_OBJECT_NAME);
}

QPixmap ImageLoader::loadPixmap(const QUrl & url)
{
    auto reply = NetworkAccessManager::get(url, QJsonObject(), false);
    return loadPixmap(reply->rawData());
}

QIcon ImageLoader::loadIcon(const QUrl & url)
{
    return loadPixmap(url);
}

QPixmap ImageLoader::loadPixmap(const QByteArray & data)
{
    QPixmap pixmap;
    pixmap.loadFromData(data);
    return pixmap;
}

QIcon ImageLoader::loadIcon(const QByteArray & data)
{
    return loadPixmap(data);
}