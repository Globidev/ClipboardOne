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

Logger::Logger() : QWidget(),
    ui_(new Ui::UiLogger),
    table_(new LoggerTable(this))
{
    ui_->setupUi(this);
    ui_->verticalLayout->addWidget(table_.get());

    qAddPostRoutine(clean);

    QObject::connect(&DynamicImageEngine::instance(), 
                     &DynamicImageEngine::maskChanged,
                     [this]()
    {
        setWindowIcon(DynamicImageEngine::colored(":/SystemTray/Scissors"));
        table_->update();
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