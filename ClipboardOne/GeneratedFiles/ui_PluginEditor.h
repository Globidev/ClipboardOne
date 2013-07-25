/********************************************************************************
** Form generated from reading UI file 'PluginEditor.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINEDITOR_H
#define UI_PLUGINEDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiPluginEditor
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *addPlugin;
    QToolButton *showLogs;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *UiPluginEditor)
    {
        if (UiPluginEditor->objectName().isEmpty())
            UiPluginEditor->setObjectName(QStringLiteral("UiPluginEditor"));
        UiPluginEditor->resize(800, 450);
        UiPluginEditor->setStyleSheet(QLatin1String(".QWidget {\n"
"	background-color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(UiPluginEditor);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        addPlugin = new QToolButton(UiPluginEditor);
        addPlugin->setObjectName(QStringLiteral("addPlugin"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(addPlugin->sizePolicy().hasHeightForWidth());
        addPlugin->setSizePolicy(sizePolicy);
        addPlugin->setMinimumSize(QSize(48, 54));
        addPlugin->setMaximumSize(QSize(48, 54));
        addPlugin->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/PluginEditor/Add"), QSize(), QIcon::Normal, QIcon::Off);
        addPlugin->setIcon(icon);
        addPlugin->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(addPlugin);

        showLogs = new QToolButton(UiPluginEditor);
        showLogs->setObjectName(QStringLiteral("showLogs"));
        sizePolicy.setHeightForWidth(showLogs->sizePolicy().hasHeightForWidth());
        showLogs->setSizePolicy(sizePolicy);
        showLogs->setMinimumSize(QSize(48, 54));
        showLogs->setMaximumSize(QSize(48, 54));
        showLogs->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/PluginEditor/Logs"), QSize(), QIcon::Normal, QIcon::Off);
        showLogs->setIcon(icon1);
        showLogs->setIconSize(QSize(48, 48));

        horizontalLayout->addWidget(showLogs);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(UiPluginEditor);

        QMetaObject::connectSlotsByName(UiPluginEditor);
    } // setupUi

    void retranslateUi(QWidget *UiPluginEditor)
    {
        UiPluginEditor->setWindowTitle(QApplication::translate("UiPluginEditor", "Manage Plug-ins", 0));
#ifndef QT_NO_TOOLTIP
        addPlugin->setToolTip(QApplication::translate("UiPluginEditor", "Add Plug-in", 0));
#endif // QT_NO_TOOLTIP
        addPlugin->setText(QString());
#ifndef QT_NO_TOOLTIP
        showLogs->setToolTip(QApplication::translate("UiPluginEditor", "Show logs", 0));
#endif // QT_NO_TOOLTIP
        showLogs->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UiPluginEditor: public Ui_UiPluginEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINEDITOR_H
