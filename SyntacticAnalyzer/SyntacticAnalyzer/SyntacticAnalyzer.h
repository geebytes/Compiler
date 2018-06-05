///=================================================================================================
/// \file SyntacticAnalyzer.h
///
/// \brief 声明算符优先分析器GUI逻辑处理的类
/// \date 2018/6/5
///=================================================================================================

#ifndef SYNTACTICANALYZER_H
#define SYNTACTICANALYZER_H
#include <QtWidgets/QMainWindow>
#include "ui_SyntacticAnalyzer.h"
#include "ExpressionCheck.h"
#include "InputInfo.h"
#include "Config.h"
#include "AnalysisStep.h"
#include <set>
#include <vector>
#include <string>
#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include "TableModel.h"
#include  <fstream>
#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include"boost/format.hpp"
#include <QTextStream>
#include <QTextDocument>
#include <QTextCursor>
#include <QDebug>
#include <QUrlQuery>
#include <QMessageBox>
using namespace std;
class SyntacticAnalyzer : public QMainWindow {
    Q_OBJECT

  public:
    SyntacticAnalyzer(QWidget *parent = Q_NULLPTR);
    ~SyntacticAnalyzer();

  private slots :
    //从文件打开表达式
    void open_expression();

    //打开配置窗口
    void open_setting();

    //开始检查表达式
    void check_btn();

    //从配置项接收终结符集合的文件路径
    void rev_terminal_path(QString);

    //从配置项接收文法的文件路径
    void rev_grammars_path(QString);

    //关闭配置窗口
    void close_cfg();

    //更新信息
    void update_info();

    //从输入窗口获取输入信息
    void input_info(int input_type);

    //输入完成响应
    void input_finish();

    //输入文法按钮响应函数
    void input_grammars();

    //输入终结符按钮响应函数
    void input_terminals();

    //输入表达式按钮响应函数
    void input_exp();

    //更新输入项
    void update_input();

    //显示某条表达式的分析过程
    void show_step(const QUrl &link);
  signals:
    //发送输入数据的类型
    void send_input_type(int input_type);

  private:
    Ui::SyntacticAnalyzerClass ui;

    /// \brief 表达式检查器
    ExpressionCheck exp_check;

    /// \brief 配置信息读写
    QSettings *settings;

    /// \brief 文法
    vector<std::string> grammars;

    /// \brief 表达式
    vector<std::string> expressions;

    /// \brief 多表达式分析步骤记录器
    map<int, map<int, vector<string>>> step_record;

    /// \brief 终结符集合
    set<char> terminal_symbols;

    /// \brief 用于显示FIRST/LAST集的表格模型
    TableModel *last_first_model;

    /// \brief 用于显示优先关系的表格模型
    TableModel *proirty_model;

    /// \brief 配置窗口
    Config *cfg;

    /// \brief 输入窗口
    InputInfo *input = new InputInfo;

    /// \brief 分析过程
    AnalysisStep *analysis_setp;


    /// \brief 输入的信息类型，0为文法，1为表达式，2为终结符
    int info_type;

    //初始化
    void init();

    //获取配置信息
    void get_settings();

    //将信号与槽函数连接
    void connect_signal_slot();

    //从文件读取文法
    void read_grammars(string file_name);

    //从文件读取终结符
    void read_terminals(string file_name);

    //从文件读取表达式
    void read_exp(string file_name);

    //添加文法的产生式
    void add_grammar(string grammar);

    //添加终结符
    void add_terminal_symbols(char terminal);

    //添加表达式
    void add_exp(string exp);

    //检查表达式
    void check_expression(string exp, int record_index);

    //设置FIRST/LAST表的样式
    void set_first_last();

    //设置优先关系表的样式
    void set_prority_table();

    //显示FIRST/LAST集
    void show_last_first();

    //显示优先关系表
    void show_prority_table();

};
#endif

