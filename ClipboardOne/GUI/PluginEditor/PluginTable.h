#ifndef PLUGINTABLE_H
#define PLUGINTABLE_H

class PluginTableModel;
class PluginTableDelegate;

class PluginTable : public QTableView
{
    public :
        PluginTable(QWidget * = nullptr);

    private :
        void updateRow(int);

        std::unique_ptr<PluginTableModel> model_;
        std::unique_ptr<PluginTableDelegate> delegate_;
};

#endif // PLUGINTABLE_H