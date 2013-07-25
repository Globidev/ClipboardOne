#ifndef PLUGINTABLEMODEL_H
#define PLUGINTABLEMODEL_H

class PluginTableModel : public QAbstractTableModel
{
    Q_OBJECT
        
    typedef std::function<QVariant (int, Qt::Orientation)> HeaderData;
    typedef std::function<QVariant (const QModelIndex &)> Data;

    public :
        PluginTableModel();

        virtual int rowCount(const QModelIndex & = QModelIndex()) const;
        virtual int columnCount(const QModelIndex & = QModelIndex()) const;

        virtual QVariant data(const QModelIndex &, int = Qt::DisplayRole) const;
        virtual QVariant headerData(int, Qt::Orientation, int = Qt::DisplayRole) const;

    private :
        inline void initIcons();
        inline void initRoleMap();
        inline void initHeaderRoleMap();

        Q_SLOT void updateIcons();

        void onPluginAdded(int);
        void onPluginRemoved(int);

        std::map<int, Data> data_;
        std::map<int, HeaderData> headerData_;
        std::vector<QIcon> horizontalHeaderIcons_;
};

Constant PLUGIN_EDITOR_COLUMN_COUNT = 5;

Constant PLUGIN_EDITOR_HORIZONTAL_HEADER_LABELS = 
    QStringList() << "Name" 
                  << "Version"
                  << "Author"
                  << "Shortcut"
                  << "Actions";

Constant PLUGIN_EDITOR_HORIZONTAL_HEADER_ICONS = 
    QStringList() << ":/PluginEditor/Label" 
                  << ":/PluginEditor/Version"
                  << ":/PluginEditor/Author"
                  << ":/PluginEditor/Shortcut"
                  << ":/PluginEditor/Gear";

Constant PLUGIN_EDITOR_SHORTCUT_COLUMN = 3;
Constant PLUGIN_EDITOR_ACTION_COLUMN = 4;

#endif // PLUGINTABLEMODEL_H