#ifndef IMAGELOADER_H
#define IMAGELOADER_H

class ImageLoader : public QObject, boost::noncopyable
{
    Q_OBJECT

    public :
        static ImageLoader & instance();

        Q_INVOKABLE QPixmap loadPixmap(const QUrl &);
        Q_INVOKABLE QIcon loadIcon(const QUrl &);

        // It seems QML does not resolve overloading correctly
        Q_INVOKABLE QPixmap loadPixmapFromData(const QByteArray &);
        Q_INVOKABLE QIcon loadIconFromData(const QByteArray &);

    private :
        ImageLoader();
};

Constant IMAGE_LOADER_OBJECT_NAME = "ImageLoader";

#endif // IMAGELOADER_H