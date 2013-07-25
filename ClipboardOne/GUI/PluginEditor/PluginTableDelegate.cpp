#include "stdafx.h"
#include "PluginTableDelegate.h"

#include "PluginTableModel.h"
#include "PluginActionWidget.h"

#include "GUI/ShortcutEditor.h"

#include "QML/QMLEnvironment.h"

QWidget * PluginTableDelegate::createEditor(QWidget * parent,
                                            const QStyleOptionViewItem & option,
                                            const QModelIndex & index) const
{
    auto plugin = QMLEnvironment::plugin(index.row());

    if(index.column() == PLUGIN_EDITOR_SHORTCUT_COLUMN) 
        return new ShortcutEditor(plugin, parent);
    else if(index.column() == PLUGIN_EDITOR_ACTION_COLUMN)
        return new PluginActionWidget(plugin, parent);
    return nullptr;
}

void PluginTableDelegate::updateEditorGeometry(QWidget * editor, 
                                               const QStyleOptionViewItem & option, 
                                               const QModelIndex & index) const
{
    editor->setGeometry(option.rect);
}