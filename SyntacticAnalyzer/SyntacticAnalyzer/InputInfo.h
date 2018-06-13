///=================================================================================================
/// \file InputInfo.h
/// \date 2018/06/13
///
/// \author qinzhonghe
///
/// \email  qinzhonghe96@163.com
///
/// \brief 声明用于配置信息读写的类
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
