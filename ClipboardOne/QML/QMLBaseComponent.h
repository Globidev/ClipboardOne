#ifndef QMLBASECOMPONENT_H
#define QMLBASECOMPONENT_H

template <class QMLComponent>
struct QMLBaseComponent
{
    static const char * package;
    static const int majorVersion;
    static const int minorVersion;
    static const char * qmlName;

    const QMLComponent & This()
    {
        return static_cast<const QMLComponent &>(*this);
    }

    void addContextProperty(QObject * object)
    {
        auto context = This().creationContext()->parentContext();
        context->setContextProperty(object->objectName(), object);
    }
};

#endif // QMLBASECOMPONENT_H