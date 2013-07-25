/********************************************************************************
** Form generated from reading UI file 'AddPluginDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDPLUGINDIALOG_H
#define UI_ADDPLUGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UiAddPluginDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *webGroupbox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *webUrl;
    QGroupBox *localGroupbox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *localUrl;
    QToolButton *localBrowse;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QToolButton *ok;
    QToolButton *cancel;

    void setupUi(QDialog *UiAddPluginDialog)
    {
        if (UiAddPluginDialog->objectName().isEmpty())
            UiAddPluginDialog->setObjectName(QStringLiteral("UiAddPluginDialog"));
        UiAddPluginDialog->resize(400, 182);
        UiAddPluginDialog->setStyleSheet(QLatin1String(".QDialog {\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(UiAddPluginDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        webGroupbox = new QGroupBox(UiAddPluginDialog);
        webGroupbox->setObjectName(QStringLiteral("webGroupbox"));
        webGroupbox->setStyleSheet(QLatin1String("QGroupBox::title {\n"
"	image: url(:/AddPluginDialog/Web);\n"
"	image-position : right;\n"
"}"));
        webGroupbox->setFlat(false);
        webGroupbox->setCheckable(true);
        verticalLayout_2 = new QVBoxLayout(webGroupbox);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(webGroupbox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMinimumSize(QSize(75, 0));

        horizontalLayout_2->addWidget(label_2);

        webUrl = new QLineEdit(webGroupbox);
        webUrl->setObjectName(QStringLiteral("webUrl"));

        horizontalLayout_2->addWidget(webUrl);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(webGroupbox);

        localGroupbox = new QGroupBox(UiAddPluginDialog);
        localGroupbox->setObjectName(QStringLiteral("localGroupbox"));
        localGroupbox->setStyleSheet(QLatin1String("QGroupBox::title\n"
"{\n"
"	image: url(:/AddPluginDialog/Folder);\n"
"	image-position : right;\n"
"}"));
        localGroupbox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        localGroupbox->setFlat(false);
        localGroupbox->setCheckable(true);
        localGroupbox->setChecked(false);
        verticalLayout = new QVBoxLayout(localGroupbox);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(localGroupbox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(75, 0));

        horizontalLayout->addWidget(label);

        localUrl = new QLineEdit(localGroupbox);
        localUrl->setObjectName(QStringLiteral("localUrl"));

        horizontalLayout->addWidget(localUrl);

        localBrowse = new QToolButton(localGroupbox);
        localBrowse->setObjectName(QStringLiteral("localBrowse"));
        localBrowse->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/AddPluginDialog/Browse"), QSize(), QIcon::Normal, QIcon::Off);
        localBrowse->setIcon(icon);
        localBrowse->setIconSize(QSize(20, 20));
        localBrowse->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        localBrowse->setAutoRaise(true);

        horizontalLayout->addWidget(localBrowse);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(localGroupbox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        ok = new QToolButton(UiAddPluginDialog);
        ok->setObjectName(QStringLiteral("ok"));
        ok->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/AddPluginDialog/Ok"), QSize(), QIcon::Normal, QIcon::Off);
        ok->setIcon(icon1);
        ok->setIconSize(QSize(20, 20));
        ok->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        ok->setAutoRaise(false);

        hboxLayout->addWidget(ok);

        cancel = new QToolButton(UiAddPluginDialog);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/AddPluginDialog/Cancel"), QSize(), QIcon::Normal, QIcon::Off);
        cancel->setIcon(icon2);
        cancel->setIconSize(QSize(20, 20));
        cancel->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        cancel->setAutoRaise(false);

        hboxLayout->addWidget(cancel);


        verticalLayout_3->addLayout(hboxLayout);

        QWidget::setTabOrder(webUrl, localGroupbox);
        QWidget::setTabOrder(localGroupbox, localUrl);
        QWidget::setTabOrder(localUrl, localBrowse);
        QWidget::setTabOrder(localBrowse, ok);
        QWidget::setTabOrder(ok, cancel);
        QWidget::setTabOrder(cancel, webGroupbox);

        retranslateUi(UiAddPluginDialog);
        QObject::connect(ok, SIGNAL(clicked()), UiAddPluginDialog, SLOT(accept()));
        QObject::connect(cancel, SIGNAL(clicked()), UiAddPluginDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(UiAddPluginDialog);
    } // setupUi

    void retranslateUi(QDialog *UiAddPluginDialog)
    {
        UiAddPluginDialog->setWindowTitle(QApplication::translate("UiAddPluginDialog", "Add a new Plug-in", 0));
        webGroupbox->setTitle(QApplication::translate("UiAddPluginDialog", "Web plugin     ", 0));
        label_2->setText(QApplication::translate("UiAddPluginDialog", "Plugin url :", 0));
        localGroupbox->setTitle(QApplication::translate("UiAddPluginDialog", "Local plugin     ", 0));
        label->setText(QApplication::translate("UiAddPluginDialog", "Plugin path :", 0));
        localBrowse->setText(QApplication::translate("UiAddPluginDialog", "Browse...", 0));
        ok->setText(QApplication::translate("UiAddPluginDialog", "Ok", 0));
        cancel->setText(QApplication::translate("UiAddPluginDialog", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class UiAddPluginDialog: public Ui_UiAddPluginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDPLUGINDIALOG_H
