#ifndef GLOBISINGLEAPPLICATION_H
#define GLOBISINGLEAPPLICATION_H

class GlobiSingleApplication : public QApplication
{
    Q_OBJECT

    public:
        GlobiSingleApplication(int &, char **, const QString &);
        virtual ~GlobiSingleApplication();

        bool isAlreadyRunning() const;
        void sendMessage(const QString &);

        Q_SIGNAL void messageRceived(const QString &);

    private:
        Q_SLOT void onNewConnection();
        Q_SLOT void onReadyRead();

        QString _appId;
        
        QLocalSocket _appSocket, * _otherAppSocket;
        QLocalServer _appServer;
        QTextStream _outStream;
        bool _isAlreadyRunning;
};

#endif // GLOBISINGLEAPPLICATION_H