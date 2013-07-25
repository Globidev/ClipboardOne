/********************************************************************************
** Form generated from reading UI file 'RemovePluginDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOVEPLUGINDIALOG_H
#define UI_REMOVEPLUGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiRemovePluginDialog
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QGridLayout *gridLayout;
    QToolButton *icon;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label;
    QCheckBox *removeSettings;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QToolButton *okButton;
    QToolButton *cancelButton;

    void setupUi(QDialog *UiRemovePluginDialog)
    {
        if (UiRemovePluginDialog->objectName().isEmpty())
            UiRemovePluginDialog->setObjectName(QStringLiteral("UiRemovePluginDialog"));
        UiRemovePluginDialog->resize(406, 149);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(UiRemovePluginDialog->sizePolicy().hasHeightForWidth());
        UiRemovePluginDialog->setSizePolicy(sizePolicy);
        UiRemovePluginDialog->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        verticalLayout = new QVBoxLayout(UiRemovePluginDialog);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget = new QWidget(UiRemovePluginDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        icon = new QToolButton(widget);
        icon->setObjectName(QStringLiteral("icon"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(48);
        sizePolicy1.setVerticalStretch(48);
        sizePolicy1.setHeightForWidth(icon->sizePolicy().hasHeightForWidth());
        icon->setSizePolicy(sizePolicy1);
        icon->setMinimumSize(QSize(48, 48));
        icon->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Dialogs/QuestionMark"), QSize(), QIcon::Normal, QIcon::Off);
        icon->setIcon(icon1);
        icon->setIconSize(QSize(48, 48));

        gridLayout->addWidget(icon, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(75);
        font.setStrikeOut(false);
        label->setFont(font);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 2, 1, 1);

        removeSettings = new QCheckBox(widget);
        removeSettings->setObjectName(QStringLiteral("removeSettings"));
        removeSettings->setChecked(false);

        gridLayout->addWidget(removeSettings, 1, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 3, 1, 1);


        verticalLayout->addWidget(widget);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QToolButton(UiRemovePluginDialog);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/AddPluginDialog/Ok"), QSize(), QIcon::Normal, QIcon::Off);
        okButton->setIcon(icon2);
        okButton->setIconSize(QSize(20, 20));
        okButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        hboxLayout->addWidget(okButton);

        cancelButton = new QToolButton(UiRemovePluginDialog);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/AddPluginDialog/Cancel"), QSize(), QIcon::Normal, QIcon::Off);
        cancelButton->setIcon(icon3);
        cancelButton->setIconSize(QSize(20, 20));
        cancelButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(UiRemovePluginDialog);
        QObject::connect(okButton, SIGNAL(clicked()), UiRemovePluginDialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), UiRemovePluginDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UiRemovePluginDialog);
    } // setupUi

    void retranslateUi(QDialog *UiRemovePluginDialog)
    {
        UiRemovePluginDialog->setWindowTitle(QApplication::translate("UiRemovePluginDialog", "Remove Plug-in", 0));
        icon->setText(QApplication::translate("UiRemovePluginDialog", "PushButton", 0));
        label->setText(QApplication::translate("UiRemovePluginDialog", "Are you sure you want to remove\n"
"%1 ?", 0));
        removeSettings->setText(QApplication::translate("UiRemovePluginDialog", "Remove settings", 0));
        okButton->setText(QApplication::translate("UiRemovePluginDialog", "OK", 0));
        cancelButton->setText(QApplication::translate("UiRemovePluginDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class UiRemovePluginDialog: public Ui_UiRemovePluginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOVEPLUGINDIALOG_H
