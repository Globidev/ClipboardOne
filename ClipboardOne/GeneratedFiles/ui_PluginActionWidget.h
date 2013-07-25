/********************************************************************************
** Form generated from reading UI file 'PluginActionWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.1.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINACTIONWIDGET_H
#define UI_PLUGINACTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UiPluginActionWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *enable;
    QToolButton *configure;
    QToolButton *remove;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *UiPluginActionWidget)
    {
        if (UiPluginActionWidget->objectName().isEmpty())
            UiPluginActionWidget->setObjectName(QStringLiteral("UiPluginActionWidget"));
        UiPluginActionWidget->resize(400, 300);
        horizontalLayout = new QHBoxLayout(UiPluginActionWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        enable = new QToolButton(UiPluginActionWidget);
        enable->setObjectName(QStringLiteral("enable"));
        enable->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/PluginEditor/SwitchOn"), QSize(), QIcon::Normal, QIcon::Off);
        enable->setIcon(icon);
        enable->setIconSize(QSize(48, 48));
        enable->setCheckable(false);
        enable->setChecked(false);
        enable->setAutoRaise(false);

        horizontalLayout->addWidget(enable);

        configure = new QToolButton(UiPluginActionWidget);
        configure->setObjectName(QStringLiteral("configure"));
        configure->setEnabled(true);
        configure->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/PluginEditor/Configuration"), QSize(), QIcon::Normal, QIcon::Off);
        configure->setIcon(icon1);
        configure->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(configure);

        remove = new QToolButton(UiPluginActionWidget);
        remove->setObjectName(QStringLiteral("remove"));
        remove->setStyleSheet(QLatin1String(" QToolButton {\n"
"     border: none;\n"
"     background-color: none;\n"
" }"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/PluginEditor/Delete"), QSize(), QIcon::Normal, QIcon::Off);
        remove->setIcon(icon2);
        remove->setIconSize(QSize(32, 32));

        horizontalLayout->addWidget(remove);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(UiPluginActionWidget);

        QMetaObject::connectSlotsByName(UiPluginActionWidget);
    } // setupUi

    void retranslateUi(QWidget *UiPluginActionWidget)
    {
        UiPluginActionWidget->setWindowTitle(QApplication::translate("UiPluginActionWidget", "Form", 0));
#ifndef QT_NO_TOOLTIP
        enable->setToolTip(QApplication::translate("UiPluginActionWidget", "Enable or Disable Plug-in", 0));
#endif // QT_NO_TOOLTIP
        enable->setText(QString());
#ifndef QT_NO_TOOLTIP
        configure->setToolTip(QApplication::translate("UiPluginActionWidget", "Configure Plug-in", 0));
#endif // QT_NO_TOOLTIP
        configure->setText(QString());
#ifndef QT_NO_TOOLTIP
        remove->setToolTip(QApplication::translate("UiPluginActionWidget", "Remove Plug-in", 0));
#endif // QT_NO_TOOLTIP
        remove->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UiPluginActionWidget: public Ui_UiPluginActionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINACTIONWIDGET_H
