///=================================================================================================
/// \file InputInfo.h
///
/// \brief 声明用于对输入窗口的输入信息处理的类
///=================================================================================================

#pragma once

#include <QWidget>
#include "ui_InputInfo.h"
#include <vector>
using namespace std;
class InputInfo : public QWidget {
    Q_OBJECT

  public:
    InputInfo(QWidget *parent = Q_NULLPTR);
    vector<string> get_info();
    ~InputInfo();
  public slots:
    void input_finish();
  signals:
    void finish();
  private:
    Ui::InputInfo ui;
    vector<string> info;
};
