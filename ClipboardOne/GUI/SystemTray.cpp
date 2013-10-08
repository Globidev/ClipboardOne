#include "stdafx.h"
#include "SystemTray.h"

#include "DynamicImageEngine.h"

#include "PluginEditor/PluginEditor.h"
#include "OptionDialog/OptionDialog.h"

#include "GUI/Logger/Logger.h"

SystemTray & SystemTray::instance()
{
    static SystemTray systemTray;
    return systemTray;
}

SystemTray::SystemTray() : QSystemTrayIcon(),
    contextMenu_(new QMenu),
    optionDialog_(new OptionDialog)
{
    setObjectName(SYSTEM_TRAY_OBJECT_NAME);
    setToolTip(SYSTEM_TRAY_BASE_TOOLTIP);

    pluginEditor_.reset(new PluginEditor);

    initContextMenu();
    updateIcon();

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged,
                     this, &SystemTray::updateIcon);

    QObject::connect(this, &QSystemTrayIcon::activated, [this] (QSystemTrayIcon::ActivationReason reason)
    {
        if(reason == QSystemTrayIcon::DoubleClick)
            pluginEditor_->forceShow();
    });

    qAddPostRoutine(clean);
}

void SystemTray::clean()
{
    auto & self = instance();

    self.contextMenu_.reset();
    self.pluginEditor_.reset();
    self.optionDialog_.reset();
}

void SystemTray::alert(const QString & message, 
                       const QString & title, 
                       QJSValue onMessageClicked)
{
    unbindMessageClicked();
    if(!onMessageClicked.isUndefined())
        bindMessageClicked(onMessageClicked);
    showMessage(title, message);
}

void SystemTray::unbindMessageClicked()
{
    if(messageClickedConnection_)
    {
        QObject::disconnect(*messageClickedConnection_);
        messageClickedConnection_.reset();
    }
}

void SystemTray::bindMessageClicked(QJSValue & slot)
{
    if(!IS_CALLABLE_WITH_ARITY(slot, 0))
        Logger::log(SYSTEM_TRAY_ON_MESSAGE_CLICKED_PARAMETER_ERROR, 
                    LogEntry::Type::Error, LogEntry::Scope::Plugin);
    else
    {
        messageClickedConnection_.reset(new QMetaObject::Connection(
            QObject::connect(this, &QSystemTrayIcon::messageClicked,
                            [slot]() mutable { slot.call(); })));
    }
}

void SystemTray::initContextMenu()
{
    auto pluginAction = new QAction(SYSTEM_TRAY_PLUGINS, contextMenu_.get());
    QObject::connect(pluginAction, &QAction::triggered,
                     pluginEditor_.get(), &PluginEditor::forceShow);
    contextMenu_->addAction(pluginAction);

    auto optionsAction = new QAction(SYSTEM_TRAY_OPTIONS, contextMenu_.get());
    QObject::connect(optionsAction, &QAction::triggered, 
                     optionDialog_.get(), &OptionDialog::forceShow);
    contextMenu_->addAction(optionsAction);

    auto quitAction = new QAction(SYSTEM_TRAY_EXIT, contextMenu_.get());
    QObject::connect(quitAction, &QAction::triggered, QApplication::quit);
    contextMenu_->addAction(quitAction);

    QObject::connect(&DynamicImageEngine::instance(), &DynamicImageEngine::maskChanged, [=]
    {
        pluginAction->setIcon (DynamicImageEngine::colored(SYSTEM_TRAY_PLUGINS_ICON));
        optionsAction->setIcon(DynamicImageEngine::colored(SYSTEM_TRAY_OPTIONS_ICON));
        quitAction->setIcon   (DynamicImageEngine::colored(SYSTEM_TRAY_EXIT_ICON));
    });

    setContextMenu(contextMenu_.get());
}

void SystemTray::updateIcon()
{
    setIcon(DynamicImageEngine::colored(SYSTEM_TRAY_ICON));
}