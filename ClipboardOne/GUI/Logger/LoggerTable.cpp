#include "stdafx.h"
#include "LoggerTable.h"

#include "LoggerModel.h"
#include "LoggerDelegate.h"

LoggerTable::LoggerTable(QWidget * parent) : QTableView(parent),
    model_(new LoggerModel),
    delegate_(new LoggerDelegate)
{
    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    setModel(model_.get());
    setItemDelegate(delegate_.get());
}

LoggerModel * LoggerTable::model() const
{
    return model_.get();
}

void LoggerTable::showEvent(QShowEvent * event)
{
    QTableView::showEvent(event);
    verticalHeader()->resizeSections(QHeaderView::ResizeToContents);
}