#include "stdafx.h"
#include "ClipboardWatcher.h"

#include "MimeDataEntry.h"
#include "Redis/RedisClient.h"

ClipboardWatcher::ClipboardWatcher() : 
    clipboardClient_(new RedisClient),
    count_(0),
    lastEntry_(new MimeDataEntry(QApplication::clipboard()->mimeData()))
{
    // Forced to use queued connection for the clipboard to be changed by plugins ...
    QObject::connect(QApplication::clipboard(), &QClipboard::dataChanged,
                     this, &ClipboardWatcher::onDataChanged,
                     Qt::QueuedConnection);
}

ClipboardWatcher & ClipboardWatcher::instance()
{
    static ClipboardWatcher clipboardWatcher;
    return clipboardWatcher;
}

void ClipboardWatcher::restore(quint32 index)
{
    MimeDataEntry * entry = new MimeDataEntry;
    QByteArray serializedData = clipboardClient_->get(REDIS_CLIPBOARD_ENTRY_KEY(index));
    QDataStream stream(serializedData);
    stream >> *entry;
    
    ClipboardSignalBlocker lock;
    QApplication::clipboard()->setMimeData(entry);
}

MimeDataEntry * ClipboardWatcher::lastEntry()
{
    return instance().lastEntry_.get();
}

ClipboardWatcher::ClipboardSignalBlocker::ClipboardSignalBlocker()
{
    QApplication::clipboard()->blockSignals(true);
}

ClipboardWatcher::ClipboardSignalBlocker::~ClipboardSignalBlocker()
{
    QApplication::clipboard()->blockSignals(false);
}

void ClipboardWatcher::onDataChanged()
{
    lastEntry_.reset(new MimeDataEntry(QApplication::clipboard()->mimeData()));
    clipboardClient_->set(REDIS_CLIPBOARD_ENTRY_KEY(count_ ++), lastEntry_->serialize());
    Q_EMIT clipboardChanged(lastEntry());
}