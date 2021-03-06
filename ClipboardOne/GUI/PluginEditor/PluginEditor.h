#ifndef PLUGINEDITOR_H
#define PLUGINEDITOR_H

#include "ui_PluginEditor.h"
#include "../GUI/Styles/GlassWidget.h"

class PluginTable;
class AddPluginDialog;

class PluginEditor : public GlassWidget
{
    Q_OBJECT

    public :
        PluginEditor(QWidget * = nullptr);

        Q_SLOT void addNewPlugin();
        Q_SLOT void forceShow();

    protected :
        virtual void dragEnterEvent(QDragEnterEvent *);
        virtual void dropEvent(QDropEvent *);
#ifdef WIN32
        virtual void showEvent(QShowEvent *);
        bool resizeOnce_;
#endif

    private :
        Q_SLOT void updateIcons();

        std::unique_ptr<Ui::UiPluginEditor> ui_;

        std::unique_ptr<PluginTable> pluginTable_;
        std::unique_ptr<AddPluginDialog> addPluginDialog_;
};

Constant PLUGIN_EDITOR_ADD_PLUGIN_ICON = ":/PluginEditor/Add";
Constant PLUGIN_EDITOR_SHOW_LOGS_ICON = ":/PluginEditor/Logs";
Constant PLUDIN_EDITOR_WINDOW_ICON = ":/SystemTray/Scissors";

#endif // PLUGINEDITOR_H