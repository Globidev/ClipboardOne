#include "stdafx.h"
#include "PluginEditor.h"

#include "PluginTable.h"

#include "GUI/Dialogs/AddPluginDialog.h"
#include "Gui/DynamicImageEngine.h"

PluginEditor::PluginEditor(QWidget * parent) : QWidget(parent),
    ui_(new Ui::UiPluginEditor),
    pluginTable_(new PluginTable(this))
{
    ui_->setupUi(this);
    ui_->verticalLayout->addWidget(pluginTable_.get());

    QObject::connect(ui_->addPlugin, 
                     &QPushButton::clicked,
                     this, &PluginEditor::addNewPlugin);

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged,
                     this, &PluginEditor::updateIcons);
}

void PluginEditor::addNewPlugin()
{
    addPluginDialog_.reset(new AddPluginDialog(this));
    addPluginDialog_->show();
}

void PluginEditor::updateIcons()
{
    setWindowIcon(DynamicImageEngine::colored(PLUDIN_EDITOR_WINDOW_ICON));
    ui_->addPlugin->setIcon(DynamicImageEngine::colored(PLUGIN_EDITOR_ADD_PLUGIN_ICON));
    ui_->showLogs->setIcon(DynamicImageEngine::colored(PLUGIN_EDITOR_SHOW_LOGS_ICON));
}