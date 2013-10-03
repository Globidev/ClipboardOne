#include "stdafx.h"
#include "PluginActionWidget.h"

#include "GUI/Dialogs/RemovePluginDialog.h"
#include "GUI/DynamicImageEngine.h"

#include "QML/QMLPlugin.h"
#include "QML/QMLEnvironment.h"

PluginActionWidget::PluginActionWidget(QMLPlugin * plugin, 
                                       QWidget * parent) : QWidget(parent),
    ui_(new Ui::UiPluginActionWidget),
    plugin_(plugin),
    enabled_(true)
{
    ui_->setupUi(this);

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged, 
                     this, &PluginActionWidget::updateIcons,
                     Qt::QueuedConnection);
    updateIcons();

    QObject::connect(ui_->remove, &QToolButton::clicked, 
                     this, &PluginActionWidget::onRemovePlugin);
    QObject::connect(ui_->enable, &QToolButton::clicked,
                     this, &PluginActionWidget::onEnablePlugin);
    QObject::connect(ui_->configure, &QToolButton::clicked,
                     this, &PluginActionWidget::onConfigurePlugin);
    QObject::connect(ui_->reload, &QToolButton::clicked,
                     this, &PluginActionWidget::onReloadPlugin);

    QObject::connect(plugin, &QMLPlugin::configurableChanged,
                     this, &PluginActionWidget::onConfigurableChanged);
    onConfigurableChanged(plugin->configurable());
}

void PluginActionWidget::enablePlugin(bool enabled)
{
    ui_->enable->setIcon(enabled ? onIcon_ : offIcon_);
    plugin_->setEnabled(enabled);
}

void PluginActionWidget::updateIcons()
{
    ui_->remove->setIcon(DynamicImageEngine::colored(PLUGIN_ACTION_REMOVE_ICON));
    ui_->configure->setIcon(DynamicImageEngine::colored(PLUGIN_ACTION_CONFIGURE_ICON));
    ui_->reload->setIcon(DynamicImageEngine::colored(PLUGIN_ACTION_RELOAD_ICON));
    onIcon_ = DynamicImageEngine::colored(PLUGIN_ACTION_ENABLED_ICON);
    offIcon_ = DynamicImageEngine::colored(PLUGIN_ACTION_DISABLED_ICON);
    enablePlugin(enabled_);
}

void PluginActionWidget::onConfigurableChanged(bool configurable)
{
    ui_->configure->setVisible(configurable);
}

void PluginActionWidget::onRemovePlugin()
{
    removeDialog_.reset(new RemovePluginDialog(plugin_, this));
    removeDialog_->show();
}

void PluginActionWidget::onEnablePlugin()
{
    enablePlugin(enabled_ = !enabled_);
}

void PluginActionWidget::onConfigurePlugin()
{
    Q_EMIT plugin_->configure();
}

void PluginActionWidget::onReloadPlugin()
{
    QMLEnvironment::reloadPlugin(plugin_);
}