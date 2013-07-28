#include "stdafx.h"
#include "DynamicImageEngine.h"

#include "Core/Settings.h"

MonochromeImage::MonochromeImage(const QString & fileName) :
    pixmap(new QPixmap(fileName)),
    mask(new QBitmap(pixmap->createMaskFromColor(Qt::black, Qt::MaskOutColor))),
    rect(pixmap->rect())
{
}

void MonochromeImage::setMaskColor(const QColor & color)
{
    painter.begin(pixmap.get());
    painter.setPen(color);
    painter.drawPixmap(rect, *mask, rect);
    painter.end();
}

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

MonochromeImage * DynamicImageEngine::image(const QString & fileName)
{
    auto found = images_.find(fileName);
    
    if(found == images_.end())
        found = images_.emplace(fileName, 
            std::unique_ptr<MonochromeImage>(new MonochromeImage(fileName))).first;

    return found->second.get();
}

QPixmap DynamicImageEngine::colored(const QString & fileName)
{
    auto imageData = instance().image(fileName);
    imageData->setMaskColor(instance().maskColor_);
    return *imageData->pixmap;
}