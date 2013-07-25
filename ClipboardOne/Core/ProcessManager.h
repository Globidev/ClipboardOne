#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

class ProcessManager : public QObject, boost::noncopyable
{
    Q_OBJECT

    public :
        static ProcessManager & instance();

        Q_INVOKABLE bool startDetached(const QString &, const QStringList & = QStringList());

    private :
        ProcessManager();
};

Constant PROCESS_MANAGER_OBJECT_NAME = "Process";

#endif // PROCESSMANAGER_H