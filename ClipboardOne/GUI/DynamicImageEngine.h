#ifndef DYNAMICICONENGINE_H
#define DYNAMICICONENGINE_H

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

        QColor maskColor_;
};

Constant DYNAMIC_IMAGE_ENGINE_OBJECT_NAME = "ImageEngine";

#endif // DYNAMICICONENGINE_H