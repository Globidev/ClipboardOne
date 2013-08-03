#include "stdafx.h"
#include "LogEntry.h"

LogEntry::LogEntry(const QString & message, 
                   Type type, 
                   Scope scope) :
    message(message.trimmed()),
    type(type),
    scope(scope)
{

}