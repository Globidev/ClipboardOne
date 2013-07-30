#include "stdafx.h"

#include "Core/GlobiSingleApplication.h"
#include "Core/ClipboardWatcher.h"
#include "Core/MimeDataEntry.h"
#include "Core/Settings.h"

#include "Core/Redis/RedisServer.h"

#include "QML/QMLPlugin.h"
#include "QML/QMLUi.h"
#include "QML/QMLClipboard.h"
#include "QML/QMLSettings.h"
#include "QML/QMLEnvironment.h"

#include "GUI/SystemTray.h"
#include "GUI/DynamicImageEngine.h"

#include "Network/NetworkAccessManager.h"
#include "Network/NetworkHTTPRequest.h"
#include "Network/NetworkHTTPReply.h"
#include "Network/LocalHTTPServer.h"

int main(int argc, char *argv[])
{
    qRegisterMetaTypeStreamOperators<Shortcut>();

    QMLEnvironment::registerComponents
    <
        QMLPlugin,
        QMLUi,
        QMLClipboard,
        QMLSettings,
        QQmlPropertyMap,
        QWidget,
        QLayout,
        MimeDataEntry,
        QNetworkReply,
        LocalHTTPServer,
        NetworkHTTPRequest,
        NetworkHTTPReply
    >();

    GlobiSingleApplication app(argc, argv, APPLICATION_NAME);
    app.setQuitOnLastWindowClosed(false);

    RedisServer::command(REDIS_FLUSHDB_COMMAND);
    SystemTray::instance().show();
    ClipboardWatcher::instance();

    auto color = Settings::value<QColor>("mask_color", "Ui", Qt::black); // initial color
    DynamicImageEngine::setMaskColor(color);

    for(auto & pluginUrl : Settings::value<QStringList>("urls", "Plug-ins"))
        QMLEnvironment::addPlugin(QUrl(pluginUrl));

    app.exec();
    return 0;
}
