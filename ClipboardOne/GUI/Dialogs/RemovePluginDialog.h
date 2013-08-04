#ifndef REMOVEPLUGINDUALOG_H
#define REMOVEPLUGINDUALOG_H

#include "ui_RemovePluginDialog.h"

class QMLPlugin;

class RemovePluginDialog : public QDialog
{
    Q_OBJECT

    public :
        RemovePluginDialog(QMLPlugin *, QWidget * = nullptr);

        virtual Q_SLOT void accept();

    private :
        std::unique_ptr<Ui::UiRemovePluginDialog> ui_;
        QMLPlugin * plugin_;
};

Constant REMOVE_PLUGIN_DIALOG_WINDOW_ICON = ":/Dialogs/QuestionMark";
Constant REMOVE_PLUGIN_DIALOG_QUESTION_ICON = ":/Dialogs/QuestionMark";
Constant REMOVE_PLUGIN_DIALOG_OK_ICON = ":/AddPluginDialog/Ok";
Constant REMOVE_PLUGIN_DIALOG_CANCEL_ICON = ":/AddPluginDialog/Cancel";

#endif // REMOVEPLUGINDUALOG_H