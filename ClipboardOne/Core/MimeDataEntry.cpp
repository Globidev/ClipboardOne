#include "stdafx.h"
#include "MimeDataEntry.h"

MimeDataEntry::MimeDataEntry() : QMimeData()
{
    init();
}

MimeDataEntry::MimeDataEntry(const QMimeData * mimeData) : QMimeData()
{
    init();
    bool hasImage = false;

    for(QString & format : mimeData->formats())
    {
        if(format.startsWith(IMAGE_MIME_TYPE))
        {
            hasImage = true;
            continue;
        }

        QByteArray data = mimeData->data(format);
        // Checking for custom MIME types
        if(format.startsWith(CUSTOM_MIME_TYPE))
        {
            // Retrieving true format name
            int indexBegin = format.indexOf('"') + 1;
            int indexEnd = format.indexOf('"', indexBegin);
            format = format.mid(indexBegin, indexEnd - indexBegin);
        }
        setData(format, data);
    }

    if(hasImage)
        setImageData(mimeData->imageData());
}

QByteArray MimeDataEntry::serialize() const
{
    QByteArray serialized;
    QDataStream stream(&serialized, QIODevice::WriteOnly);
    stream << *this;
    return serialized;
}

void MimeDataEntry::init()
{
    timeStamp_ = QDateTime::currentDateTime();
}

QByteArray MimeDataEntry::rawImageData(const QString & format) const
{
    QByteArray data;
    QBuffer dataBuffer(&data);
    dataBuffer.open(QIODevice::WriteOnly);
    auto imgData = imageData().value<QImage>();
    imgData.save(&dataBuffer, format.toLocal8Bit().constData());
    return data;
}

QByteArray MimeDataEntry::data(const QString & mimeType) const
{
    return QMimeData::data(mimeType);
}

QVariantMap MimeDataEntry::data() const
{
    QVariantMap dataMap;
    for(const QString & mimeType : formats())
        dataMap.insert(mimeType, data(mimeType));
    return dataMap;
}

void MimeDataEntry::setData(const QString & mimeType, 
                            const QByteArray & value)
{
    QMimeData::setData(mimeType, value);
}

void MimeDataEntry::setData(const QVariantMap & dataMap)
{
    for(QVariantMap::ConstIterator it(dataMap.constBegin()); it != dataMap.constEnd(); ++ it)
        setData(it.key(), it.value().toByteArray());
}

QDataStream & operator<<(QDataStream & stream, const MimeDataEntry & mimeDataEntry)
{
    QList<QPair<QString, QByteArray>> data;
    bool hasImage = false;

    for(QString & format : mimeDataEntry.formats())
    {
        if(format.startsWith(IMAGE_MIME_TYPE))
        {
            hasImage = true;
            continue;
        }

        QByteArray formatData = mimeDataEntry.data(format);
        data << qMakePair(format, formatData);
    }

    stream << data << hasImage;
    if(hasImage) stream << mimeDataEntry.imageData();
    return stream;
}

QDataStream & operator>>(QDataStream & stream, MimeDataEntry & mimeDataEntry)
{
    QList<QPair<QString, QByteArray>> data;
    bool hasImage;

    stream >> data >> hasImage;
    for(auto & item : data)
        mimeDataEntry.setData(item.first, item.second);

    if(hasImage)
    {
        QVariant imageData;
        stream >> imageData;
        mimeDataEntry.setImageData(imageData);
    }

    return stream;
}