#ifndef LOGGER_H
#define LOGGER_H

#include "ui_Logger.h"
#include "LogEntry.h"

class LoggerTable;

class Logger : public QWidget, boost::noncopyable
{
    Q_OBJECT

    public :
        static Logger & instance();

        static void log(const QString &, LogEntry::Type, LogEntry::Scope);

        Q_INVOKABLE void log(const QString &);
        Q_INVOKABLE void warning(const QString &);
        Q_INVOKABLE void error(const QString &);

    private :
        Logger();
        static void clean();

        std::unique_ptr<Ui::UiLogger> ui_;
        std::unique_ptr<LoggerTable> table_;
};

Constant LOGGER_OBJECT_NAME = "Logger";
Constant LOGGER_WINDOW_ICON = ":/PluginEditor/Logs";

#endif // LOGGER_H