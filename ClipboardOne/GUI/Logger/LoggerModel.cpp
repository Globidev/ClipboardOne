#include "stdafx.h"
#include "LoggerModel.h"

#include "GUI/DynamicImageEngine.h"

LoggerModel::LoggerModel()
{
    initRoleMap();
    initHeaderRoleMap();
}

void LoggerModel::initRoleMap()
{
    typedef std::function<QVariant (LogEntry *)> LogEntryData;

    auto type    = [](LogEntry * entry) { return LOG_ENTRY_TYPE(entry->type)  ; };
    auto scope   = [](LogEntry * entry) { return LOG_ENTRY_SCOPE(entry->scope); };
    auto message = [](LogEntry * entry) { return entry->message;                };

    LogEntryData _columnData[] = { type, scope, message };
    std::vector<LogEntryData> columnData(&_columnData[0], &_columnData[0] + LOG_TABLE_COLUMN_COUNT);

    data_[Qt::DisplayRole] = [columnData, this](const QModelIndex & index)
    {
        return columnData[index.column()](entries_.at(index.row()).get());
    };

    data_[Qt::TextAlignmentRole] = [](const QModelIndex & index)
    {
        return Qt::AlignVCenter;
    };

    data_[Qt::ForegroundRole] = [this](const QModelIndex & index)
    {
        return index.column() == 0 ?
                LOG_ENTRY_TYPE_COLOR(entries_.at(index.row())->type) :
                QVariant();
    };

    data_[Qt::DecorationRole] = [this](const QModelIndex & index) -> QVariant
    {
        if(index.column() == 1)
        {
            auto iconName = LOG_ENTRY_SCOPE_ICON(entries_.at(index.row())->scope);
            QPixmap icon(DynamicImageEngine::colored(iconName));
            return icon.scaled(QSize(20, 20), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        }
        return QVariant();
    };

    data_[Qt::FontRole] = [this](const QModelIndex & index) -> QVariant
    {
        QFont font;
        font.setBold(index.column() == 0);
        font.setItalic(index.column() == 1);
        return font;
    };
}

void LoggerModel::initHeaderRoleMap()
{
    headerData_[Qt::DisplayRole] = [](int section, Qt::Orientation orientation)
    {
        return orientation == Qt::Vertical ?
               QVariant() :
               LOG_TABLE_HORIZONTAL_HEADER_LABELS[section];
    };
}

int LoggerModel::rowCount(const QModelIndex &) const
{
    return entries_.size();
}

int LoggerModel::columnCount(const QModelIndex &) const
{
    return LOG_TABLE_COLUMN_COUNT;
}

QVariant LoggerModel::data(const QModelIndex & index, int role) const
{
    auto dataFound = data_.find(role);
    return dataFound != data_.end() ?
           dataFound->second(index) :
           QVariant();
}

QVariant LoggerModel::headerData(int section, 
                                 Qt::Orientation orientation, 
                                 int role) const
{
    auto dataFound = headerData_.find(role);
    return dataFound != headerData_.end() ? 
           dataFound->second(section, orientation) :
           QVariant();
}

void LoggerModel::addEntry(const QString & message, 
                           LogEntry::Type type, 
                           LogEntry::Scope scope)
{
    beginInsertRows(QModelIndex(), entries_.size(), entries_.size());
    entries_.emplace_back(new LogEntry(message, type, scope));
    endInsertRows();
}