#ifndef LOGGERTABLE_H
#define LOGGERTABLE_H

class LoggerModel;
class LoggerDelegate;

class LoggerTable : public QTableView
{
    public :
        LoggerTable(QWidget * = nullptr);

        LoggerModel * model() const;

    protected :
        virtual void showEvent(QShowEvent *);

    private :
        std::unique_ptr<LoggerModel> model_;
        std::unique_ptr<LoggerDelegate> delegate_;
};

#endif // LOGGERTABLE_H