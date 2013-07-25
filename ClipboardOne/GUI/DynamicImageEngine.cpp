#include "stdafx.h"
#include "DynamicImageEngine.h"

#include "Core/Settings.h"

DynamicImageEngine & DynamicImageEngine::instance()
{
    static DynamicImageEngine iconEngine;
    return iconEngine;
}

DynamicImageEngine::DynamicImageEngine() : QObject()
{
    setObjectName(DYNAMIC_IMAGE_ENGINE_OBJECT_NAME);
}

QColor DynamicImageEngine::maskColor()
{
    return instance().maskColor_;
}

void DynamicImageEngine::setMaskColor(const QColor & color)
{
    auto & self = instance();
    self.maskColor_ = color;
    Q_EMIT self.maskChanged(self.maskColor_);
    Settings::setValue("mask_color", color, "Ui");
}

QPixmap DynamicImageEngine::colored(const QString & fileName)
{
    QPixmap pixmap(fileName);
    QBitmap mask = pixmap.createMaskFromColor(Qt::black, Qt::MaskOutColor);

    QPainter painter(&pixmap);
    painter.setPen(instance().maskColor_);
    painter.drawPixmap(pixmap.rect(), mask, mask.rect());

    return pixmap;
}