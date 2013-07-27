#include "stdafx.h"
#include "QMLUiTools.h"

QMLUiTools & QMLUiTools::instance()
{
    static QMLUiTools uiTools;
    return uiTools;
}

QMLUiTools::QMLUiTools() : QObject(),
    rootWidget(new QWidget)
{
    setObjectName(QML_UI_TOOLS_OBJECT_NAME);
    qAddPostRoutine(clean);
}

void QMLUiTools::clean()
{
    instance().rootWidget.reset();
}

QWidget * QMLUiTools::qmlWidget(QQuickItem * rootItem)
{
    if(!rootItem) return nullptr;
    auto window = new QQuickWindow;
    rootItem->setParentItem(window->contentItem());
    return QWidget::createWindowContainer(window, rootWidget.get(), Qt::Window);
}

void QMLUiTools::layWidget(QLayout * layout, QWidget * widget)
{
    if(layout && widget)
        layout->addWidget(widget);
}