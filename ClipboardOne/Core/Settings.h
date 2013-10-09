#ifndef SETTINGS_H
#define SETTINGS_H

class Settings : boost::noncopyable
{
    public :
        struct Scope
        {
            explicit Scope(const QString &);
            ~Scope();
        };

        template <class Type>
        class Reference
        {
            public :
                explicit Reference(const QString & key) :
                    key_(key), value_(value<Type>(key)) { }
                Reference(const QString & key, const QString & scopeName) :
                    key_(key), scope_(new Scope(scopeName)), value_(value<Type>(key)) { }
                ~Reference() { setValue(key_, value_); }

                Type * operator->() { return &value_; }

            private :
                QString key_;
                // The order of the following two members actually matters
                std::unique_ptr<Scope> scope_;
                Type value_;
        };

        static Settings & instance();

        static void setValue(const QString &, const QVariant &);
        static void setValue(const QString &, const QVariant &, const QString &);

        template <class Type>
        static Type value(const QString &, const Type & = Type());
        template <class Type>
        static Type value(const QString &, const QString &, const Type & = Type());

        static void removeKey(const QString &);
        static QStringList allKeys();

        static QString directory();

    private :
        Settings();

        std::unique_ptr<QSettings> settings_;
};

template <class Type>
Type Settings::value(const QString & key, const Type & defaultValue)
{
    return instance().settings_->value(key, QVariant::fromValue(defaultValue))
            .value<Type>();
}
        
template <class Type>
Type Settings::value(const QString & key, const QString & scope, const Type & defaultValue)
{
    return value<Type>(QString("%1/%2").arg(scope, key), defaultValue);
}

Constant SETTINGS_DIR = QString(".GlobiData/%1").arg(APPLICATION_NAME);

#endif // SETTINGS_H