#ifndef LOGGER_H
#define LOGGER_H

#include "ui_Logger.h"

#include "LogEntry.h"

class LoggerTable;

class Logger : public QWidget, boost::noncopyable
{
    public :
        static Logger & instance();

        static void log(const QString &, LogEntry::Type, LogEntry::Scope);

    private :
        Logger();
        static void clean();

        std::unique_ptr<Ui::UiLogger> ui_;
        std::unique_ptr<LoggerTable> table_;
};

#endif // LOGGER_H