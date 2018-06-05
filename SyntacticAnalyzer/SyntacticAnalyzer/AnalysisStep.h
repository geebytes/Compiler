///=================================================================================================
/// \file AnalysisStep.h
///
/// \brief 声明分析过程显示界面处理的类
///=================================================================================================

#pragma once

#include <QWidget>
#include "ui_AnalysisStep.h"
#include "TableModel.h"
#include <vector>
#include <map>
#include <string>
#include <QDebug>
using namespace std;
class AnalysisStep : public QWidget {
    Q_OBJECT

  public:
    AnalysisStep(QWidget *parent = Q_NULLPTR);
    void add_step(map<int, vector<string>> setp);
    void clear_table();
    ~AnalysisStep();

  private:
    Ui::AnalysisStep ui;
    TableModel *setp_model;
    void init_table();
};
