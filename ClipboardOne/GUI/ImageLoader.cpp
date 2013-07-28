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
    return loadPixmapFromData(reply->rawData());
}

QIcon ImageLoader::loadIcon(const QUrl & url)
{
    return loadPixmap(url);
}

QPixmap ImageLoader::loadPixmapFromData(const QByteArray & data)
{
    QPixmap pixmap;
    pixmap.loadFromData(data);
    return pixmap;
}

QIcon ImageLoader::loadIconFromData(const QByteArray & data)
{
    return loadPixmapFromData(data);
}