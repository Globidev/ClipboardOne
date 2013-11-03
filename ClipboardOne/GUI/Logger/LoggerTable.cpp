#include "stdafx.h"
#include "LoggerTable.h"

#include "LoggerModel.h"
#include "LoggerDelegate.h"

LoggerTable::LoggerTable(QWidget * parent) : QTableView(parent),
    model_(new LoggerModel),
    delegate_(new LoggerDelegate)
{
    horizontalHeader()->setStretchLastSection(true);
    //horizontalHeader()->setSortIndicatorShown(true);

    std::function<void (int, Qt::SortOrder)> sort = 
        std::bind(&QAbstractItemModel::sort, model(), _1,_2);
    QObject::connect(horizontalHeader(), &QHeaderView::sortIndicatorChanged, sort);

    setModel(model_.get());
    setItemDelegate(delegate_.get());

    setStyleSheet(fromResource(":/Transparent/TableView"));
    setShowGrid(false);
}

LoggerModel * LoggerTable::model() const
{
    return model_.get();
}

void LoggerTable::showEvent(QShowEvent * event)
{
    QTableView::showEvent(event);
}