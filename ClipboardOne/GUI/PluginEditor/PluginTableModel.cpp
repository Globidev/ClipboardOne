#include "stdafx.h"
#include "PluginTableModel.h"

#include "GUI/DynamicImageEngine.h"

#include "QML/QMLEnvironment.h"
#include "QML/QMLPlugin.h"

PluginTableModel::PluginTableModel()
{
    initIcons();
    initRoleMap();
    initHeaderRoleMap();

    QObject::connect(&QMLEnvironment::instance(),
                     &QMLEnvironment::pluginAdded,
                     [this](int index) { onPluginAdded(index); });

    QObject::connect(&QMLEnvironment::instance(),
                     &QMLEnvironment::pluginRemoved,
                     [this](int index) { onPluginRemoved(index); });
}

void PluginTableModel::initIcons()
{
    for(const QString & iconPath : PLUGIN_EDITOR_HORIZONTAL_HEADER_ICONS)
    {
        horizontalHeaderIcons_.emplace_back(iconPath);
        QObject::connect(&DynamicImageEngine::instance(),
                         &DynamicImageEngine::maskChanged,
                         this, &PluginTableModel::updateIcons);
    }
}

void PluginTableModel::initRoleMap()
{
    typedef std::function<QVariant (QMLPlugin *)> PluginData;

    auto name     = [](QMLPlugin * plugin) { return plugin->name();    };
    auto version  = [](QMLPlugin * plugin) { return plugin->version(); };
    auto author   = [](QMLPlugin * plugin) { return plugin->author();  };
    auto shortcut = [](QMLPlugin * plugin) { return QVariant();        };
    auto actions  = [](QMLPlugin * plugin) { return QVariant();        };

    PluginData _columnData[] = { name, version, author, shortcut, actions };
    std::vector<PluginData> columnData(&_columnData[0], &_columnData[0] + PLUGIN_EDITOR_COLUMN_COUNT);

    data_[Qt::DisplayRole] = [columnData](const QModelIndex & index) -> QVariant
    {
        return columnData[index.column()](QMLEnvironment::plugin(index.row()));
    };

    data_[Qt::TextAlignmentRole] = [](const QModelIndex & index) -> QVariant
    {
        return Qt::AlignCenter;
    };
}

void PluginTableModel::initHeaderRoleMap()
{
    headerData_[Qt::DisplayRole] = [](int section, Qt::Orientation orientation)
    {
        return orientation == Qt::Vertical ?
               QVariant() :
               PLUGIN_EDITOR_HORIZONTAL_HEADER_LABELS[section];
    };

    headerData_[Qt::DecorationRole] = [this](int section, Qt::Orientation orientation)
    {
        return orientation == Qt::Horizontal ?
               horizontalHeaderIcons_.at(section) :
               QMLEnvironment::plugin(section)->loadedIcon();
    };
}

int PluginTableModel::rowCount(const QModelIndex &) const
{
    return QMLEnvironment::pluginCount();
}

int PluginTableModel::columnCount(const QModelIndex &) const
{
    return PLUGIN_EDITOR_COLUMN_COUNT;
}

QVariant PluginTableModel::data(const QModelIndex & index, int role) const
{
    auto dataFound = data_.find(role);
    return dataFound != data_.end() ?
           dataFound->second(index) :
           QVariant();
}

QVariant PluginTableModel::headerData(int section, 
                                      Qt::Orientation orientation, 
                                      int role) const
{
    auto dataFound = headerData_.find(role);
    return dataFound != headerData_.end() ? 
           dataFound->second(section, orientation) :
           QVariant();
}

void PluginTableModel::updateIcons()
{
    for(size_t i(0); i < PLUGIN_EDITOR_COLUMN_COUNT; ++ i)
        horizontalHeaderIcons_[i] = DynamicImageEngine::colored(PLUGIN_EDITOR_HORIZONTAL_HEADER_ICONS[i]); 
    headerDataChanged(Qt::Horizontal, 0, PLUGIN_EDITOR_COLUMN_COUNT);
}

void PluginTableModel::onPluginAdded(int index)
{
    beginInsertRows(QModelIndex(), index, index);
    endInsertRows();
}

void PluginTableModel::onPluginRemoved(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    endRemoveRows();
}