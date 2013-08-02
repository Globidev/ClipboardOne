#ifndef LOGGERMODEL_H
#define LOGGERMODEL_H

#include "LogEntry.h"

class LoggerModel : public QAbstractTableModel
{
    typedef std::function<QVariant (int, Qt::Orientation)> HeaderData;
    typedef std::function<QVariant (const QModelIndex &)> Data;

    public :
        LoggerModel();

        virtual int rowCount(const QModelIndex & = QModelIndex()) const;
        virtual int columnCount(const QModelIndex & = QModelIndex()) const;

        virtual QVariant data(const QModelIndex &, int = Qt::DisplayRole) const;
        virtual QVariant headerData(int, Qt::Orientation, int = Qt::DisplayRole) const;

        void addEntry(const QString &, LogEntry::Type, LogEntry::Scope);

    private :
        inline void initRoleMap();
        inline void initHeaderRoleMap();

        std::vector<std::unique_ptr<LogEntry>> entries_;

        std::map<int, Data> data_;
        std::map<int, HeaderData> headerData_;
};

Constant LOG_TABLE_COLUMN_COUNT = 3;

Constant LOG_TABLE_HORIZONTAL_HEADER_LABELS = 
    QStringList() << "Type" 
                  << "Scope"
                  << "Message";

#endif // LOGGERMODEL_H