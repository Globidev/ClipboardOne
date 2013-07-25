#ifndef IMAGELOADER_H
#define IMAGELOADER_H

class ImageLoader : public QObject, boost::noncopyable
{
    Q_OBJECT

    public :
        static ImageLoader & instance();

        Q_INVOKABLE QPixmap loadPixmap(const QUrl &);
        Q_INVOKABLE QIcon loadIcon(const QUrl &);

        Q_INVOKABLE QPixmap loadPixmap(const QByteArray &);
        Q_INVOKABLE QIcon loadIcon(const QByteArray &);

    private :
        ImageLoader();
};

Constant IMAGE_LOADER_OBJECT_NAME = "ImageLoader";

#endif // IMAGELOADER_H