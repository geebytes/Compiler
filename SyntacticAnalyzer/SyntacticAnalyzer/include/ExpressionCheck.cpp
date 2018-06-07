#include "ExpressionCheck.h"
#include <regex>
#include <iterator>
#include"boost/format.hpp"
#include <iomanip>
ExpressionCheck::ExpressionCheck() {
    left_prime_phrase = "";
    is_move = true;
    error_info.push_back("缺少表达式"); //eg.
    error_info.push_back("表达式间缺少运算符"); //eg .ii
    error_info.push_back("括号间无表达式"); //eg.()
    error_info.push_back("非法左括号");
    error_info.push_back("表达式间缺少运算符"); //eg. )(
    error_info.push_back("正确");
    error_info.push_back("非法右括号");
    expression_index = 0;
    setp = 1;
}

///=================================================================================================
/// \fn void ExpressionCheck::get_grammar(std::vector<std::string> grammars)
///
/// \brief 获取文法
///
/// \date 2018/6/3
///
/// \param grammars 存储产生式的数组
///=================================================================================================

void ExpressionCheck::get_grammar(std::vector<std::string> grammars) {
    priority_table.get_grammar(grammars);
    this->grammars = grammars;
}

///=================================================================================================
/// \fn void ExpressionCheck::get_terminal_symbol(set<char> terminal_symbols)
///
/// \brief 获取终结符集
/// \date 2018/6/3
///
/// \param terminal_symbols 终结符集合
///=================================================================================================

void ExpressionCheck::get_terminal_symbol(set<char> terminal_symbols) {
    priority_table.get_terminal_symbol(terminal_symbols);
    this->terminal_symbols = terminal_symbols;
}

///=================================================================================================
/// \fn void ExpressionCheck::make_priority_table()
///
/// \brief 构建优先关系表.
///
/// \date 2018/6/4
///=================================================================================================

void ExpressionCheck::make_priority_table() {
    priority_table.make_prioity_table();
    table = priority_table.get_prioity_table();
    production_to_std();
}

///=================================================================================================
/// \fn int ExpressionCheck::check_error(string left_prime_phrase, char normalize_char)
///
/// \brief 错误检查
///
/// \date 2018/6/3
///
/// \param left_prime_phrase 最左素短语
/// \param normalize_char    归约的符号
///
/// \return 错误代码
///=================================================================================================

int ExpressionCheck::check_error(string left_prime_phrase, char normalize_char) {

    if (normalize_char == 'i') { //表达式两侧是否存在运算符
        int index = left_prime_phrase.find(normalize_char);
        if (index != left_prime_phrase.size() - 1 != 0 && left_prime_phrase[index + 1] == 'i') { //表达式左侧是缺少运算符,eg. ii
            return DEFECT_OPERATOR;
        }
        if ((index != 0 && (terminal_symbols.find(index - 1) == terminal_symbols.end()))) //表达式右侧是缺少运算符
            return EXP_NO_OPERATOR;
        if ((index != left_prime_phrase.size() - 1 && (terminal_symbols.find(index + 1) == terminal_symbols.end()))) //表达式左侧是缺少运算符
            return EXP_NO_OPERATOR;
    }
    if (normalize_char == '(' || normalize_char == ')') { //括号合法性检查
        int left_index = left_prime_phrase.find('(');
        int right_index = left_prime_phrase.find(')');
        if (left_index != -1 && right_index != -1) { //括号间是否存在表达式,eg. (i)
            for (int i = left_index; i != right_index; i++) {
                if (terminal_symbols.find(left_prime_phrase[i]) == terminal_symbols.end())
                    return OK;
            }
            return BRACKETS_NO_EXP;
        }
        if (left_index == left_prime_phrase.size() - 1) { //非法左括号
            return INVALID_LEFT_BRACKET;
        }
        if (left_index + 1 == right_index) { //缺少运算符，eg. )(
            return DEFECT_OPERATOR;
        }
        if (left_index != -1 && right_index == -1) { //非法左括号
            return INVALID_LEFT_BRACKET;
        }
        if (left_index == -1 && right_index != -1) { //非法右括号
            return INVALID_RIGHT_BRACKET;
        }
    }
    if (terminal_symbols.find(normalize_char) != terminal_symbols.end()) { //运算符间是否存在非终结符
        int index = left_prime_phrase.find(normalize_char);
        if ((index != 0 && (terminal_symbols.find(index - 1) != terminal_symbols.end()))) //运算符左侧缺少表达式
            return EXPRESSION_ERROR;
        if ((index != left_prime_phrase.size() - 1 && (terminal_symbols.find(index + 1) != terminal_symbols.end()))) //运算符右侧缺少表达式
            return EXPRESSION_ERROR;
    }
    return OK;
}

///=================================================================================================
/// \fn char ExpressionCheck::skip_no_terminal(char top_value)
///
/// \brief 跳过非终结符
///
/// \date 2018/6/3
///
/// \param top_value 符号栈栈顶元素
///
/// \return 终结符栈顶
///=================================================================================================

char ExpressionCheck::skip_no_terminal(char top_value) {
    if (terminal_symbols.find(top_value) == terminal_symbols.end() && top_value != '#') {
        left_prime_phrase.append(1, top_value);
        symbols_stack.pop();
        if (!symbols_stack.empty())
            top_value = symbols_stack.top();
        else {
            cout << "error" << endl;
            return 0;
        }
    }
    return top_value;
}

///=================================================================================================
/// \fn char ExpressionCheck::reduction(char top_value, char exp_value)
///
/// \brief 归约操作
///
/// \date 2018/6/3
///
/// \param top_value 栈顶元素
/// \param exp_value 表达式串当前的首字符
///
/// \return 归约后的栈顶元素
///=================================================================================================

char ExpressionCheck::reduction(char top_value, char exp_value) {
    char q = top_value; //栈顶元素，最左素短语的第一个非终结符
    char a = exp_value; //输入串首
    char p = top_value;

    while ((table[make_pair(p, a)] == '>' || a == '#') && !symbols_stack.empty()) { //栈顶优先级高于输入串首
        left_prime_phrase.append(1, top_value); //添加素短语的字符
        symbols_stack.pop();
        top_value = symbols_stack.top();
        top_value = skip_no_terminal(top_value); //跳过非终结符
        if (table[make_pair(top_value, q)] == '=' || table[make_pair(top_value, q)] == '<' || top_value == '#') { //到达最左素短语的最后一个终结符
            if (table[make_pair(top_value, q)] == '=') {
                left_prime_phrase.append(1, top_value);
                symbols_stack.pop();
            }
            reverse(left_prime_phrase.begin(), left_prime_phrase.end()); //最左素短语的反转

            top_value = symbols_stack.top(); //更新栈顶元素
            if (match_production_left(left_prime_phrase)) { //是否满足归约的条件
                symbols_stack.push('V'); //替换最左素短语
                is_move = false; //不移进
                left_phrase = left_prime_phrase; //满足条件的最左素短语
            } else {
                int error_type = check_error(left_prime_phrase, q);
                if (error_type != OK) {
                    error_record[expression_index] = error_info[error_type];
                }
                is_move = true;
                left_phrase.clear();
            }
            left_prime_phrase.clear(); //清空该步骤的最左素短语
            break;
        } else {
            continue;
        }
    }
    return top_value;
}

///=================================================================================================
/// \fn void ExpressionCheck::production_to_std()
///
/// \brief 产生式标准化，即产生式右部所有的非终结符替换为V
///
/// \date 2018/6/3
///=================================================================================================

void ExpressionCheck::production_to_std() {
    productions = priority_table.get_productions();
    map<char, vector<string>>::iterator it = productions.begin();
    map<char, vector<string>>::iterator end = productions.end();
    vector<string>::iterator str_it;
    vector<string>::iterator end_it;

    for (it; it != end; it++) {
        str_it = it->second.begin();
        end_it = it->second.end();
        for (str_it; str_it != end_it; str_it++) {
            string reg_str = "?[A-Z]";
            std::regex reg("[A-Z]");
            string str = std::regex_replace(*str_it, reg, "V");
            std_left.insert(str);
        }
    }

}

///=================================================================================================
/// \fn bool ExpressionCheck::match_production_left(string right_str)
///
/// \brief 是否存在能够推导出给定产生式的右部的产生式左部.
///
/// \date 2018/6/3
///
/// \param right_str 产生式右部
///
/// \return True 如果存在, false 如果不存在
///=================================================================================================

bool ExpressionCheck::match_production_left(string right_str) {
    if (std_left.find(right_str) != std_left.end())
        return true;
    else {
        return false;
    }
}

///=================================================================================================
/// \fn void ExpressionCheck::save_analysis_step(int index, char prioity, string left, string act)
///
/// \brief 保存分析记录
///
/// \date 2018/6/4
///
/// \param index   当前表达式的位置
/// \param prioity 栈顶与当前表达式字符的关系
/// \param left    最左素短语
/// \param act     动作
///=================================================================================================

void ExpressionCheck::save_analysis_step(int index, char prioity, string left, string act) {
    string stack_status = get_stack_status();
    if (prioity == 0)
        prioity = '<';
    boost::format fmt("%-20s|%-20s|%-20s|%-20s|%-20s|%-20s");
    fmt % setp % stack_status % prioity % expression_str.substr(index) % left % act;
    analysis_info[setp].push_back(stack_status);
    analysis_info[setp].push_back(string("").append(1, prioity));
    analysis_info[setp].push_back(expression_str.substr(index));
    analysis_info[setp].push_back(left);
    analysis_info[setp].push_back(act);
    setp++;
}

///=================================================================================================
/// \fn int ExpressionCheck::check_expression(string expression)
///
/// \brief 检查表达式
///
/// \date 2018/6/3
///
/// \param expression 给定的表达式
///
/// \return An int.
///=================================================================================================

int ExpressionCheck::check_expression(string expression) {

    symbols_stack.push('#');
    expression.append(1, '#');
    expression_str = expression;

    table = priority_table.get_prioity_table();
    int str_size = expression.size();
    int index = 0;
    char top_value = symbols_stack.top();
    int stack_size = symbols_stack.size();

    while (expression[index] != '#') { //遍历表达式串
        expression_index = index;
        is_move = true;
        char a = expression[index];
        top_value = symbols_stack.top();
        top_value = skip_no_terminal(top_value);
        if (top_value == 0) { //符号栈为空
            break;
        }
        char q = top_value;
        if (table.count(make_pair(top_value, a)) == 0 && top_value != '#') { //栈顶终结符和输入串当前的终结符无关系
            error_record[expression_index] = error_info[EXP_NO_OPERATOR];
        }
        save_analysis_step(index, table[make_pair(top_value, a)], left_phrase, "移进");
        top_value = reduction(q, a); //归约操作
        if (!left_phrase.empty()) { //归约
            save_analysis_step(index, table[make_pair(top_value, a)], left_phrase, "归约");
            left_phrase.clear();
        }
        if (is_move || top_value == '#' || table[make_pair(top_value, a)] == '<' || table[make_pair(top_value, a)] == '=') { //移进
            symbols_stack.push(a);
        } else { //输入串不移动
            is_move = true;
            index--;
        }
        index++;
    }
    while (expression[index] == '#' && symbols_stack.size() > 2) {

        top_value = symbols_stack.top();
        top_value = skip_no_terminal(top_value);

        reduction(top_value, '#');
        if (!left_phrase.empty())
            save_analysis_step(index, '>', left_phrase, "归约");

    }
    left_phrase.clear();
    if (terminal_symbols.find(symbols_stack.top()) != terminal_symbols.end() || symbols_stack.top() == '#') {
        if(error_record.find(expression_index) == error_record.end())
            error_record[expression_index] = error_info[EXPRESSION_ERROR]; //运算符间缺少表达式
        save_analysis_step(index, ' ', left_phrase, "错误");

    } else
        save_analysis_step(index, ' ', left_phrase, "结束");
    setp = 0;
    return 0;
}

///=================================================================================================
/// \fn void ExpressionCheck::print_info()
///
/// \brief 打印所有信息
///
/// \date 2018/6/3
///=================================================================================================

void ExpressionCheck::print_info() {
    priority_table.print_first_last();
    priority_table.print_table();
    print_step();
    print_error();
}

///=================================================================================================
/// \fn void ExpressionCheck::print_stack()
///
/// \brief 打印符号栈的状态
///
/// \date 2018/6/3
///=================================================================================================

void ExpressionCheck::print_stack() {
    stack<char> s_stack = symbols_stack;
    while (!s_stack.empty()) {
        cout << s_stack.top();
        s_stack.pop();
    }
    cout << endl;
}

///=================================================================================================
/// \fn void ExpressionCheck::print_step()
///
/// \brief 打印每一步的状态.
///
/// \date 2018/6/3
///=================================================================================================

void ExpressionCheck::print_step() {
    boost::format fmt("%-20s|%-20s|%-20s|%-20s|%-20s|%-20s");
    fmt % "步骤" % "符号栈" % "关系" % "输入串" % "最左素短语" % "动作"; //输出每一步的状态
    string output_str = fmt.str();
    cout << output_str << endl;
    cout << setfill('-') << setw(100) << "" << endl;
    map<int, vector<string>>::iterator it = analysis_info.begin();
    map<int, vector<string>>::iterator end = analysis_info.end();
    for (it; it != end; it++) {
        int setp_num = it->first;
        string stack_status = it->second[0];
        string prioity = it->second[1];
        string expression_str = it->second[2];
        string left = it->second[3];
        string act = it->second[4];
        boost::format fmt("%-20s|%-20s|%-20s|%-20s|%-20s|%-20s");
        fmt % setp_num % stack_status % prioity % expression_str % left % act;
        string output_str = fmt.str();
        cout << output_str;
        cout << "\n" << setfill('-') << setw(100) << "" << endl;
    }
    cout << endl;
}

///=================================================================================================
/// \fn void ExpressionCheck::print_error()
///
/// \brief 输出错误信息
/// \date 2018/6/3
///=================================================================================================

void ExpressionCheck::print_error() {
    boost::format fmt("%-20s|%-20s");
    fmt % "出错位置" % "错误描述"; //错误描述
    string output_str = fmt.str();
    cout << output_str << endl;
    cout << setfill('-') << setw(100) << "" << endl;
    map<int, string>::iterator it = error_record.begin();
    map<int, string>::iterator end = error_record.end();
    for (it; it != end; it++) {
        boost::format fmt("%-20s|%-20s");
        fmt % it->first % it->second; //错误描述
        string output_str = fmt.str();
        cout << output_str << endl;
        cout << setfill('-') << setw(100) << "" << endl;
    }
}

///=================================================================================================
/// \fn void ExpressionCheck::reset()
///
/// \brief 重置一些记录信息
///
/// \date 2018/6/4
///=================================================================================================

void ExpressionCheck::reset() {
    analysis_info.clear();
    while (!symbols_stack.empty()) {
        symbols_stack.pop();
    }
    left_phrase.clear();
    left_prime_phrase.clear();
    error_record.clear();
    expression_index = 0;
    setp = 1;
    is_move = true;
}

///=================================================================================================
/// \fn std::map<int, std::vector<std::string>> ExpressionCheck::get_setp()
///
/// \brief 获取分析步骤
///
/// \date 2018/6/3
///
/// \return 分析步骤信息
///=================================================================================================

std::map<int, std::vector<std::string>> ExpressionCheck::get_setp() {
    return analysis_info;
}

///=================================================================================================
/// \fn std::map<int, std::string> ExpressionCheck::get_error()
///
/// \brief 获取错误信息
///
/// \date 2018/6/3
///
/// \return 错误信息
///=================================================================================================

std::map<int, std::string> ExpressionCheck::get_error() {
    return error_record;
}

///=================================================================================================
/// \fn std::map<std::pair<char, char>, char> ExpressionCheck::get_priority_table()
///
/// \brief 获取优先关系表
///
/// \date 2018/6/3
///
/// \return 优先关系表
///=================================================================================================

std::map<std::pair<char, char>, char> ExpressionCheck::get_priority_table() {
    return table;
}

///=================================================================================================
/// \fn std::map<char, std::set<char>> ExpressionCheck::get_last()
///
/// \brief 获取LAST集
///
/// \date 2018/6/3
///
/// \return LAST集.
///=================================================================================================

std::map<char, std::set<char>> ExpressionCheck::get_last() {
    return priority_table.get_last();
}

///=================================================================================================
/// \fn std::map<char, std::set<char>> ExpressionCheck::get_first()
///
/// \brief 获取FIRST集
///
/// \date 2018/6/3
///
/// \return The first.
///=================================================================================================

std::map<char, std::set<char>> ExpressionCheck::get_first() {
    return priority_table.get_first();
}

///=================================================================================================
/// \fn std::string ExpressionCheck::get_stack_status()
///
/// \brief 获取符号栈的内容
///
/// \date 2018/6/3
///
/// \return 符号栈的内容，从右到左
///=================================================================================================

std::string ExpressionCheck::get_stack_status() {
    string temp = "";
    stack<char> s_stack = symbols_stack;
    while (!s_stack.empty()) {
        temp.append(1, s_stack.top());
        s_stack.pop();
    }
    reverse(temp.begin(), temp.end());
    return temp;
}

ExpressionCheck::~ExpressionCheck() {
}
