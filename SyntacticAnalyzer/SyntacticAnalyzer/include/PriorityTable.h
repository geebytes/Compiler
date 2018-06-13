///=================================================================================================
/// \file PriorityTable.h
/// \date 2018/06/13
///
/// \author qinzhonghe
///
/// \email  qinzhonghe96@163.com
///
/// \brief 生成优先关系表
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
/// \brief 该类用于通过文法和文法中的终结符集生成一个优先关系表。
///
/// \date 2018/6/1
///=================================================================================================

class PriorityTable {
  public:
    PriorityTable();
    //获取产生式
    void get_grammar(std::vector<std::string> grammars);

    //获取终结符集
    void get_terminal_symbol(set<char> terminal_symbols);

    //生成优先关系表
    void make_prioity_table();

    //打印FIRST/LAST集
    void print_first_last();

    //打印优先关系表
    void print_table();

    //打印文法
    void print_grammar();

    //根据产生式右部查找产生式左部
    char get_production_left(string right);

    //获取产生式
    map<char, vector<string>> get_productions();

    //获取优先关系表
    map<pair<char, char>, char> get_prioity_table();

    //获取FIRST集
    map<char, set<char>> get_first();

    //获取LAST集
    map<char, set<char>> get_last();
    ~PriorityTable();
  private:

    /// 文法
    vector<string> grammars;

    ///终结符集合
    set<char> terminal_symbols;

    ///符号栈
    stack<pair<char, char> > symbols_stack;

    ///文法左右部的映射
    map<char, vector<string>>grammars_map;

    ///FirstVT集
    map<char, set<char>> first;

    ///LastVT集
    map<char, set<char>> last;

    ///优先关系表
    map<pair<char, char>, char>prioity_table;
    bool is_make_table;
  private:
    //是否满足FIRST的条件
    bool is_first(string right_str, char &terminal_symbol);

    //是否满足LAST的条件
    bool is_last(string right_str, char &terminal_symbol);

    //生成FIRST集
    void make_first();

    //生成LAST集
    void make_last();

    //查找满足FIRST条件且能推导出right的产生式的左部
    char find_first_equivalence(char right);

    //查找满足LAST条件且能推导出right的产生式的左部
    char find_last_equivalence(char right);

    //分解文法
    void resolve_grammars();

    //两个符号的优先关系
    int prioity_type(char current, char next);

    //生成优先关系表
    void make_prioity(string right_str);
};
#endif

