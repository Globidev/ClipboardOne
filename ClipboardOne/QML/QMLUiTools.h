#ifndef QMLUITOOLS_H
#define QMLUITOOLS_H

class QMLUiTools : public QObject, boost::noncopyable
{
    Q_OBJECT

    public :
        static QMLUiTools & instance();
        static void clean();

        Q_INVOKABLE QWidget * qmlWidget(QQuickItem *);
        Q_INVOKABLE void layWidget(QLayout *, QWidget *);

    private :
        QMLUiTools();
        std::unique_ptr<QWidget> rootWidget;
};

Constant QML_UI_TOOLS_OBJECT_NAME = "UiTools";

#endif // QMLUITOOLS_H