#include "stdafx.h"
#include "QMLUiTools.h"

QMLUiTools & QMLUiTools::instance()
{
    static QMLUiTools uiTools;
    return uiTools;
}

QMLUiTools::QMLUiTools() : QObject()
{
    setObjectName(QML_UI_TOOLS_OBJECT_NAME);
}

QWidget * QMLUiTools::qmlWidget(const QUrl & url)
{
    auto view = new QQuickView;
    view->setSource(url);
    return QWidget::createWindowContainer(view);
}

void QMLUiTools::layWidget(QLayout * layout, QWidget * widget)
{
    if(layout && widget)
        layout->addWidget(widget);
}