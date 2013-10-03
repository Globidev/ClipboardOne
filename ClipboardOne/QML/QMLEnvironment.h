#ifndef QMLENVIRONMENT_H
#define QMLENVIRONMENT_H

template <class T>
class QMLBaseComponent;

class QMLPlugin;

class QMLEnvironment : public QObject, boost::noncopyable
{
    Q_OBJECT

    typedef std::unique_ptr<QQmlComponent> Component;
    typedef std::unique_ptr<QMLPlugin> Plugin;
    typedef std::pair<Component, Plugin> PluginData;

    typedef std::function<void (QMLPlugin *)> PluginAction;

    public :
        static QMLEnvironment & instance();
        static void clean();

        // 2 + types registration
        template <class T, class T2, class ... Tn>
        static void registerComponents()
        {
            registerComponent<T>();
            registerComponents<T2, Tn ...>();
        }

        // 1 type registration
        template <class T>
        static void registerComponents()
        { 
            registerComponent<T>();
        }

        // Custom Component registration
        template <class T>
        static typename std::enable_if<std::is_base_of<QMLBaseComponent<T>, T>::value, void>::type
        registerComponent()
        {
            qmlRegisterType<T>(T::package, T::majorVersion, 
                               T::minorVersion, T::qmlName);
        }

        // Standard type registration
        template <class T>
        static typename std::enable_if<!std::is_base_of<QMLBaseComponent<T>, T>::value, void>::type
        registerComponent()
        {
            qmlRegisterType<T>();
        }

        // 2 + singleton registration
        template <class T, class T2, class ... Tn>
        static void addSingletonToContext()
        {
            addSingletonToContext<T>();
            addSingletonToContext<T2, Tn ...>();
        }

        // 1 singleton registration
        template <class T>
        static void addSingletonToContext()
        {
            static_assert(is_singleton<T>::value, 
                          "Cannot register a non-singleton type as a singleton");
            qmlRegisterType<T>();
            auto & instance = T::instance();
            rootContext()->setContextProperty(instance.objectName(),
                                              QVariant::fromValue(&instance));
        }

        static QQmlContext * rootContext();

        static void addPlugin(const QUrl &);
        static void removePlugin(QMLPlugin *, bool);
        static void reloadPlugin(QMLPlugin *);

        Q_SIGNAL void pluginAdded(int);
        Q_SIGNAL void pluginRemoved(int);

        static QMLPlugin * plugin(int);
        static int pluginCount();

        static void apply(const PluginAction &);

    private :
        QMLEnvironment();

        void onComponentReady(QQmlComponent *, const QUrl &);
        void onComponentError(QQmlComponent *, const QUrl &);
        static inline void initPlugin(QMLPlugin *);

        inline void addPluginToCache(const QUrl &);
        inline void removePluginFromCache(const QUrl &);

        std::unique_ptr<QQmlEngine> engine_;
        std::vector<PluginData> plugins_;
};

#endif // QMLENVIRONMENT_H