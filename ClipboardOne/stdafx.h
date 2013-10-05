// OS specific
#ifdef WIN32
  #define _WINSOCKAPI_
#endif

// Qt and related libs
#include <QtCore>

#include <QtGui>
#include <QtSvg>
#include <QtWidgets>
#include <QtUiTools>

#include <QtQml>
#include <QtQuick>

#include <QtNetwork>

#include <QtXml> // Currently for SVG file parsing

// Boost
#include <boost/noncopyable.hpp> // Useful for singleton classes

// STL
#include <memory>

#include <functional>
using namespace std::placeholders;

#include <algorithm>
#include <numeric>

#include <set>

// Redis
#ifdef WIN32
  #include <hiredis.h>
#endif

// Syntax sugars
#define Constant static const auto
#define Global static auto

// Application-wide constants
Constant APPLICATION_NAME = "PowerClipboard";

Constant LOCALHOST_IP = "127.0.0.1";

Constant REDIS_SERVER_EXECUTABLE = "redis-server.exe";
Constant REDIS_DEFAULT_PORT      = 6379;

Constant REDIS_SHUTDOWN_COMMAND   = "SHUTDOWN";
Constant REDIS_FLUSHDB_COMMAND    = "FLUSHDB";
Constant REDIS_SET_BINARY_COMMAND = "SET %s %b";
Constant REDIS_GET_COMMAND        = "GET %s";

Constant REDIS_REPLY_OK = "OK";

Constant REDIS_CLIPBOARD_ENTRY_KEY = [](quint32 index)
{ 
    return QString("CB%1").arg(index);
};

Constant CUSTOM_MIME_TYPE = "application/x-qt";
Constant IMAGE_MIME_TYPE  = "application/x-qt-image";

Constant QML_FILE_EXTENSION = "qml";
Constant IS_QML_LOCAL_FILE = [](const QUrl & url)
{
    if(!url.isLocalFile()) return false;

    QFileInfo fileInfo(url.toLocalFile());
    return fileInfo.suffix().toLower() == QML_FILE_EXTENSION;
};

typedef std::function<void ()> DefaultFunctor;

// Shortcuts
typedef std::set<int> Shortcut;
    // For serialization
Q_DECLARE_METATYPE(Shortcut);
QDataStream & operator<<(QDataStream &, const Shortcut &);
QDataStream & operator>>(QDataStream &, Shortcut &);

// Global utilities
    // Containers
template <class Value>
QVariantMap pairListToMap(const QList<QPair<QString, Value>> & list)
{
    QVariantMap map;
    for(const auto & pair : list) 
        map.insert(pair.first, QVariant::fromValue(pair.second));
    return map;
}

    // Force window to be displayed
static void forceShowWindow(QWidget * window)
{
    window->show();
    window->setWindowState(window->windowState() & ~Qt::WindowMinimized | Qt::WindowActive);
    window->activateWindow();
}

    // Generic synchronous function
template <
    class AsyncWorkerSignal,
    class AsyncWorkerCreator,
    class ... AsyncWorkerCreatorArgs,
    class Worker = decltype(std::bind(std::declval<AsyncWorkerCreator>(),  // deduced returned type
                                      std::declval<AsyncWorkerCreatorArgs>() ...)())
>
typename std::enable_if< // Worker must inherit QObject and be a pointer
    std::is_pointer<Worker>::value && 
    std::is_base_of<QObject, typename std::remove_pointer<Worker>::type>::value,
    Worker
>
::type synchronousCall(size_t computingTimeout,
                       AsyncWorkerSignal && endCondition,
                       AsyncWorkerCreator && asyncWorkerCreator,
                       AsyncWorkerCreatorArgs && ... creatorArgs)
{
    QTimer computingTimer;
    computingTimer.setSingleShot(true);

    QEventLoop synchronousLoop;
    QObject::connect(&computingTimer, &QTimer::timeout,
                     &synchronousLoop, &QEventLoop::quit);

    Worker worker = std::bind(asyncWorkerCreator, creatorArgs ...)();
    QObject::connect(worker, endCondition,
                     &synchronousLoop, &QEventLoop::quit);

    computingTimer.start(computingTimeout);
    synchronousLoop.exec();

    return worker;
}

// Type traits

template<class Type>
class is_singleton
{
    template <
        class T,
        // This checks that <Type> has in fact a member called "instance"
        // and also deduce its return type
        class InstanceReturnType = decltype(T::instance())
    >
    static typename std::enable_if<
        // Checks that the return type of "instance" is in fact <Type &>
        std::is_same<InstanceReturnType, T &>::value,
        std::true_type
    >::type hasInstance(void *);

    // Fallback function, substituted if there is no member "instance" for <Type>
    // with the correct return type
    template <class T>
    static std::false_type hasInstance(...);

    typedef decltype(hasInstance<Type>(nullptr)) HasInstance;

    public :
        Constant value = HasInstance::value;
};

#ifdef Q_OS_WIN
static int startProcessElevated(const QString & program, const QStringList & args)
{
    return (int)::ShellExecuteA(0, "runas", program.toUtf8().constData(), 
                                args.join(" ").toUtf8().constData(), 0, SW_HIDE);
}
#endif

Constant IS_CALLABLE_WITH_ARITY = [](const QJSValue & function, int arity)
{
    return function.isCallable() && 
           function.property("length").toInt() == arity;
};