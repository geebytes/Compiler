#include "stdafx.h"
#include "PriorityTable.h"
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/regex.hpp>
#include <boost/algorithm/string/regex.hpp>
#include <iterator>
#include <iomanip>
PriorityTable::PriorityTable() {
    is_make_table = false;
}

///=================================================================================================
/// \fn void PriorityTable::get_grammar(std::vector<std::string> grammars)
///
/// \brief 获取文法
///
/// \date 2018/5/31
///
/// \param grammars 所有的文法
///=================================================================================================

void PriorityTable::get_grammar(std::vector<std::string> grammars) {
    this->grammars = grammars;
    resolve_grammars();
}

///=================================================================================================
/// \fn void PriorityTable::get_terminal_symbol(set<char> terminal_symbols)
///
/// \brief 获取终结符
///
/// \date 2018/5/31
///
/// \param terminal_symbols 终结符集合
///=================================================================================================

void PriorityTable::get_terminal_symbol(set<char> terminal_symbols) {
    this->terminal_symbols = terminal_symbols;
}

///=================================================================================================
/// \fn void PriorityTable::resolve_grammars()
///
/// \brief 分解文法，细化文法，将文法的左右部映射成字典
/// 	   以如下文法为例：
/// 	   E->E+T|T
/// 	   T->T*F|F
///		   F->(E)|i
/// \date 2018/5/31
///=================================================================================================

void PriorityTable::resolve_grammars() {
    vector<string>::iterator it = grammars.begin(); //产生式起始句，E->E+T|T
    vector<string>::iterator end = grammars.end(); //产生式结尾句，F->(E)|i
    for (it; it != end; it++) { //遍历产生式
        vector<string> grammars_left_right; //存储产生式的左部和右部，F,(E)|i
        boost::split_regex(grammars_left_right, *it, boost::regex("->")); //将产生式左右部分隔
        vector<string> right;//分隔产生式右部,E+T,T
        boost::split(right, grammars_left_right[1], boost::is_any_of("|"), boost::token_compress_on);
        grammars_map[grammars_left_right[0][0]] = right; //产生式的左右部映射,E->E+T
        first[grammars_left_right[0][0]] = set<char>(); //初始化FIRST集
        last[grammars_left_right[0][0]] = set<char>(); //初始化LAST集
    }
}

///=================================================================================================
/// \fn int PriorityTable::prioity_type(char current, char next)
///
/// \brief 取得两个终结符间的关系
///
/// \date 2018/6/1
///
/// \param current 产生式右部当前的字符
/// \param next    下一个字符
///
/// \return 关系类型
/// 		0:U->...ab...,=
/// 		1:U->...aV...,<
/// 		2:U->...Vb...,>
/// 		3: 都是非终结符
///=================================================================================================

int PriorityTable::prioity_type(char current, char next) {
    bool current_is_teminal = terminal_symbols.find(current) != terminal_symbols.end() ? true : false;
    bool next_is_teminal = terminal_symbols.find(next) != terminal_symbols.end() ? true : false;
    if (current_is_teminal && next_is_teminal)
        return 0;
    else if (current_is_teminal && (!next_is_teminal))
        return 1;
    else if (!current_is_teminal && next_is_teminal)
        return 2;
    else
        return 3;
}

///=================================================================================================
/// \fn void PriorityTable::make_prioity(string right_str)
///
/// \brief 由产生式构建非终结符间的优先关系
///
/// \date 2018/6/1
///
/// \param right_str 产生式的右部
///=================================================================================================

void PriorityTable::make_prioity(string right_str) {
    int str_size = right_str.size();
    for (int i = 0; i < str_size - 1; i++) {
        if (prioity_type(right_str[i], right_str[i + 1]) == 0) //U->...ab...
            prioity_table[make_pair(right_str[i], right_str[i + 1])] = '=';
        if (i <= str_size - 2 && (prioity_type(right_str[i], right_str[i + 2]) == 0) &&
                (terminal_symbols.find(right_str[i + 1]) == terminal_symbols.end())) //U->...aVb...
            prioity_table[make_pair(right_str[i], right_str[i + 2])] = '=';
        if (prioity_type(right_str[i], right_str[i + 1]) == 1) { //U->...aV...
            set<char>next_first = first[right_str[i + 1]];
            set<char>::iterator set_it = next_first.begin();
            set<char>::iterator set_end = next_first.end();
            for (set_it; set_it != set_end; set_it++) { //相邻的下一个字符的FIRST集
                prioity_table[make_pair(right_str[i], *set_it)] = '<';
            }
        }
        if (prioity_type(right_str[i], right_str[i + 1]) == 2) { //U->...Vb...
            set<char>next_first = last[right_str[i]];
            set<char>::iterator set_it = next_first.begin();
            set<char>::iterator set_end = next_first.end();
            for (set_it; set_it != set_end; set_it++) { //当前字符的LAST集
                prioity_table[make_pair(*set_it, right_str[i + 1])] = '>';
            }
        }
    }
}

///=================================================================================================
/// \fn void PriorityTable::make_prioity_table()
///
/// \brief 生成FIRST、LAST集，并构建优先关系表
///
/// \date 2018/6/1
///=================================================================================================

void PriorityTable::make_prioity_table() {
    make_first();
    make_last();
    map<char, vector<string>>::iterator it = grammars_map.begin(); //产生式起始句
    map<char, vector<string>>::iterator end = grammars_map.end(); //产生式结尾句
    vector<string>::iterator right_it; //产生式右部起始
    vector<string>::iterator right_end; //产生式右部结尾
    string right_str;
    for (it; it != end; it++) {
        right_it = it->second.begin();
        right_end = it->second.end();
        for (right_it; right_it != right_end; right_it++) {
            right_str = *right_it;
            make_prioity(right_str);
        }
    }
    is_make_table = true;
}

///=================================================================================================
/// \fn void PriorityTable::make_first()
///
/// \brief 构建FIRST集
///
/// \date 2018/5/31
///=================================================================================================

void PriorityTable::make_first() {
    map<char, vector<string>>::iterator it = grammars_map.begin(); //产生式起始句
    map<char, vector<string>>::iterator end = grammars_map.end(); //产生式结尾句
    vector<string>::iterator right_it; //产生式右部起始
    vector<string>::iterator right_end; //产生式右部结尾
    char terminal_symbol; //终结符
    for (it; it != end; it++) { //遍历产生式
        right_it = it->second.begin(); //产生式右部字段起始
        right_end = it->second.end();
        for (right_it; right_it != right_end; right_it++) { //遍历产生式右部字段
            if (is_first(*right_it, terminal_symbol)) { //是否为满足first集合元素的定义
                symbols_stack.push(make_pair(it->first, terminal_symbol));//满足则入栈
                first[it->first].insert(terminal_symbol); //添加到左部对应的FIRST集
            }
        }
        while (!symbols_stack.empty()) { //对栈内符号处理，相当于递归添加FIRST
            char first_value = symbols_stack.top().first; //获取栈顶终结符，记为（Q，a）
            char left = find_first_equivalence(first_value); //查找对应等价产生式并返回该产生式的左部，即满足P=>Q···的产生式
            if (first_value != left) { //找到满足条件的产生式
                set<char> temp;
                auto iter = std::set_union(first[left].begin(), first[left].end(), first[first_value].begin(),
                                           first[first_value].end(), std::inserter(temp, temp.begin())); //求并集，即将Q的FIRST添加到P的FIRST
                first[left] = temp;
            }
            symbols_stack.pop();
        }
    }

}

///=================================================================================================
/// \fn void PriorityTable::make_last()
///
/// \brief 构建LAST集
///
/// \date 2018/5/31
///=================================================================================================

void PriorityTable::make_last() {
    map<char, vector<string>>::iterator it = grammars_map.begin(); //产生式起始句
    map<char, vector<string>>::iterator end = grammars_map.end(); //产生式结尾句
    vector<string>::iterator right_it; //产生式右部起始
    vector<string>::iterator right_end; //产生式右部结尾
    char terminal_symbol; //终结符
    for (it; it != end; it++) { //遍历产生式
        right_it = it->second.begin(); //产生式右部字段起始
        right_end = it->second.end();
        for (right_it; right_it != right_end; right_it++) { //遍历产生式右部字段
            if (is_last(*right_it, terminal_symbol)) { //是否为满足LAST集合元素的定义
                symbols_stack.push(make_pair(it->first, terminal_symbol));//满足则入栈
                last[it->first].insert(terminal_symbol); //添加到左部对应的FIRST集
            }
        }
        while (!symbols_stack.empty()) { //对栈内符号处理，相当于递归添加LAST
            char first_value = symbols_stack.top().first; //获取栈顶终结符，记为（Q，a）
            char left = find_last_equivalence(first_value); //查找对应等价产生式并返回该产生式的左部，即满足P=>...Q的产生式
            if (first_value != left) { //找到满足条件的产生式
                set<char> temp;
                auto iter = std::set_union(last[left].begin(), last[left].end(), last[first_value].begin(),
                                           last[first_value].end(), std::inserter(temp, temp.begin())); //求并集，即将Q的LAST添加到P的LAST
                last[left] = temp;
            }
            symbols_stack.pop();
        }
    }
}

///=================================================================================================
/// \fn void PriorityTable::print_first()
///
/// \brief 打印FIRST、LAST集
///
/// \date 2018/5/31
///=================================================================================================

void PriorityTable::print_first_last() {
    map<char, set<char>>::iterator it = first.begin();
    map<char, set<char>>::iterator end = first.end();
    if (!is_make_table) {
        cout << "请先生成优先关系表" << endl;
        return;
    }
    cout << setfill('*') << setw(50) << "FIRST集";
    cout << setfill('*') << setw(50) << "" << endl;
    for (it; it != end; it++) {
        cout << setfill(' ') << setw(10) << it->first << "|";
        set<char>::iterator symbos_it = it->second.begin();
        set<char>::iterator symbos_end = it->second.end();
        for (symbos_it; symbos_it != symbos_end; symbos_it++) {
            cout << setfill(' ') << setw(10) << *symbos_it << "|";
        }
        cout << endl;
        cout << setfill('-') << setw(100) << "" << endl;
    }
    cout << endl;
    it = last.begin();
    end = last.end();
    cout << setfill('*') << setw(50) << "LAST集";
    cout << setfill('*') << setw(50) << "" << endl;
    for (it; it != end; it++) {
        cout << setfill(' ') << setw(10) << it->first << "|";
        set<char>::iterator symbos_it = it->second.begin();
        set<char>::iterator symbos_end = it->second.end();
        for (symbos_it; symbos_it != symbos_end; symbos_it++) {
            cout << setfill(' ') << setw(10) << *symbos_it << "|";
        }
        cout << endl;
        cout << setfill('-') << setw(100) << "" << endl;
    }
    cout << endl;
}

///=================================================================================================
/// \fn void PriorityTable::print_table()
///
/// \brief 打印优先关系表
///
/// \date 2018/6/1
///=================================================================================================

void PriorityTable::print_table() {
    cout << setfill('=') << setw(50) << "优先关系表";
    cout << setfill('=') << setw(50) << "" << endl;
    cout << setfill(' ') << setw(10) << "";
    set<char>::iterator it = terminal_symbols.begin();
    set<char>::iterator end = terminal_symbols.end();
    set<char>::iterator set_it = it;
    set<char>::iterator set_end = end;
    cout << " ";
    for (it; it != end; it++)
        cout << setfill(' ') << setw(10) << *it << "|";
    cout << endl;
    cout << setfill('=') << setw(100) << "" << endl;
    it = set_it;
    for (it; it != end; it++) {
        cout << setfill(' ') << setw(10) << *it << "|";
        for (set_it; set_it != set_end; set_it++) {
            cout << setfill(' ') << setw(10) << prioity_table[make_pair(*it, *set_it)] << "|";
        }
        cout << endl;
        set_it = terminal_symbols.begin();
    }
    cout << endl;
}

void PriorityTable::print_grammar() {
    map<char, vector<string>>::iterator it = grammars_map.begin();
    map<char, vector<string>>::iterator end = grammars_map.end();
    vector<string>::iterator it_str;
    vector<string>::iterator end_str;
    for (it; it != end; it++) {
        cout << it->first << ":";
        it_str = it->second.begin();
        end_str = it->second.end();
        for (it_str; it_str != end_str; it_str++) {
            cout << *it_str << " ";
        }
        cout << endl;
    }
}

///=================================================================================================
/// \fn string PriorityTable::get_production_left(string right)
///
/// \brief 给定产生式的右部获取产生式的左部
///
/// \date 2018/6/1
///
/// \param right 产生式的右部
///
/// \return 产生式的左部
///=================================================================================================

char PriorityTable::get_production_left(string right) {
    map<char, vector<string>>::iterator it = grammars_map.begin();
    map<char, vector<string>>::iterator end = grammars_map.end();
    for (it; it != end; it++) {
        if (std::find(it->second.begin(), it->second.end(), right) != it->second.end())
            return it->first;
    }
    return 0;
}

map<char, vector<string>> PriorityTable::get_productions() {
    return grammars_map;
}

///=================================================================================================
/// \fn map<pair<char, char>, char> PriorityTable::get_prioity_table()
///
/// \brief 获取优先关系表.
///
/// \date 2018/6/1
///
/// \return 优先关系表
///=================================================================================================

map<pair<char, char>, char> PriorityTable::get_prioity_table() {
    return prioity_table;
}

///=================================================================================================
/// \fn std::map<char, std::set<char>> PriorityTable::get_first()
///
/// \brief 获取first集合
///
/// \date 2018/6/1
///
/// \return FIRST集
///=================================================================================================

std::map<char, std::set<char>> PriorityTable::get_first() {
    return first;
}

///=================================================================================================
/// \fn std::map<char, std::set<char>> PriorityTable::get_last()
///
/// \brief 获取LAST集合
///
/// \date 2018/6/1
///
/// \return last集
///=================================================================================================

std::map<char, std::set<char>> PriorityTable::get_last() {
    return last;
}

PriorityTable::~PriorityTable() {
}

///=================================================================================================
/// \fn bool PriorityTable::is_first(string right_str, char &terminal_symbol)
///
/// \brief 产生式的右部是否有满足FIRST集元素定义的终结符
///
/// \date 2018/5/31
///
/// \param 		    right_str	    产生式右部
/// \param [out] terminal_symbol 满足条件的终结符，如果没有则值设为0
///
/// \return 满足条件返回TURE,不满足则FALSE
///=================================================================================================

bool PriorityTable::is_first(string right_str, char &terminal_symbol) {
    string::iterator it = right_str.begin();
    string::iterator end = right_str.end();
    if (terminal_symbols.find(*it) != terminal_symbols.end()) {
        terminal_symbol = *it;
        return true;
    }
    it++;
    if((it != end) && (terminal_symbols.find(*it) != terminal_symbols.end())) {
        terminal_symbol = *it;
        return true;
    } else {
        terminal_symbol = 0;
        return false;
    }
}

///=================================================================================================
/// \fn bool PriorityTable::is_last(string right_str, char &terminal_symbol)
///
/// \brief 判断是否满足LAST集元素的定义
///
/// \date 2018/5/31
///
/// \param 		    right_str	    产生式右部
/// \param [out] terminal_symbol 满足条件的终结符，如果没有则值设为0
///
/// \return 满足条件返回TURE,不满足则FALSE
///=================================================================================================

bool PriorityTable::is_last(string right_str, char &terminal_symbol) {
    string::iterator it = right_str.end();
    string::iterator end = right_str.end();
    int str_size = right_str.size();
    int index = str_size - 1;
    if (terminal_symbols.find(right_str[index]) != terminal_symbols.end()) {
        terminal_symbol = right_str[index];
        return true;
    } else if (str_size >= 2)
        index--;
    else {
        terminal_symbol = 0;
        return false;
    }
    if ((terminal_symbols.find(right_str[index]) != terminal_symbols.end())) {
        terminal_symbol = right_str[index];
        return true;
    } else {
        terminal_symbol = 0;
        return false;
    }

}

///=================================================================================================
/// \fn char PriorityTable::find_equivalence(char right)
///
/// \brief 查找满足能推导出right的产生式的左部
/// 	   条件：对于产生式，A->B...,这里的right就是B，则满足条件的左部就是A
///
/// \date 2018/5/31
///
/// \param right 该产生式的右部
///
/// \return 满足条件的左部，若没有则返回right
///=================================================================================================

char PriorityTable::find_first_equivalence(char right) {
    map<char, vector<string>>::iterator it = grammars_map.begin();
    map<char, vector<string>>::iterator end = grammars_map.end();
    vector<string>::iterator start_it;
    vector<string>::iterator end_it;
    string temp = "";
    temp.append(1, right);
    for (it; it != end; it++) { //遍历产生式
        start_it = it->second.begin();
        end_it = it->second.end();
        for (start_it; start_it != end_it; start_it++) { //查找等于right的右部的第一个非终结符
            string::iterator str_it = start_it->begin();
            if(*str_it == right)
                return it->first;
        }
    }
    return right;
}

///=================================================================================================
/// \fn char PriorityTable::find_last_equivalence(char right)
///
/// \brief 查找满足相应条件的能推导出right的产生式的左部
/// 	   条件：对于产生式，A->...B,这里的right就是B，则满足条件的左部就是A
///
/// \date 2018/6/1
///
/// \param right 产生式的右部
///
/// \return 产生式的左部
///=================================================================================================

char PriorityTable::find_last_equivalence(char right) {
    map<char, vector<string>>::iterator it = grammars_map.begin();
    map<char, vector<string>>::iterator end = grammars_map.end();
    vector<string>::iterator start_it;
    vector<string>::iterator end_it;
    string temp = "";
    temp.append(1, right);
    for (it; it != end; it++) {
        start_it = it->second.begin();
        end_it = it->second.end();
        for (start_it; start_it != end_it; start_it++) { //遍历产生式
            if (start_it->at(start_it->size() - 1) == right) //产生式右部最后一个非终结符
                return it->first;
        }
    }
    return right;
}
