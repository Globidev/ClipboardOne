#include "stdafx.h"
#include "PluginTable.h"

#include "PluginTableModel.h"
#include "PluginTableDelegate.h"

PluginTable::PluginTable(QWidget * parent) : QTableView(parent),
    model_(new PluginTableModel),
    delegate_(new PluginTableDelegate)
{
    verticalHeader()->setDefaultSectionSize(50);
    verticalHeader()->setMinimumSectionSize(50);
    
    horizontalHeader()->setStretchLastSection(true);

    setSelectionMode(QAbstractItemView::NoSelection);

    setModel(model_.get());
    setItemDelegate(delegate_.get());

    QObject::connect(model_.get(), &QAbstractItemModel::rowsInserted,
        [this](const QModelIndex &, int start, int end) { updateRow(start); });
}

void PluginTable::updateRow(int row)
{
    openPersistentEditor(model_->index(row, PLUGIN_EDITOR_SHORTCUT_COLUMN));
    openPersistentEditor(model_->index(row, PLUGIN_EDITOR_ACTION_COLUMN));
    horizontalHeader()->resizeSections(QHeaderView::ResizeToContents);
    horizontalHeader()->resizeSection(horizontalHeader()->count() - 1, QHeaderView::Stretch);
}