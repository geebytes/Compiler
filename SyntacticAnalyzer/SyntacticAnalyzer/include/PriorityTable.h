///=================================================================================================
/// \file PriorityTable.h
/// \date 2018/06/13
///
/// \author qinzhonghe
///
/// \email  qinzhonghe96@163.com
///
/// \brief �������ȹ�ϵ��
///=================================================================================================

#ifndef PRIORITYTABLE_H
#define PRIORITYTABLE_H
#include <stack>
#include<vector>
#include <string>
#include <set>
#include <map>
#include <iostream>
using namespace std;

///=================================================================================================
/// \class PriorityTable
///
/// \brief ��������ͨ���ķ����ķ��е��ս��������һ�����ȹ�ϵ��
///
/// \date 2018/6/1
///=================================================================================================

class PriorityTable {
  public:
    PriorityTable();
    //��ȡ����ʽ
    void get_grammar(std::vector<std::string> grammars);

    //��ȡ�ս����
    void get_terminal_symbol(set<char> terminal_symbols);

    //�������ȹ�ϵ��
    void make_prioity_table();

    //��ӡFIRST/LAST��
    void print_first_last();

    //��ӡ���ȹ�ϵ��
    void print_table();

    //��ӡ�ķ�
    void print_grammar();

    //���ݲ���ʽ�Ҳ����Ҳ���ʽ��
    char get_production_left(string right);

    //��ȡ����ʽ
    map<char, vector<string>> get_productions();

    //��ȡ���ȹ�ϵ��
    map<pair<char, char>, char> get_prioity_table();

    //��ȡFIRST��
    map<char, set<char>> get_first();

    //��ȡLAST��
    map<char, set<char>> get_last();
    ~PriorityTable();
  private:

    /// �ķ�
    vector<string> grammars;

    ///�ս������
    set<char> terminal_symbols;

    ///����ջ
    stack<pair<char, char> > symbols_stack;

    ///�ķ����Ҳ���ӳ��
    map<char, vector<string>>grammars_map;

    ///FirstVT��
    map<char, set<char>> first;

    ///LastVT��
    map<char, set<char>> last;

    ///���ȹ�ϵ��
    map<pair<char, char>, char>prioity_table;
    bool is_make_table;
  private:
    //�Ƿ�����FIRST������
    bool is_first(string right_str, char &terminal_symbol);

    //�Ƿ�����LAST������
    bool is_last(string right_str, char &terminal_symbol);

    //����FIRST��
    void make_first();

    //����LAST��
    void make_last();

    //��������FIRST���������Ƶ���right�Ĳ���ʽ����
    char find_first_equivalence(char right);

    //��������LAST���������Ƶ���right�Ĳ���ʽ����
    char find_last_equivalence(char right);

    //�ֽ��ķ�
    void resolve_grammars();

    //�������ŵ����ȹ�ϵ
    int prioity_type(char current, char next);

    //�������ȹ�ϵ��
    void make_prioity(string right_str);
};
#endif

