#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include "ui_OptionDialog.h"

class OptionDialog : public QDialog
{
    public :
        OptionDialog(QWidget * = nullptr);
        
        Q_SLOT void forceShow();

        Q_SLOT void onStartupToggled(bool);
        Q_SLOT void onIconColorChanged();

    private :
        std::unique_ptr<Ui::UiOptionDialog> ui_;
        std::unique_ptr<QColorDialog> colorDialog_;
};

Constant BACKGROUND_STYLE_SHEET = [](const QColor & color)
{
    return QString("background-color: rgb(%1, %2, %3);")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());
};

Constant OPTION_DIALOG_ICON = ":/SystemTray/Options";

#endif // OPTIONDIALOG_H
