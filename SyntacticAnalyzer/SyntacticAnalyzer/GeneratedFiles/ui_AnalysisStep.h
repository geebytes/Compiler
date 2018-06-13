/********************************************************************************
** Form generated from reading UI file 'AnalysisStep.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSISSTEP_H
#define UI_ANALYSISSTEP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalysisStep
{
public:
    QGridLayout *gridLayout;
    QTableView *setp_table;

    void setupUi(QWidget *AnalysisStep)
    {
        if (AnalysisStep->objectName().isEmpty())
            AnalysisStep->setObjectName(QStringLiteral("AnalysisStep"));
        AnalysisStep->resize(811, 800);
        gridLayout = new QGridLayout(AnalysisStep);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        setp_table = new QTableView(AnalysisStep);
        setp_table->setObjectName(QStringLiteral("setp_table"));
        setp_table->setStyleSheet(QLatin1String("QHeaderView::section {\n"
"    color: white;\n"
"    background-color: rgb(0, 170, 255);\n"
"    border: 5px solid #f6f7fa;\n"
"    border-radius:0px;\n"
"    border-color: rgb(0, 170, 255);\n"
"} "));
        setp_table->horizontalHeader()->setCascadingSectionResizes(false);
        setp_table->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        setp_table->horizontalHeader()->setStretchLastSection(false);
        setp_table->verticalHeader()->setVisible(true);
        setp_table->verticalHeader()->setCascadingSectionResizes(false);
        setp_table->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        gridLayout->addWidget(setp_table, 0, 0, 1, 1);


        retranslateUi(AnalysisStep);

        QMetaObject::connectSlotsByName(AnalysisStep);
    } // setupUi

    void retranslateUi(QWidget *AnalysisStep)
    {
        AnalysisStep->setWindowTitle(QApplication::translate("AnalysisStep", "\345\210\206\346\236\220\350\277\207\347\250\213", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AnalysisStep: public Ui_AnalysisStep {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSISSTEP_H
