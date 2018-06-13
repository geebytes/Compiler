/********************************************************************************
** Form generated from reading UI file 'SyntacticAnalyzer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SYNTACTICANALYZER_H
#define UI_SYNTACTICANALYZER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SyntacticAnalyzerClass
{
public:
    QAction *open_exp;
    QAction *check;
    QAction *input_grammars;
    QAction *input_treminal;
    QAction *input_exp;
    QAction *read_settings;
    QWidget *centralWidget;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableView *lastView;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QTextEdit *input_text;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_2;
    QVBoxLayout *output_verticalLayout;
    QTextBrowser *output_text;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SyntacticAnalyzerClass)
    {
        if (SyntacticAnalyzerClass->objectName().isEmpty())
            SyntacticAnalyzerClass->setObjectName(QStringLiteral("SyntacticAnalyzerClass"));
        SyntacticAnalyzerClass->resize(1017, 490);
        open_exp = new QAction(SyntacticAnalyzerClass);
        open_exp->setObjectName(QStringLiteral("open_exp"));
        check = new QAction(SyntacticAnalyzerClass);
        check->setObjectName(QStringLiteral("check"));
        input_grammars = new QAction(SyntacticAnalyzerClass);
        input_grammars->setObjectName(QStringLiteral("input_grammars"));
        input_treminal = new QAction(SyntacticAnalyzerClass);
        input_treminal->setObjectName(QStringLiteral("input_treminal"));
        input_exp = new QAction(SyntacticAnalyzerClass);
        input_exp->setObjectName(QStringLiteral("input_exp"));
        read_settings = new QAction(SyntacticAnalyzerClass);
        read_settings->setObjectName(QStringLiteral("read_settings"));
        centralWidget = new QWidget(SyntacticAnalyzerClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_6 = new QGridLayout(centralWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lastView = new QTableView(groupBox);
        lastView->setObjectName(QStringLiteral("lastView"));
        lastView->setStyleSheet(QLatin1String("QHeaderView::section {\n"
"    color: white;\n"
"    background-color: rgb(0, 170, 255);\n"
"    border: 5px solid #f6f7fa;\n"
"    border-radius:0px;\n"
"    border-color: rgb(0, 170, 255);\n"
"} "));
        lastView->horizontalHeader()->setVisible(true);
        lastView->horizontalHeader()->setCascadingSectionResizes(true);
        lastView->horizontalHeader()->setDefaultSectionSize(100);
        lastView->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        lastView->horizontalHeader()->setStretchLastSection(true);
        lastView->verticalHeader()->setCascadingSectionResizes(true);
        lastView->verticalHeader()->setProperty("showSortIndicator", QVariant(true));
        lastView->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(lastView, 0, 0, 1, 1);


        verticalLayout_2->addWidget(groupBox);


        horizontalLayout->addLayout(verticalLayout_2);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        tableView = new QTableView(groupBox_3);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setStyleSheet(QLatin1String("QHeaderView::section {\n"
"    color: white;\n"
"    background-color: rgb(0, 170, 255);\n"
"    border: 5px solid #f6f7fa;\n"
"    border-radius:0px;\n"
"    border-color: rgb(0, 170, 255);\n"
"} "));

        gridLayout_3->addWidget(tableView, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_3);


        horizontalLayout_2->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        input_text = new QTextEdit(groupBox_4);
        input_text->setObjectName(QStringLiteral("input_text"));
        input_text->setTextInteractionFlags(Qt::TextSelectableByKeyboard|Qt::TextSelectableByMouse);

        gridLayout_4->addWidget(input_text, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout_2 = new QGridLayout(groupBox_5);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        output_verticalLayout = new QVBoxLayout();
        output_verticalLayout->setSpacing(6);
        output_verticalLayout->setObjectName(QStringLiteral("output_verticalLayout"));
        output_text = new QTextBrowser(groupBox_5);
        output_text->setObjectName(QStringLiteral("output_text"));

        output_verticalLayout->addWidget(output_text);


        gridLayout_2->addLayout(output_verticalLayout, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_5);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 5);

        gridLayout_6->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        SyntacticAnalyzerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SyntacticAnalyzerClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1017, 26));
        SyntacticAnalyzerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SyntacticAnalyzerClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SyntacticAnalyzerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SyntacticAnalyzerClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SyntacticAnalyzerClass->setStatusBar(statusBar);

        mainToolBar->addAction(open_exp);
        mainToolBar->addAction(check);
        mainToolBar->addAction(input_grammars);
        mainToolBar->addAction(input_treminal);
        mainToolBar->addAction(input_exp);
        mainToolBar->addAction(read_settings);

        retranslateUi(SyntacticAnalyzerClass);

        QMetaObject::connectSlotsByName(SyntacticAnalyzerClass);
    } // setupUi

    void retranslateUi(QMainWindow *SyntacticAnalyzerClass)
    {
        SyntacticAnalyzerClass->setWindowTitle(QApplication::translate("SyntacticAnalyzerClass", "\347\256\227\347\254\246\344\274\230\345\205\210\350\257\255\346\263\225\345\210\206\346\236\220\345\231\250", Q_NULLPTR));
        open_exp->setText(QApplication::translate("SyntacticAnalyzerClass", "\345\257\274\345\205\245\350\241\250\350\276\276\345\274\217", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        open_exp->setToolTip(QApplication::translate("SyntacticAnalyzerClass", "\345\257\274\345\205\245\350\241\250\350\276\276\345\274\217", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        check->setText(QApplication::translate("SyntacticAnalyzerClass", "\346\243\200\346\237\245", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        check->setToolTip(QApplication::translate("SyntacticAnalyzerClass", "\346\243\200\346\237\245", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        input_grammars->setText(QApplication::translate("SyntacticAnalyzerClass", "\350\276\223\345\205\245\346\226\207\346\263\225", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        input_grammars->setToolTip(QApplication::translate("SyntacticAnalyzerClass", "\350\276\223\345\205\245\346\226\207\346\263\225", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        input_treminal->setText(QApplication::translate("SyntacticAnalyzerClass", "\350\276\223\345\205\245\347\273\210\347\273\223\347\254\246", Q_NULLPTR));
        input_exp->setText(QApplication::translate("SyntacticAnalyzerClass", "\350\276\223\345\205\245\350\241\250\350\276\276\345\274\217", Q_NULLPTR));
        read_settings->setText(QApplication::translate("SyntacticAnalyzerClass", "\351\205\215\347\275\256", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        read_settings->setToolTip(QApplication::translate("SyntacticAnalyzerClass", "\351\205\215\347\275\256", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        groupBox->setTitle(QApplication::translate("SyntacticAnalyzerClass", "FIRST\345\222\214LAST\351\233\206", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("SyntacticAnalyzerClass", "\344\274\230\345\205\210\345\205\263\347\263\273\350\241\250", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("SyntacticAnalyzerClass", "\350\276\223\345\205\245\351\241\271", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("SyntacticAnalyzerClass", "\346\243\200\346\265\213\347\273\223\346\236\234", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SyntacticAnalyzerClass: public Ui_SyntacticAnalyzerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SYNTACTICANALYZER_H
