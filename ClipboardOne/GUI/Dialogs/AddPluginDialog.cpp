#include "stdafx.h"
#include "AddPluginDialog.h"

#include "QML/QMLEnvironment.h"

AddPluginDialog::AddPluginDialog(QWidget * parent) : QDialog(parent),
    ui_(new Ui::UiAddPluginDialog)
{
    ui_->setupUi(this);

    setWindowModality(Qt::WindowModal);

    auto disableLocalGroupBox = [this](bool enable) { ui_->localGroupbox->setChecked(!enable); };
    auto disableWebGroupBox   = [this](bool enable) { ui_->webGroupbox->setChecked(!enable);   };

    QObject::connect(ui_->webGroupbox, &QGroupBox::toggled, disableLocalGroupBox);
    QObject::connect(ui_->localGroupbox, &QGroupBox::toggled, disableWebGroupBox);

    QObject::connect(ui_->localBrowse, &QPushButton::clicked, [this] { onBrowse(); });
}

void AddPluginDialog::onBrowse()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open plugin file", QString(), "plugin files (*.qml)");
    if(!fileName.isEmpty())
        ui_->localUrl->setText(fileName);
}

void AddPluginDialog::accept()
{
    if(ui_->webGroupbox->isChecked() && !ui_->webUrl->text().isEmpty())
        QMLEnvironment::addPlugin(QUrl(ui_->webUrl->text()));
    else if(ui_->localGroupbox->isChecked() && !ui_->localUrl->text().isEmpty())
        QMLEnvironment::addPlugin(QUrl::fromLocalFile(ui_->localUrl->text()));
    QDialog::accept();
}