#ifndef QMLUITOOLS_H
#define QMLUITOOLS_H

class QMLUiTools : public QObject, boost::noncopyable
{
    Q_OBJECT

    public :
        static QMLUiTools & instance();

        Q_INVOKABLE QWidget * qmlWidget(const QUrl &);
        Q_INVOKABLE void layWidget(QLayout *, QWidget *);

    private :
        QMLUiTools();
};

Constant QML_UI_TOOLS_OBJECT_NAME = "UiTools";

#endif // QMLUITOOLS_H