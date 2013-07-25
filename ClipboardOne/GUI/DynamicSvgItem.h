#ifndef DYNAMICSVGITEM_H
#define DYNAMICSVGITEM_H

class DynamicSVGItem : public QGraphicsSvgItem
{
    Q_OBJECT

    public :
        DynamicSVGItem(const QString &);

        void changeColor(const QColor &);

    private :
        inline void walkNode(const QDomNode &);
        inline void processNode(const QDomNode &);

        QDomDocument svgXml_;
        QColor currentColor_;
        std::unique_ptr<QSvgRenderer> renderer_;
};

Constant COLOR_TO_STRING = [](const QColor & color) 
{  
    return QString("rgb(%1,%2,%3)").arg(color.red())
                                   .arg(color.green())
                                   .arg(color.blue()); 
};

Constant SVG_ELEMENT_NAME = "svg";
Constant FILL_ATTRIBUTE = "fill";

#endif // DYNAMICSVGITEM_H