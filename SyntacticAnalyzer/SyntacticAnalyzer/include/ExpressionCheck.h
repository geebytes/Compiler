///=================================================================================================
/// \file ExpressionCheck.h
/// \date 2018/06/13
///
/// \author qinzhonghe
///
/// \email  qinzhonghe96@163.com
///
/// \brief 声明用于表达式检查的类
///=================================================================================================

#ifndef EXPRESSIONCHECK_H
#define EXPRESSIONCHECK_H
#include "PriorityTable.h"
#include<vector>
#include<set>
#include <map>
#include <stack>
#include <cctype>
#include <boost/algorithm/string/replace.hpp>
using namespace std;

///=================================================================================================
/// \enum ERROR_CODE
///
/// \brief 表达式错误代码
///
///=================================================================================================

enum ERROR_CODE {

    /// \brief 运算符间缺少表达式
    EXPRESSION_ERROR,

    /// \brief 表达式间缺少运算符
    EXP_NO_OPERATOR,

    /// \brief 括号间无表达式
    BRACKETS_NO_EXP,

    /// \brief 非法左括号
    INVALID_LEFT_BRACKET,

    /// \brief 表达式间缺少运算符
    DEFECT_OPERATOR,

    /// \brief 正确
    OK,

    /// \brief 非法右括号
    INVALID_RIGHT_BRACKET
};

///=================================================================================================
/// \class ExpressionCheck
///
/// \brief 提供检查表达式合法性的功能
///
/// \date 2018/6/3
///=================================================================================================

class ExpressionCheck {
  public:
    ExpressionCheck();

    //获取文法
    void get_grammar(std::vector<std::string> grammars);

    //获取终结符集合
    void get_terminal_symbol(set<char> terminal_symbols);

    //构建优先关系表
    void make_priority_table();

    //检查表达式
    int check_expression(string expression);

    //打印信息
    void print_info();

    //打印符号状态
    void print_stack();

    //打印分析步骤
    void print_step();

    //打印错误信息
    void print_error();

    //重置数据
    void reset();

    //获取分析步骤
    map<int, vector<string>> get_setp();

    //获取错误信息
    map<int, string> get_error();

    //获取优先关系表
    map<pair<char, char>, char> get_priority_table();

    //获取LAST集
    map<char, set<char>> get_last();

    //获取FIRST集
    map<char, set<char>> get_first();

    //获取符号栈状态
    string get_stack_status();

    ~ExpressionCheck();
  private:

    /// \brief 优先关系表
    PriorityTable priority_table;

    /// \brief 产生式
    vector<std::string> grammars;

    /// \brief 错误信息
    vector<std::string>error_info;

    /// \brief 分析过程的信息
    map<int, vector<string>> analysis_info;

    /// \brief 错误记录
    map<int, string> error_record;

    /// \brief 终结符集合
    set<char> terminal_symbols;

    /// \brief 符号栈
    stack<char> symbols_stack;

    /// \brief 优先关系表
    map<pair<char, char>, char>table;

    /// \brief 产生式
    map<char, vector<string>>productions;

    /// \brief 标准化后的产生式的右部
    set<string> std_left;

    /// \brief 最左素短语
    string left_prime_phrase;

    /// \brief 表达式
    string expression_str;

    /// \brief 表达式字符索引
    int expression_index;

    /// \brief 步骤计数器
    int setp;

    /// \brief 素短语
    string left_phrase;

    /// \brief 是否移进
    bool is_move;

    //对最左素短语进行错误检查
    int check_error(string left_prime_phrase, char normalize_char);

    //跳过非终结符
    char skip_no_terminal(char top_value);

    //归约
    char reduction(char top_value, char exp_value);

    //产生式标准化
    void production_to_std();

    //根据产生式右侧匹配左侧
    bool match_production_left(string right_str);

    //存储分析步骤
    void save_analysis_step(int index, char prioity, string left, string act);




};
#endif


