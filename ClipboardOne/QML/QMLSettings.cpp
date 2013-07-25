#include "stdafx.h"
#include "QMLSettings.h"

#include "Core/Settings.h"

const char * QMLSettings::package = "GlobiPlugin";
const int QMLSettings::majorVersion = 1;
const int QMLSettings::minorVersion = 0;
const char * QMLSettings::qmlName = "Settings";

QMLSettings::QMLSettings() : QQmlComponent()
{

}

QString QMLSettings::prefix() const
{
    return prefix_;
}

void QMLSettings::setPrefix(const QString & prefix)
{
    prefix_ = prefix;
}

void QMLSettings::setValue(const QString & key, const QVariant & value)
{
    Settings::setValue(key, value, QML_SETTINGS_SCOPE(prefix_));
}

QVariant QMLSettings::value(const QString & key, const QVariant & defaultValue)
{
    return Settings::value<QVariant>(key, QML_SETTINGS_SCOPE(prefix_), defaultValue);
}

void QMLSettings::removeAllKeys()
{
    Settings::Scope scope(QML_SETTINGS_SCOPE(prefix_));
    for(const QString & key : Settings::allKeys())
        Settings::removeKey(key);
}