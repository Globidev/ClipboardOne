#include "stdafx.h"
#include "QMLPlugin.h"

#include "QMLUi.h"
#include "QMLClipboard.h"
#include "QMLSettings.h"

#include "Core/Settings.h"

#include "GUI/SystemTray.h"

#include "Network/NetworkAccessManager.h"
#include "Network/NetworkHTTPReply.h"

const char * QMLPlugin::package = "GlobiPlugin";
const int QMLPlugin::majorVersion = 1;
const int QMLPlugin::minorVersion = 0;
const char * QMLPlugin::qmlName = "Plugin";

QMLPlugin::QMLPlugin() : QQmlComponent(),
    author_("Anonymous"),
    activable_(true),
    configurable_(true),
    loadedIcon_(new QPixmap(":/PluginEditor/Question"))
{
    
}

QUrl QMLPlugin::url() const
{
    return url_;
}

void QMLPlugin::setUrl(const QUrl & url)
{
    url_ = url;
}

QString QMLPlugin::name() const
{
    return name_;
}

void QMLPlugin::setName(const QString & name)
{
    name_ = name;
}

QString QMLPlugin::version() const
{
    return version_;
}

void QMLPlugin::setVersion(const QString & version)
{
    version_ = version;
}

QString QMLPlugin::author() const
{
    return author_;
}

void QMLPlugin::setAuthor(const QString & author)
{
    author_ = author;
}

QUrl QMLPlugin::icon() const
{
    return icon_;
}

void QMLPlugin::setIcon(const QUrl & icon)
{
    icon_ = icon;

    std::unique_ptr<NetworkHTTPReply> reply(NetworkAccessManager::get(icon_.toString(), QJsonObject(), false));
    loadedIcon_.reset(new QPixmap);
    loadedIcon_->loadFromData(reply->rawData());
}

bool QMLPlugin::activable() const
{
    return activable_;
}

void QMLPlugin::setActivable(bool activable)
{
    activable_ = activable;
    if(clipboard_) clipboard_->setActivable(activable);
    Q_EMIT activableChanged(activable);
}

bool QMLPlugin::configurable() const
{
    return configurable_;
}

void QMLPlugin::setConfigurable(bool configurable)
{
    configurable_ = configurable;
    Q_EMIT configurableChanged(configurable);
}

QQmlListProperty<QMLUi> QMLPlugin::uis()
{
    auto appendUi = [](Uis * uis, QMLUi *value) { self(uis)->uis_.emplace_back(value);    };
    auto countUi  = [](Uis * uis) -> int        { return self(uis)->uis_.size();          };
    auto atUi     = [](Uis * uis, int index)    { return self(uis)->uis_.at(index).get(); };
    auto clearUi  = [](Uis * uis)               { self(uis)->uis_.clear();                };

    return Uis(this, nullptr, appendUi, countUi, atUi, clearUi);
}

QMLClipboard * QMLPlugin::clipboard() const
{
    return clipboard_.get();
}

void QMLPlugin::setClipboard(QMLClipboard * clipboard)
{
    clipboard_.reset(clipboard);
}

QMLSettings * QMLPlugin::settings() const
{
    return settings_.get();
}

void QMLPlugin::setSettings(QMLSettings * settings)
{
    settings_.reset(settings);
}

QPixmap QMLPlugin::loadedIcon()
{
    return *loadedIcon_;
}

void QMLPlugin::setEnabled(bool enabled)
{
    if(clipboard_) clipboard_->setEnabled(enabled);
}

void QMLPlugin::cleanUp(bool removeCacheEntries)
{
    if(removeCacheEntries)
    {
        if(settings_) settings_->removeAllKeys();
        Settings::removeKey(QString("shortcuts/%1").arg(name()));
    }
}

QMLPlugin * QMLPlugin::self(Uis * uis)
{
    return qobject_cast<QMLPlugin *>(uis->object);
}