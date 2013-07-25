#ifndef CLIPBOARDWATCHER_H
#define CLIPBOARDWATCHER_H

class RedisClient;
class MimeDataEntry;

class ClipboardWatcher : public QObject, boost::noncopyable
{
    Q_OBJECT
    typedef std::function<void (MimeDataEntry *)> Callback;

    public :
        struct ClipboardSignalBlocker
        {
            ClipboardSignalBlocker();
            ~ClipboardSignalBlocker();
        };

        static ClipboardWatcher & instance();

        static MimeDataEntry * lastEntry();
        void restore(quint32);

        Q_SIGNAL void clipboardChanged(MimeDataEntry *);

    private :
        ClipboardWatcher();

        Q_SLOT void onDataChanged();

        std::unique_ptr<RedisClient> clipboardClient_;

        quint32 count_;

        std::unique_ptr<MimeDataEntry> lastEntry_;
};

#endif // CLIPBOARDWATCHER_H