/********************************************************************************
** Form generated from reading UI file 'Config.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Config
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *garmmars_path;
    QPushButton *open_garmms;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *terminals_path;
    QPushButton *open_terminals;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *ok;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Config)
    {
        if (Config->objectName().isEmpty())
            Config->setObjectName(QStringLiteral("Config"));
        Config->resize(384, 130);
        Config->setMaximumSize(QSize(385, 130));
        gridLayout = new QGridLayout(Config);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(Config);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        garmmars_path = new QLineEdit(Config);
        garmmars_path->setObjectName(QStringLiteral("garmmars_path"));

        horizontalLayout->addWidget(garmmars_path);

        open_garmms = new QPushButton(Config);
        open_garmms->setObjectName(QStringLiteral("open_garmms"));

        horizontalLayout->addWidget(open_garmms);

        horizontalLayout->setStretch(1, 2);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(Config);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        terminals_path = new QLineEdit(Config);
        terminals_path->setObjectName(QStringLiteral("terminals_path"));

        horizontalLayout_2->addWidget(terminals_path);

        open_terminals = new QPushButton(Config);
        open_terminals->setObjectName(QStringLiteral("open_terminals"));

        horizontalLayout_2->addWidget(open_terminals);

        horizontalLayout_2->setStretch(1, 4);

        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        ok = new QPushButton(Config);
        ok->setObjectName(QStringLiteral("ok"));

        horizontalLayout_3->addWidget(ok);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(2, 2);

        verticalLayout_2->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(Config);

        QMetaObject::connectSlotsByName(Config);
    } // setupUi

    void retranslateUi(QWidget *Config)
    {
        Config->setWindowTitle(QApplication::translate("Config", "\351\205\215\347\275\256", Q_NULLPTR));
        label->setText(QApplication::translate("Config", "\346\226\207\346\263\225\346\226\207\344\273\266\350\267\257\345\276\204", Q_NULLPTR));
        open_garmms->setText(QApplication::translate("Config", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        label_2->setText(QApplication::translate("Config", "\347\273\210\347\273\223\347\254\246\351\233\206\345\220\210\346\226\207\344\273\266\350\267\257\345\276\204", Q_NULLPTR));
        open_terminals->setText(QApplication::translate("Config", "\346\211\223\345\274\200\346\226\207\344\273\266", Q_NULLPTR));
        ok->setText(QApplication::translate("Config", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Config: public Ui_Config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
