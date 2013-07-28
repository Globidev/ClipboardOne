#include "stdafx.h"
#include "Settings.h"

Settings & Settings::instance()
{
    static Settings settings;
    return settings;
}

Settings::Settings() :
    settings_(new QSettings(QSettings::IniFormat,
                            QSettings::UserScope,
                            SETTINGS_DIR, APPLICATION_NAME))
{
}

void Settings::setValue(const QString & key, const QVariant & value)
{
    instance().settings_->setValue(key, value);
}

void Settings::setValue(const QString & key, const QVariant & value, const QString & scopeName)
{
    Scope scope(scopeName);
    setValue(key, value);
}

void Settings::removeKey(const QString & key)
{
    instance().settings_->remove(key);
}

QStringList Settings::allKeys()
{
    return instance().settings_->allKeys();
}

QString Settings::directory()
{
    QDir dir(instance().settings_->fileName());
    dir.cdUp();
    return QDir::toNativeSeparators(dir.path());
}

Settings::Scope::Scope(const QString & scopeName)
{
    Settings::instance().settings_->beginGroup(scopeName);
}

Settings::Scope::~Scope()
{
    Settings::instance().settings_->endGroup();
}