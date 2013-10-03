#ifndef QMLPLUGIN_H
#define QMLPLUGIN_H

#include "QMLBaseComponent.h"

class QMLUi;
class QMLClipboard;
class QMLSettings;

class QMLPlugin : public QQmlComponent, public QMLBaseComponent<QMLPlugin>
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString version READ version WRITE setVersion)
    Q_PROPERTY(QString author READ author WRITE setAuthor)
    Q_PROPERTY(QUrl icon READ icon WRITE setIcon)

    Q_PROPERTY(bool activable READ activable WRITE setActivable NOTIFY activableChanged)
    Q_PROPERTY(bool configurable READ configurable WRITE setConfigurable NOTIFY configurableChanged)

    Q_PROPERTY(QQmlListProperty<QMLUi> uis READ uis); // MOC does not support typedefs apparently
    Q_PROPERTY(QMLClipboard * clipboard READ clipboard WRITE setClipboard)
    Q_PROPERTY(QMLSettings * settings READ settings WRITE setSettings)

    Q_PROPERTY(QIcon loadedIcon READ loadedIcon)

    Q_CLASSINFO("DefaultProperty", "uis")

    typedef QQmlListProperty<QMLUi> Uis;

    public :
        QMLPlugin();

        QUrl url() const;
        void setUrl(const QUrl &);

        QString name() const;
        void setName(const QString &);

        QString version() const;
        void setVersion(const QString &);

        QString author() const;
        void setAuthor(const QString &);

        QUrl icon() const;
        void setIcon(const QUrl &);

        bool activable() const;
        void setActivable(bool);
        Q_SIGNAL void activableChanged(bool);

        bool configurable() const;
        void setConfigurable(bool);
        Q_SIGNAL void configurableChanged(bool);

        Uis uis();

        QMLClipboard * clipboard() const;
        void setClipboard(QMLClipboard *);

        QMLSettings * settings() const;
        void setSettings(QMLSettings *);

        QPixmap loadedIcon();

        void setEnabled(bool);

        Q_SIGNAL void configure();

        void cleanUp(bool);

    private :
        static inline QMLPlugin * self(Uis *); // convenience function for deducing 'this' from a list property

        QUrl url_;

        QString name_;
        QString version_;
        QString author_;

        bool activable_;
        bool configurable_;

        QUrl icon_;
        std::unique_ptr<QPixmap> loadedIcon_;

        std::vector<std::unique_ptr<QMLUi>> uis_;
        std::unique_ptr<QMLClipboard> clipboard_;
        std::unique_ptr<QMLSettings> settings_;
};

#endif // QMLPLUGIN_H