#ifndef PLUGINACTIONWIDGET_H
#define PLUGINACTIONWIDGET_H

#include "ui_PluginActionWidget.h"
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

Constant REMOVE_PLUGIN_QUESTION_ICON = ":/Dialogs/QuestionMark";

class PluginActionWidget : public QWidget
{
    Q_OBJECT

    public :
        PluginActionWidget(QMLPlugin *, QWidget * = nullptr);

    private :
        void enablePlugin(bool);
        inline void updateIcons();

        Q_SLOT void onConfigurableChanged(bool);

        Q_SLOT void onRemovePlugin();
        Q_SLOT void onEnablePlugin();
        Q_SLOT void onConfigurePlugin();

        std::unique_ptr<Ui::UiPluginActionWidget> ui_;
        std::unique_ptr<RemovePluginDialog> removeDialog_;
        QMLPlugin * plugin_;

        QIcon onIcon_, offIcon_;
        bool enabled_;
};

Constant PLUGIN_ACTION_REMOVE_ICON    = ":/PluginEditor/Delete";
Constant PLUGIN_ACTION_ENABLED_ICON   = ":/PluginEditor/SwitchOn";
Constant PLUGIN_ACTION_DISABLED_ICON  = ":/PluginEditor/SwitchOff";
Constant PLUGIN_ACTION_CONFIGURE_ICON = ":/PluginEditor/Configuration";

#endif // PLUGINACTIONWIDGET_H