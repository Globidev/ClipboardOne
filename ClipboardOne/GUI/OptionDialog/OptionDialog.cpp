#include "stdafx.h"
#include "OptionDialog.h"

#include "Core/Settings.h"
#include "GUI/DynamicImageEngine.h"

OptionDialog::OptionDialog(QWidget * parent) : QDialog(parent),
    ui_(new Ui::UiOptionDialog),
    colorDialog_(new QColorDialog(this))
{
    ui_->setupUi(this);

    ui_->startup->setChecked(Settings::value<bool>("startup", "Options", false));
    auto color = Settings::value<QColor>("mask_color", "Ui", Qt::black);
    ui_->iconColor->setStyleSheet(BACKGROUND_STYLE_SHEET(color));
    colorDialog_->setCurrentColor(color);

    QObject::connect(ui_->startup, &QCheckBox::toggled,
                     this, &OptionDialog::onStartupToggled);

    QObject::connect(ui_->iconColor, &QPushButton::clicked,
                     colorDialog_.get(), &QDialog::show);

    QObject::connect(colorDialog_.get(), &QColorDialog::accepted,
                     this, &OptionDialog::onIconColorChanged);

    QObject::connect(&DynamicImageEngine::instance(), &DynamicImageEngine::maskChanged,
                    [this] { setWindowIcon(DynamicImageEngine::colored(OPTION_DIALOG_ICON)); });
}

void OptionDialog::forceShow()
{
    forceShowWindow(this);
}

void OptionDialog::onStartupToggled(bool checked)
{
    Settings::setValue("startup", checked, "Options");
    QStringList args;
    if(!checked)
        args << "/r";
    args << QDir::toNativeSeparators(QApplication::applicationFilePath());
    startProcessElevated("startup", args);
}

void OptionDialog::onIconColorChanged()
{
    ui_->iconColor->setStyleSheet(BACKGROUND_STYLE_SHEET(colorDialog_->currentColor()));
    DynamicImageEngine::setMaskColor(colorDialog_->currentColor());
}