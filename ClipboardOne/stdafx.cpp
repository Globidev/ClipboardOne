#include "stdafx.h"

QDataStream & operator<<(QDataStream & s, const Shortcut & set)
{
    s << set.size();
    for(auto i : set) s << i;
    return s;
}

QDataStream & operator>>(QDataStream & s, Shortcut & set)
{
    int size;
    s >> size;
    for(int i(0); i < size; ++ i)
    {
        int v;
        s >> v;
        set.insert(v);
    }
    return s;
}

void forceShowWindow(QWidget * window)
{
    window->show();
    window->setWindowState(window->windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
    window->activateWindow();
}

QString fromResource(const QString & resourceName)
{
    QFile resource(resourceName);
    resource.open(QIODevice::ReadOnly);
    return resource.readAll();
}

#ifdef WIN32
void startProcessElevated(const QString & program, const QStringList & args)
{
    ShellExecuteA(0, "runas", program.toUtf8().constData(), 
                  args.join(" ").toUtf8().constData(), 0, SW_HIDE);
}
#else
void startProcessElevated(const QString & program, const QStringList & args)
{
    QProcess::startDetached(program, args);
}
#endif

bool jsIsCallableWithArity(const QJSValue & function, int arity)
{
    return function.isCallable() && 
           function.property("length").toInt() == arity;
}