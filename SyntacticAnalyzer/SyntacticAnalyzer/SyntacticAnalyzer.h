///=================================================================================================
/// \file SyntacticAnalyzer.h
///
/// \brief ����������ȷ�����GUI�߼��������
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
    //���ļ��򿪱��ʽ
    void open_expression();

    //�����ô���
    void open_setting();

    //��ʼ�����ʽ
    void check_btn();

    //������������ս�����ϵ��ļ�·��
    void rev_terminal_path(QString);

    //������������ķ����ļ�·��
    void rev_grammars_path(QString);

    //�ر����ô���
    void close_cfg();

    //������Ϣ
    void update_info();

    //�����봰�ڻ�ȡ������Ϣ
    void input_info(int input_type);

    //���������Ӧ
    void input_finish();

    //�����ķ���ť��Ӧ����
    void input_grammars();

    //�����ս����ť��Ӧ����
    void input_terminals();

    //������ʽ��ť��Ӧ����
    void input_exp();

    //����������
    void update_input();

    //��ʾĳ�����ʽ�ķ�������
    void show_step(const QUrl &link);
  signals:
    //�����������ݵ�����
    void send_input_type(int input_type);

  private:
    Ui::SyntacticAnalyzerClass ui;

    /// \brief ���ʽ�����
    ExpressionCheck exp_check;

    /// \brief ������Ϣ��д
    QSettings *settings;

    /// \brief �ķ�
    vector<std::string> grammars;

    /// \brief ���ʽ
    vector<std::string> expressions;

    /// \brief ����ʽ���������¼��
    map<int, map<int, vector<string>>> step_record;

    /// \brief �ս������
    set<char> terminal_symbols;

    /// \brief ������ʾFIRST/LAST���ı��ģ��
    TableModel *last_first_model;

    /// \brief ������ʾ���ȹ�ϵ�ı��ģ��
    TableModel *proirty_model;

    /// \brief ���ô���
    Config *cfg;

    /// \brief ���봰��
    InputInfo *input = new InputInfo;

    /// \brief ��������
    AnalysisStep *analysis_setp;


    /// \brief �������Ϣ���ͣ�0Ϊ�ķ���1Ϊ���ʽ��2Ϊ�ս��
    int info_type;

    //��ʼ��
    void init();

    //��ȡ������Ϣ
    void get_settings();

    //���ź���ۺ�������
    void connect_signal_slot();

    //���ļ���ȡ�ķ�
    void read_grammars(string file_name);

    //���ļ���ȡ�ս��
    void read_terminals(string file_name);

    //���ļ���ȡ���ʽ
    void read_exp(string file_name);

    //����ķ��Ĳ���ʽ
    void add_grammar(string grammar);

    //����ս��
    void add_terminal_symbols(char terminal);

    //��ӱ��ʽ
    void add_exp(string exp);

    //�����ʽ
    void check_expression(string exp, int record_index);

    //����FIRST/LAST�����ʽ
    void set_first_last();

    //�������ȹ�ϵ�����ʽ
    void set_prority_table();

    //��ʾFIRST/LAST��
    void show_last_first();

    //��ʾ���ȹ�ϵ��
    void show_prority_table();

};
#endif

