#include "stdafx.h"
#include "PluginEditor.h"

#include "PluginTable.h"

#include "GUI/Dialogs/AddPluginDialog.h"
#include "GUI/DynamicImageEngine.h"
#include "GUI/Logger/Logger.h"

#include "QML/QMLEnvironment.h"

PluginEditor::PluginEditor(QWidget * parent) : QWidget(parent),
    ui_(new Ui::UiPluginEditor),
    pluginTable_(new PluginTable(this))
{
    ui_->setupUi(this);
    ui_->verticalLayout->addWidget(pluginTable_.get());

    QObject::connect(ui_->addPlugin, 
                     &QPushButton::clicked,
                     this, &PluginEditor::addNewPlugin);

    QObject::connect(ui_->showLogs,
                     &QPushButton::clicked,
                     &Logger::instance(), &Logger::forceShow);

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged,
                     this, &PluginEditor::updateIcons);

    setAcceptDrops(true);
}

void PluginEditor::addNewPlugin()
{
    addPluginDialog_.reset(new AddPluginDialog(this));
    addPluginDialog_->show();
}

void PluginEditor::forceShow()
{
    show();
    setWindowState(Qt::WindowActive);
}

void PluginEditor::updateIcons()
{
    setWindowIcon(DynamicImageEngine::colored(PLUDIN_EDITOR_WINDOW_ICON));
    ui_->addPlugin->setIcon(DynamicImageEngine::colored(PLUGIN_EDITOR_ADD_PLUGIN_ICON));
    ui_->showLogs->setIcon(DynamicImageEngine::colored(PLUGIN_EDITOR_SHOW_LOGS_ICON));
}

void PluginEditor::dragEnterEvent(QDragEnterEvent * event)
{
    auto urlList = event->mimeData()->urls().toStdList();
    bool hasQmlFiles = std::any_of(urlList.cbegin(),
                                   urlList.cend(),
                                   IS_QML_LOCAL_FILE);
    if(hasQmlFiles) event->acceptProposedAction();
}

void PluginEditor::dropEvent(QDropEvent * event)
{
    for(const QUrl & url : event->mimeData()->urls())
        if(IS_QML_LOCAL_FILE(url))
            QMLEnvironment::addPlugin(url);
    event->acceptProposedAction();
}