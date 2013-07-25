#include "stdafx.h"
#include "ProcessManager.h"

ProcessManager & ProcessManager::instance()
{
    static ProcessManager processManager;
    return processManager;
}

ProcessManager::ProcessManager()
{
    setObjectName(PROCESS_MANAGER_OBJECT_NAME);
}

bool ProcessManager::startDetached(const QString & program, const QStringList & arguments)
{
    return QProcess::startDetached(program, arguments);
}