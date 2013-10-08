#ifndef LOGENTRY_H
#define LOGENTRY_H

struct LogEntry
{
    enum class Type { 
        Output, 
        Warning, 
        Error 
    };

    enum class Scope {
        Unknown,
        Redis,
        Plugin
    };

    LogEntry(const QString &, Type, Scope);

    QString message;
    Type type;
    Scope scope;
};

Constant LOG_ENTRY_TYPE = [](LogEntry::Type type)
{
    switch(type)
    {
        case LogEntry::Type::Output  : return "Output";
        case LogEntry::Type::Error   : return "Error";
        case LogEntry::Type::Warning : return "Warning";
    }
    return "Unknown";
};

Constant LOG_ENTRY_SCOPE = [](LogEntry::Scope scope)
{
    switch(scope)
    {
        case LogEntry::Scope::Unknown : return "Unknown";
        case LogEntry::Scope::Plugin  : return "Plugin";
        case LogEntry::Scope::Redis   : return "Redis";
    }
    return "Unknown";
};

Constant LOG_ENTRY_TYPE_COLOR = [](LogEntry::Type type) -> QBrush
{
    switch(type)
    {
        case LogEntry::Type::Output  : return QColor(0, 192, 128);
        case LogEntry::Type::Error   : return Qt::red;
        case LogEntry::Type::Warning : return QColor(255, 128, 0);
    }
    return Qt::black;
};

Constant LOG_ENTRY_SCOPE_ICON = [](LogEntry::Scope scope)
{
    switch(scope)
    {
        case LogEntry::Scope::Unknown : return ":/ShortcutEditor/QuestionMark";
        case LogEntry::Scope::Plugin  : return ":/SystemTray/Plugins";
        case LogEntry::Scope::Redis   : return ":/Redis/Redis";
    }
    return ":/ShortcutEditor/QuestionMark";
};

#endif // LOGENTRY_H