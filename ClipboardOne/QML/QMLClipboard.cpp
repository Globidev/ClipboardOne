#include "stdafx.h"
#include "QMLClipboard.h"

#include "Core/ClipboardWatcher.h"
#include "Core/MimeDataEntry.h"

#include "Core/KeyLogger.h"

const char * QMLClipboard::package = "GlobiPlugin";
const int QMLClipboard::majorVersion = 1;
const int QMLClipboard::minorVersion = 0;
const char * QMLClipboard::qmlName = "Clipboard";

QMLClipboard::QMLClipboard() : QQmlComponent(),
    ignoreShortcut_(false),
    enabled_(true),
    activable_(true)
{
    QObject::connect(&ClipboardWatcher::instance(), &ClipboardWatcher::clipboardChanged,
                     this, &QMLClipboard::onClipboardChanged);

    QObject::connect(&KeyLogger::instance(), &KeyLogger::sequence,
                     this, &QMLClipboard::onKeyPressed);
}

bool QMLClipboard::autoTrigger() const
{
    return autoTrigger_;
}

void QMLClipboard::setAutoTrigger(bool autoTrigger)
{
    autoTrigger_ = autoTrigger;
}

Shortcut QMLClipboard::shortcut() const
{
    return shortcut_;
}

void QMLClipboard::setShortcut(const Shortcut & shortcut)
{
    shortcut_ = shortcut;
}

void QMLClipboard::setIgnoreShortcut(bool ignore)
{
    ignoreShortcut_ = ignore;
}

void QMLClipboard::setEnabled(bool enabled)
{
    enabled_ = enabled;
}

void QMLClipboard::setActivable(bool activable)
{
    activable_ = activable;
}

void QMLClipboard::setText(const QString & text)
{
    ClipboardWatcher::ClipboardSignalBlocker lock;
    QApplication::clipboard()->setText(text);
}

void QMLClipboard::setData(MimeDataEntry * data)
{
    ClipboardWatcher::ClipboardSignalBlocker lock;
    QApplication::clipboard()->setMimeData(data);
}

void QMLClipboard::setData(const QVariantMap & dataMap)
{
    auto mimeData = new MimeDataEntry;
    mimeData->setData(dataMap);
    setData(mimeData);
}

MimeDataEntry * QMLClipboard::newMime()
{
    return new MimeDataEntry;
}

void QMLClipboard::activate(MimeDataEntry * entry, bool fromAutoTrigger)
{
    if(enabled_) Q_EMIT activated(entry, fromAutoTrigger);
}

void QMLClipboard::onClipboardChanged(MimeDataEntry * entry)
{
    if(autoTrigger_) activate(entry, true);
}

void QMLClipboard::onKeyPressed(const Shortcut & shortcut, bool pressed)
{
    if(!ignoreShortcut_ && activable_ && pressed && shortcut == shortcut_)
        activate(ClipboardWatcher::lastEntry(), false);
}