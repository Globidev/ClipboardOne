#include "stdafx.h"
#include "QMLEnvironment.h"

#include "QMLPlugin.h"
#include "QMLSettings.h"
#include "QMLClipboard.h"
#include "QMLUiTools.h"

#include "GUI/SystemTray.h"
#include "GUI/DynamicImageEngine.h"
#include "GUI/ImageLoader.h"

#include "Network/NetworkAccessManager.h"

#include "Core/ProcessManager.h"
#include "Core/Settings.h"

QMLEnvironment::QMLEnvironment() : QObject(),
    engine_(new QQmlEngine)
{
    QObject::connect(engine_.get(), &QQmlEngine::warnings, [](const QList<QQmlError> & warnings)
    {
        qDebug() << warnings;
    });

    qAddPostRoutine(clean);
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

void QMLEnvironment::addPlugin(const QUrl & qmlFileUrl)
{
    auto component = new QQmlComponent(instance().engine_.get());

    QObject::connect(component, &QQmlComponent::statusChanged, [component, qmlFileUrl]
    {
        if(component->isReady())
        {
            auto plugin = qobject_cast<QMLPlugin *>(component->create());
            if(!plugin) // failed to laod plugin most likely due to incorrect Plugin structure 
            {
                qDebug() << "Failed to create plugin";
                return;
            }
            initPlugin(plugin);
            instance().plugins_.push_back(
                std::make_pair(Component(component), Plugin(plugin))
            );
            Q_EMIT instance().pluginAdded(pluginCount() - 1);
            instance().addPluginToCache(qmlFileUrl);
        }

        if(component->isError())
            qDebug() << component->errors();
    });

    component->loadUrl(qmlFileUrl);
}

void QMLEnvironment::initPlugin(QMLPlugin * plugin)
{
    plugin->addContextProperty(&SystemTray::instance());
    plugin->addContextProperty(&ImageLoader::instance());
    plugin->addContextProperty(&ProcessManager::instance());
    plugin->addContextProperty(&NetworkAccessManager::instance());
    plugin->addContextProperty(&DynamicImageEngine::instance());
    plugin->addContextProperty(&QMLUiTools::instance());

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
    instance().engine_->trimComponentCache();
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