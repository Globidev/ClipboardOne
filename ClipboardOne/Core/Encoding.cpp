#include "stdafx.h"
#include "Encoding.h"

Encoding & Encoding::instance()
{
    static Encoding encoding;
    return encoding;
}

Encoding::Encoding() : QObject()
{
    setObjectName(ENCODING_OBJECT_NAME);
}

QString Encoding::base64(const QByteArray & data)
{
    return data.toBase64();
}

QString Encoding::percentEncode(const QByteArray & data)
{
    return data.toPercentEncoding();
}