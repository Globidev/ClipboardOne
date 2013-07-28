#ifndef ENCODING_H
#define ENCODING_H

class Encoding : public QObject
{
    Q_OBJECT

    public :
        static Encoding & instance();

        Q_INVOKABLE QString base64(const QByteArray &);
        Q_INVOKABLE QString percentEncode(const QByteArray &);

    private :
        Encoding();
};

Constant ENCODING_OBJECT_NAME = "Encoding";

#endif // ENCODING_H