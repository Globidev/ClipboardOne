#include "stdafx.h"
#include "QMLEnvironment.h"

#include "QMLPlugin.h"
#include "QMLSettings.h"
#include "QMLClipboard.h"
#include "QMLUiTools.h"

#include "GUI/SystemTray.h"
#include "GUI/DynamicImageEngine.h"
#include "GUI/ImageLoader.h"
#include "GUI/Logger/Logger.h"

#include "Network/NetworkAccessManager.h"

#include "Core/ProcessManager.h"
#include "Core/Settings.h"
#include "Core/Encoding.h"

QMLEnvironment::QMLEnvironment() : QObject(),
    engine_(new QQmlEngine)
{
    QObject::connect(engine_.get(), &QQmlEngine::warnings, [](const QList<QQmlError> & warnings)
    {
        for(auto & error : warnings)
            Logger::log(error.toString(), 
                        LogEntry::Type::Warning,
                        LogEntry::Scope::Plugin);
    });

    qAddPostRoutine(clean);

    addSingletonToContext <
        SystemTray,
        ImageLoader,
        ProcessManager,
        NetworkAccessManager,
        DynamicImageEngine,
        QMLUiTools,
        Encoding,
        Logger
    >();
}

void QMLEnvironment::clean()
{
    instance().engine_.reset();
    instance().plugins_.clear();
}

QMLEnvironment & QMLEnvironment::instance()
{
    static QMLEnvironment environment;
    return environment;
}

QQmlContext * QMLEnvironment::rootContext()
{
    return instance().engine_->rootContext();
}

void QMLEnvironment::addPlugin(const QUrl & qmlFileUrl)
{
    auto component = new QQmlComponent(instance().engine_.get());

    QObject::connect(component, &QQmlComponent::statusChanged, 
        [=](QQmlComponent::Status status)
    {
        switch(status)
        {
            case QQmlComponent::Ready : 
                instance().onComponentReady(component, qmlFileUrl);
                break;

            case QQmlComponent::Error :
                instance().onComponentError(component, qmlFileUrl);
                break;

            default : break;
        }
    });

    component->loadUrl(qmlFileUrl);
}

void QMLEnvironment::onComponentReady(QQmlComponent * component,
                                      const QUrl & url)
{
    auto plugin = qobject_cast<QMLPlugin *>(component->create());

    if(!plugin) // failed to laod plugin most likely due to incorrect Plugin structure 
        return onComponentError(component, url);
    
    plugins_.push_back(std::make_pair(Component(component), 
                                      Plugin(plugin)));

    initPlugin(plugin);
    addPluginToCache(url);

    Q_EMIT pluginAdded(pluginCount() - 1);
}

void QMLEnvironment::onComponentError(QQmlComponent * component,
                                      const QUrl & url)
{
    Logger::log("Failed to create plugin : " + component->errorString(), 
                LogEntry::Type::Error,
                LogEntry::Scope::Plugin);
    component->deleteLater();
    instance().engine_->clearComponentCache();
}

void QMLEnvironment::initPlugin(QMLPlugin * plugin)
{
    // Load shortcut settings
    if(plugin->clipboard())
    {
        auto shortcut = Settings::value<Shortcut>(plugin->name(), "shortcuts");
        plugin->clipboard()->setShortcut(shortcut);
    }
}

void QMLEnvironment::removePlugin(QMLPlugin * plugin, bool removeCacheEntries)
{
    auto & self = instance();
    self.removePluginFromCache(plugin->creationContext()->baseUrl());
    plugin->cleanUp(removeCacheEntries);

    for(size_t i = 0; i < self.plugins_.size(); ++ i)
        if(self.plugins_[i].second.get() == plugin)
        {
            self.plugins_.erase(self.plugins_.begin() + i);
            Q_EMIT self.pluginRemoved(i);
            break;
        }
    
    // Clearing cache for eventual later updates
    instance().engine_->clearComponentCache();
}
int QMLEnvironment::pluginCount()
{
    return instance().plugins_.size();
}

QMLPlugin * QMLEnvironment::plugin(int id)
{
    return instance().plugins_.at(id).second.get();
}

void QMLEnvironment::apply(const PluginAction & action)
{
    for(auto & pluginData : instance().plugins_)
        action(pluginData.second.get());
}

void QMLEnvironment::addPluginToCache(const QUrl & url)
{
    auto pluginUrls = Settings::value<QStringList>("urls", "Plug-ins");
    if(!pluginUrls.contains(url.toString()))
        pluginUrls.append(url.toString());
    Settings::setValue("urls", pluginUrls, "Plug-ins");
}

void QMLEnvironment::removePluginFromCache(const QUrl & url)
{
    auto pluginUrls = Settings::value<QStringList>("urls", "Plug-ins");
    pluginUrls.removeOne(url.toString());
    Settings::setValue("urls", pluginUrls, "Plug-ins");
}