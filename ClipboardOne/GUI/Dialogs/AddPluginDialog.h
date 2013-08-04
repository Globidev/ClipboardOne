#ifndef ADDPLUGINDIALOG_H
#define ADDPLUGINDIALOG_H

#include "ui_AddPluginDialog.h"

class AddPluginDialog : public QDialog
{
    public :
        AddPluginDialog(QWidget * = nullptr);

        virtual Q_SLOT void accept();

    private :
        void onBrowse();

        Q_SLOT void updateIcons();

        std::unique_ptr<Ui::UiAddPluginDialog> ui_;
};

Constant ADD_PLUGIN_DIALOG_WINDOW_ICON = ":/PluginEditor/Add";
Constant ADD_PLUGIN_DIALOG_OK_ICON = ":/AddPluginDialog/Ok";
Constant ADD_PLUGIN_DIALOG_CANCEL_ICON = ":/AddPluginDialog/Cancel";

#endif // ADDPLUGINDIALOG_H