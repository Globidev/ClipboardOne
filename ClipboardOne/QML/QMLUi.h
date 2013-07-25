#ifndef QMLUI_H
#define QMLUI_H

#include "QMLBaseComponent.h"

class QMLUi : public QQmlComponent, public QMLBaseComponent<QMLUi>
{
    Q_OBJECT

    Q_PROPERTY(QString file READ file WRITE setFile)
    Q_PROPERTY(QWidget * mainWindow READ loadedUi)
    Q_PROPERTY(bool isWebUi READ isWebUi WRITE setWebUi)
    Q_PROPERTY(QQmlPropertyMap * loaded READ uiElements)

    public :
        QMLUi();

        QString file() const;
        void setFile(const QString &);

        bool isWebUi() const;
        void setWebUi(bool);

        QQmlPropertyMap * uiElements() const;

        QWidget * loadedUi();

        Q_INVOKABLE void show();

    private :
        inline void loadUi();
        inline void addUiElement(QObject *);

        std::unique_ptr<QWidget> loadedUi_;
        QString uiFileName_;
        bool isWebUi_;

        std::unique_ptr<QQmlPropertyMap> uiElements_;
};

#endif // QMLUI_H