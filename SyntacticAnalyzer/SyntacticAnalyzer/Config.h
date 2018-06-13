///=================================================================================================
/// \file Config.h
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
#include "ui_Config.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
class Config : public QWidget {
    Q_OBJECT

  public:
    Config(QWidget *parent = Q_NULLPTR);
    void connect_signal_slot();
    QString get_grammars_path();
    QString get_terminal_path();
    ~Config();
  private slots:
    void open_terminal();
    void open_grammars();
    void ok_btn();
    void open_file(int file_type);
  signals:
    void teminanls_file(QString);
    void grammars_file(QString);
    void file_type_send(int file_type);
    void finish();

  private:
    Ui::Config ui;
    QString teminanls_path;
    QString grammars_path;
    void read_setting();
    void wirte_setting();
};
