#include "stdafx.h"
#include "RemovePluginDialog.h"

#include "GUI/DynamicImageEngine.h"

#include "QML/QMLEnvironment.h"
#include "QML/QMLPlugin.h"

RemovePluginDialog::RemovePluginDialog(QMLPlugin * plugin, QWidget * parent) : QDialog(parent),
    ui_(new Ui::UiRemovePluginDialog),
    plugin_(plugin)
{
    ui_->setupUi(this);
    setWindowModality(Qt::WindowModal);

    ui_->label->setText(ui_->label->text().arg(plugin->name()));

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged,
                     this, &RemovePluginDialog::updateIcons,
                     Qt::QueuedConnection);
    updateIcons();
}

void RemovePluginDialog::accept()
{
    bool removeSettings = ui_->removeSettings->isChecked();
    QMLEnvironment::removePlugin(plugin_, removeSettings);

    QDialog::accept();
}

void RemovePluginDialog::updateIcons()
{
    setWindowIcon(DynamicImageEngine::colored(REMOVE_PLUGIN_DIALOG_WINDOW_ICON));
    ui_->icon->setIcon(DynamicImageEngine::colored(REMOVE_PLUGIN_DIALOG_QUESTION_ICON));
    ui_->okButton->setIcon(DynamicImageEngine::colored(REMOVE_PLUGIN_DIALOG_OK_ICON));
    ui_->cancelButton->setIcon(DynamicImageEngine::colored(REMOVE_PLUGIN_DIALOG_CANCEL_ICON));
}