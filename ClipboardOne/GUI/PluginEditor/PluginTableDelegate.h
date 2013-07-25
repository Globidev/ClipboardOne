#ifndef PLUGINTABLEDELEGATE_H
#define PLUGINTABLEDELEGATE_H

class PluginTableDelegate : public QItemDelegate
{
    public :
        virtual QWidget * createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;
        virtual void updateEditorGeometry(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const;
};

#endif // PLUGINTABLEDELEGATE_H