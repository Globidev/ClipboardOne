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

        std::unique_ptr<Ui::UiAddPluginDialog> ui_;
};

#endif // ADDPLUGINDIALOG_H