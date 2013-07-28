#ifndef MIMEDATAENTRY_H
#define MIMEDATAENTRY_H

Constant PNG_FORMAT = "PNG";

class MimeDataEntry : public QMimeData
{
    Q_OBJECT

    public :
        MimeDataEntry();
        MimeDataEntry(const QMimeData *);

        QByteArray serialize() const;

        Q_INVOKABLE bool hasText () const { return QMimeData::hasText();  }
        Q_INVOKABLE bool hasImage() const { return QMimeData::hasImage(); }
        Q_INVOKABLE bool hasHtml () const { return QMimeData::hasHtml();  }
        Q_INVOKABLE bool hasColor() const { return QMimeData::hasColor(); }
        Q_INVOKABLE bool hasUrls () const { return QMimeData::hasUrls();  }
        Q_INVOKABLE bool hasFormat(const QString &) const;

        Q_INVOKABLE QString     text() const { return QMimeData::text(); }
        Q_INVOKABLE QString     html() const { return QMimeData::html(); }
        Q_INVOKABLE QList<QUrl> urls() const { return QMimeData::urls(); }

        Q_INVOKABLE QByteArray rawImageData(const QString & = PNG_FORMAT) const;

        Q_INVOKABLE QByteArray  data(const QString &) const;
        Q_INVOKABLE QVariantMap data()                const;

        Q_INVOKABLE void setText(const QString &);
        Q_INVOKABLE void setHtml(const QString &);
        Q_INVOKABLE void setUrls(const QList<QUrl> &);

        Q_INVOKABLE void setData(const QString &, const QByteArray &);
        Q_INVOKABLE void setData(const QVariantMap &);

    private :
        QDateTime timeStamp_;

        inline void init();
};

QDataStream & operator<<(QDataStream &, const MimeDataEntry &);
QDataStream & operator>>(QDataStream &, MimeDataEntry &);

#endif // MIMEDATAENTRY_H