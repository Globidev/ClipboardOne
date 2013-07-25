#ifndef QMLCLIPBOARD_H
#define QMLCLIPBOARD_H

#include "QMLBaseComponent.h"

class MimeDataEntry;

class QMLClipboard : public QQmlComponent, public QMLBaseComponent<QMLClipboard>
{
    Q_OBJECT

    Q_PROPERTY(bool autoTrigger READ autoTrigger WRITE setAutoTrigger)

    public :
        QMLClipboard();

        bool autoTrigger() const;
        void setAutoTrigger(bool);

        Shortcut shortcut() const;
        void setShortcut(const Shortcut &);

        void setIgnoreShortcut(bool);
        void setEnabled(bool);
        void setActivable(bool);

        void activate(MimeDataEntry *, bool);
        Q_SIGNAL void activated(MimeDataEntry * data, bool autoTriggered); // the parameters names will be the same in QML

        Q_INVOKABLE void setText(const QString &);
        Q_INVOKABLE void setData(MimeDataEntry *);
        Q_INVOKABLE void setData(const QVariantMap &);

        Q_INVOKABLE MimeDataEntry * newMime();

    private :
        Q_SLOT void onClipboardChanged(MimeDataEntry *);
        Q_SLOT void onKeyPressed(const Shortcut &, bool);

        bool autoTrigger_;
        bool enabled_;
        bool activable_;
        bool ignoreShortcut_;

        Shortcut shortcut_;
};

#endif // QMLCLIPBOARD_H