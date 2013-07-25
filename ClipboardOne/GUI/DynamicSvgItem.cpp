#include "stdafx.h"
#include "DynamicSvgItem.h"

#include "DynamicImageEngine.h"

DynamicSVGItem::DynamicSVGItem(const QString & fileName) :
    QGraphicsSvgItem(),
    renderer_(new QSvgRenderer)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    svgXml_.setContent(&file);

    changeColor(DynamicImageEngine::maskColor());

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged,
                     this, &DynamicSVGItem::changeColor);
}

void DynamicSVGItem::changeColor(const QColor & color)
{
    currentColor_ = color;
    walkNode(svgXml_);

    renderer_->load(svgXml_.toByteArray());
    setSharedRenderer(renderer_.get()); // force refresh
}

void DynamicSVGItem::walkNode(const QDomNode & node)
{
    auto childList = node.childNodes();
    for(int i(0); i < childList.count(); ++ i)
    {
        processNode(childList.at(i));
        walkNode(childList.at(i));
    }
}

void DynamicSVGItem::processNode(const QDomNode & node)
{
    if(node.nodeName() == SVG_ELEMENT_NAME)
        node.toElement().setAttribute(FILL_ATTRIBUTE, 
                                      COLOR_TO_STRING(currentColor_));
    else if(node.toElement().hasAttribute(FILL_ATTRIBUTE))
        node.toElement().removeAttribute(FILL_ATTRIBUTE);
}