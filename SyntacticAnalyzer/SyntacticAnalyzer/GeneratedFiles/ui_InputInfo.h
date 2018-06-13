/********************************************************************************
** Form generated from reading UI file 'InputInfo.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTINFO_H
#define UI_INPUTINFO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputInfo
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *input_edit;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *input_finish;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *InputInfo)
    {
        if (InputInfo->objectName().isEmpty())
            InputInfo->setObjectName(QStringLiteral("InputInfo"));
        InputInfo->resize(280, 299);
        InputInfo->setMaximumSize(QSize(280, 350));
        gridLayout = new QGridLayout(InputInfo);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        input_edit = new QTextEdit(InputInfo);
        input_edit->setObjectName(QStringLiteral("input_edit"));

        verticalLayout_2->addWidget(input_edit);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        input_finish = new QPushButton(InputInfo);
        input_finish->setObjectName(QStringLiteral("input_finish"));

        horizontalLayout->addWidget(input_finish);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        horizontalLayout->setStretch(0, 5);
        horizontalLayout->setStretch(2, 5);

        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(InputInfo);

        QMetaObject::connectSlotsByName(InputInfo);
    } // setupUi

    void retranslateUi(QWidget *InputInfo)
    {
        InputInfo->setWindowTitle(QApplication::translate("InputInfo", "\350\276\223\345\205\245\344\277\241\346\201\257", Q_NULLPTR));
        input_finish->setText(QApplication::translate("InputInfo", "\350\276\223\345\205\245\347\273\223\346\235\237", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class InputInfo: public Ui_InputInfo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTINFO_H
