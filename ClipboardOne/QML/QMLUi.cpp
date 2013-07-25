#include "stdafx.h"
#include "QMLUi.h"

#include "Network/NetworkAccessManager.h"
#include "Network/NetworkHTTPReply.h"

const char * QMLUi::package = "GlobiPlugin";
const int QMLUi::majorVersion = 1;
const int QMLUi::minorVersion = 0;
const char * QMLUi::qmlName = "Ui";

QMLUi::QMLUi() : QQmlComponent(),
    isWebUi_(true), uiElements_(new QQmlPropertyMap)
{
}

QString QMLUi::file() const
{
    return uiFileName_;
}

void QMLUi::setFile(const QString & uifileName)
{
    uiFileName_ = uifileName;
    loadUi();
}

bool QMLUi::isWebUi() const
{
    return isWebUi_;
}

void QMLUi::setWebUi(bool webUi)
{
    isWebUi_ = webUi;
}

QWidget * QMLUi::loadedUi()
{
    return loadedUi_.get();
}

QQmlPropertyMap * QMLUi::uiElements() const
{
    return uiElements_.get();
}

void QMLUi::loadUi()
{
    QUiLoader uiLoader;

    std::unique_ptr<QIODevice> uiDevice;
    if(isWebUi_)
    {
        QNetworkAccessManager manager;
        QNetworkRequest request(uiFileName_);
        auto reply = synchronousCall(5000, 
                                     &QNetworkReply::finished,
                                     &QNetworkAccessManager::get,
                                     &manager, request);
        reply->setParent(nullptr);
        uiDevice.reset(reply);
    }
    else
        uiDevice.reset(new QFile(uiFileName_));
    loadedUi_.reset(uiLoader.load(uiDevice.get()));

    if(loadedUi_)
        for(auto object : loadedUi_->children()) 
            addUiElement(object);
}

void QMLUi::addUiElement(QObject * object)
{
    uiElements_->insert(object->objectName(), QVariant::fromValue(object));
    for(auto child : object->children()) addUiElement(child);
}

void QMLUi::show()
{
    if(loadedUi_) loadedUi_->show();
}