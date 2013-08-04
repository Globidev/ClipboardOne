#include "stdafx.h"
#include "SystemTray.h"

#include "DynamicImageEngine.h"

#include "GUI/PluginEditor/PluginEditor.h"

SystemTray & SystemTray::instance()
{
    static SystemTray systemTray;
    return systemTray;
}

SystemTray::SystemTray() : QSystemTrayIcon(),
    contextMenu_(new QMenu),
    colorDialog_(new QColorDialog)
{
    setObjectName(SYSTEM_TRAY_OBJECT_NAME);
    setToolTip(SYSTEM_TRAY_BASE_TOOLTIP);

    pluginEditor_.reset(new PluginEditor);

    initContextMenu();
    updateIcon();

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged,
                     this, &SystemTray::updateIcon);

    QObject::connect(colorDialog_.get(), 
                     &QColorDialog::currentColorChanged, 
                     &DynamicImageEngine::setMaskColor);

    qAddPostRoutine(clean);
}

void SystemTray::clean()
{
    instance().contextMenu_.release(); // LEAK (use reset when fixed)
                                       // QT BUG : https://bugreports.qt-project.org/browse/QTBUG-30756
    instance().pluginEditor_.reset();
    instance().colorDialog_.reset();
}

void SystemTray::alert(const QString & message, 
                       const QString & title, 
                       QSystemTrayIcon::MessageIcon icon)
{
    showMessage(title, message, icon);
}

void SystemTray::initContextMenu()
{
    auto pluginAction = new QAction(SYSTEM_TRAY_PLUGINS, contextMenu_.get());
    QObject::connect(pluginAction, &QAction::triggered,
                     pluginEditor_.get(), &PluginEditor::forceShow);
    contextMenu_->addAction(pluginAction);

    auto optionsAction = new QAction(SYSTEM_TRAY_OPTIONS, contextMenu_.get());
    QObject::connect(optionsAction, &QAction::triggered, 
                     colorDialog_.get(), &QColorDialog::show);
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