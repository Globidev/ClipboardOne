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

        QString appId_;
        
        QLocalSocket appSocket_, * otherAppSocket_;
        QLocalServer appServer_;
        QTextStream outStream_;
        bool isAlreadyRunning_;
};

#endif // GLOBISINGLEAPPLICATION_H