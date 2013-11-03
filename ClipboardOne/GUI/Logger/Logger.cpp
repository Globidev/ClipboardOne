#include "stdafx.h"
#include "logger.h"

#include "LoggerTable.h"
#include "LoggerModel.h"

#include "GUI/DynamicImageEngine.h"

Logger & Logger::instance()
{
    static Logger logger;
    return logger;
}

Logger::Logger() : GlassWidget(),
    ui_(new Ui::UiLogger),
    table_(new LoggerTable(this))
{
    setObjectName(LOGGER_OBJECT_NAME);

    ui_->setupUi(this);
    ui_->verticalLayout->addWidget(table_.get());

    qAddPostRoutine(clean);

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged,
                     [this]()
    {
        setWindowIcon(DynamicImageEngine::colored(LOGGER_WINDOW_ICON));
    });
}

void Logger::clean()
{
    instance().close();
}

void Logger::log(const QString & message,
                 LogEntry::Type type,
                 LogEntry::Scope scope)
{
    instance().table_->model()->addEntry(message, type, scope);
}

void Logger::log(const QString & message)
{
    log(message, LogEntry::Type::Output, LogEntry::Scope::Plugin);
}

void Logger::warning(const QString & message)
{
    log(message, LogEntry::Type::Warning, LogEntry::Scope::Plugin);
}

void Logger::error(const QString & message)
{
    log(message, LogEntry::Type::Error, LogEntry::Scope::Plugin);
}

void Logger::forceShow()
{
    forceShowWindow(this);
}