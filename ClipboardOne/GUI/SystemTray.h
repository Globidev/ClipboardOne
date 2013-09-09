#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

class PluginEditor;
class OptionDialog;

class SystemTray : public QSystemTrayIcon, boost::noncopyable
{
    Q_OBJECT

    public :
        static SystemTray & instance();

        Q_INVOKABLE void alert(const QString &, 
                               const QString & = QString(), 
                               QSystemTrayIcon::MessageIcon = Information);

    private :
        SystemTray();
        static void clean();

        Q_SLOT void updateIcon();

        inline void initContextMenu();
        std::unique_ptr<QMenu> contextMenu_;

        std::unique_ptr<PluginEditor> pluginEditor_;
        std::unique_ptr<OptionDialog> optionDialog_;
};

Constant SYSTEM_TRAY_OBJECT_NAME = "SystemTray";

Constant SYSTEM_TRAY_ICON = ":/SystemTray/Scissors";

Constant SYSTEM_TRAY_EXIT_ICON = ":/SystemTray/Exit";
Constant SYSTEM_TRAY_EXIT = "Exit";

Constant SYSTEM_TRAY_OPTIONS_ICON = ":/SystemTray/Options";
Constant SYSTEM_TRAY_OPTIONS = "Options";

Constant SYSTEM_TRAY_PLUGINS_ICON = ":/SystemTray/Plugins";
Constant SYSTEM_TRAY_PLUGINS = "Plug-ins";

Constant SYSTEM_TRAY_BASE_TOOLTIP = APPLICATION_NAME;

#endif // SYSTEMTRAY_H