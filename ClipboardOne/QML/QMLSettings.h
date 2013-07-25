#ifndef QMLSETTINGS_H
#define QMLSETTINGS_H

#include "QMLBaseComponent.h"

class QMLSettings : public QQmlComponent, public QMLBaseComponent<QMLSettings>
{
    Q_OBJECT

    Q_PROPERTY(QString prefix READ prefix WRITE setPrefix)

    public :
        QMLSettings();

        QString prefix() const;
        void setPrefix(const QString &);

        Q_INVOKABLE void setValue(const QString &, const QVariant &);
        Q_INVOKABLE QVariant value(const QString &, const QVariant & = QVariant());

        void removeAllKeys();

    private :
        QString prefix_;
};

Constant QML_SETTINGS_SCOPE = [](const QString & prefix) 
{ return QString("Plugin_%1").arg(prefix); };

#endif // QMLSETTINGS_H