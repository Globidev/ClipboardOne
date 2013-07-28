#ifndef DYNAMICIMAGEENGINE_H
#define DYNAMICIMAGEENGINE_H

struct MonochromeImage
{
    MonochromeImage(const QString &);

    void setMaskColor(const QColor &);

    QPainter painter;

    std::unique_ptr<QPixmap> pixmap;
    std::unique_ptr<QBitmap> mask;
    QRect rect;
};

class DynamicImageEngine : public QObject, boost::noncopyable
{
    Q_OBJECT

    public :
        static DynamicImageEngine & instance();

        static QColor maskColor();
        Q_INVOKABLE static void setMaskColor(const QColor &);
        Q_SIGNAL void maskChanged(const QColor &);

        static QPixmap colored(const QString &);

    private :
        DynamicImageEngine();

        MonochromeImage * image(const QString &);

        QColor maskColor_;
        std::map<QString, std::unique_ptr<MonochromeImage>> images_;
};

Constant DYNAMIC_IMAGE_ENGINE_OBJECT_NAME = "ImageEngine";

#endif // DYNAMICIMAGEENGINE_H