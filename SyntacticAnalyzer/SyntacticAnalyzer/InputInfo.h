///=================================================================================================
/// \file InputInfo.h
///
/// \brief �������ڶ����봰�ڵ�������Ϣ�������
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
