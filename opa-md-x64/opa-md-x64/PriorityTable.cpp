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
/// \brief ��ȡ�ķ�
///
/// \date 2018/5/31
///
/// \param grammars ���е��ķ�
///=================================================================================================

void PriorityTable::get_grammar(std::vector<std::string> grammars) {
    this->grammars = grammars;
    resolve_grammars();
}

///=================================================================================================
/// \fn void PriorityTable::get_terminal_symbol(set<char> terminal_symbols)
///
/// \brief ��ȡ�ս��
///
/// \date 2018/5/31
///
/// \param terminal_symbols �ս������
///=================================================================================================

void PriorityTable::get_terminal_symbol(set<char> terminal_symbols) {
    this->terminal_symbols = terminal_symbols;
}

///=================================================================================================
/// \fn void PriorityTable::resolve_grammars()
///
/// \brief �ֽ��ķ���ϸ���ķ������ķ������Ҳ�ӳ����ֵ�
/// 	   �������ķ�Ϊ����
/// 	   E->E+T|T
/// 	   T->T*F|F
///		   F->(E)|i
/// \date 2018/5/31
///=================================================================================================

void PriorityTable::resolve_grammars() {
    vector<string>::iterator it = grammars.begin(); //����ʽ��ʼ�䣬E->E+T|T
    vector<string>::iterator end = grammars.end(); //����ʽ��β�䣬F->(E)|i
    for (it; it != end; it++) { //��������ʽ
        vector<string> grammars_left_right; //�洢����ʽ���󲿺��Ҳ���F,(E)|i
        boost::split_regex(grammars_left_right, *it, boost::regex("->")); //������ʽ���Ҳ��ָ�
        vector<string> right;//�ָ�����ʽ�Ҳ�,E+T,T
        boost::split(right, grammars_left_right[1], boost::is_any_of("|"), boost::token_compress_on);
        grammars_map[grammars_left_right[0][0]] = right; //����ʽ�����Ҳ�ӳ��,E->E+T
        first[grammars_left_right[0][0]] = set<char>(); //��ʼ��FIRST��
        last[grammars_left_right[0][0]] = set<char>(); //��ʼ��LAST��
    }
}

///=================================================================================================
/// \fn int PriorityTable::prioity_type(char current, char next)
///
/// \brief ȡ�������ս����Ĺ�ϵ
///
/// \date 2018/6/1
///
/// \param current ����ʽ�Ҳ���ǰ���ַ�
/// \param next    ��һ���ַ�
///
/// \return ��ϵ����
/// 		0:U->...ab...,=
/// 		1:U->...aV...,<
/// 		2:U->...Vb...,>
/// 		3: ���Ƿ��ս��
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
/// \brief �ɲ���ʽ�������ս��������ȹ�ϵ
///
/// \date 2018/6/1
///
/// \param right_str ����ʽ���Ҳ�
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
            for (set_it; set_it != set_end; set_it++) { //���ڵ���һ���ַ���FIRST��
                prioity_table[make_pair(right_str[i], *set_it)] = '<';
            }
        }
        if (prioity_type(right_str[i], right_str[i + 1]) == 2) { //U->...Vb...
            set<char>next_first = last[right_str[i]];
            set<char>::iterator set_it = next_first.begin();
            set<char>::iterator set_end = next_first.end();
            for (set_it; set_it != set_end; set_it++) { //��ǰ�ַ���LAST��
                prioity_table[make_pair(*set_it, right_str[i + 1])] = '>';
            }
        }
    }
}

///=================================================================================================
/// \fn void PriorityTable::make_prioity_table()
///
/// \brief ����FIRST��LAST�������������ȹ�ϵ��
///
/// \date 2018/6/1
///=================================================================================================

void PriorityTable::make_prioity_table() {
    make_first();
    make_last();
    map<char, vector<string>>::iterator it = grammars_map.begin(); //����ʽ��ʼ��
    map<char, vector<string>>::iterator end = grammars_map.end(); //����ʽ��β��
    vector<string>::iterator right_it; //����ʽ�Ҳ���ʼ
    vector<string>::iterator right_end; //����ʽ�Ҳ���β
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
/// \brief ����FIRST��
///
/// \date 2018/5/31
///=================================================================================================

void PriorityTable::make_first() {
    map<char, vector<string>>::iterator it = grammars_map.begin(); //����ʽ��ʼ��
    map<char, vector<string>>::iterator end = grammars_map.end(); //����ʽ��β��
    vector<string>::iterator right_it; //����ʽ�Ҳ���ʼ
    vector<string>::iterator right_end; //����ʽ�Ҳ���β
    char terminal_symbol; //�ս��
    for (it; it != end; it++) { //��������ʽ
        right_it = it->second.begin(); //����ʽ�Ҳ��ֶ���ʼ
        right_end = it->second.end();
        for (right_it; right_it != right_end; right_it++) { //��������ʽ�Ҳ��ֶ�
            if (is_first(*right_it, terminal_symbol)) { //�Ƿ�Ϊ����first����Ԫ�صĶ���
                symbols_stack.push(make_pair(it->first, terminal_symbol));//��������ջ
                first[it->first].insert(terminal_symbol); //��ӵ��󲿶�Ӧ��FIRST��
            }
        }
        while (!symbols_stack.empty()) { //��ջ�ڷ��Ŵ����൱�ڵݹ����FIRST
            char first_value = symbols_stack.top().first; //��ȡջ���ս������Ϊ��Q��a��
            char left = find_first_equivalence(first_value); //���Ҷ�Ӧ�ȼ۲���ʽ�����ظò���ʽ���󲿣�������P=>Q�������Ĳ���ʽ
            if (first_value != left) { //�ҵ����������Ĳ���ʽ
                set<char> temp;
                auto iter = std::set_union(first[left].begin(), first[left].end(), first[first_value].begin(),
                                           first[first_value].end(), std::inserter(temp, temp.begin())); //�󲢼�������Q��FIRST��ӵ�P��FIRST
                first[left] = temp;
            }
            symbols_stack.pop();
        }
    }

}

///=================================================================================================
/// \fn void PriorityTable::make_last()
///
/// \brief ����LAST��
///
/// \date 2018/5/31
///=================================================================================================

void PriorityTable::make_last() {
    map<char, vector<string>>::iterator it = grammars_map.begin(); //����ʽ��ʼ��
    map<char, vector<string>>::iterator end = grammars_map.end(); //����ʽ��β��
    vector<string>::iterator right_it; //����ʽ�Ҳ���ʼ
    vector<string>::iterator right_end; //����ʽ�Ҳ���β
    char terminal_symbol; //�ս��
    for (it; it != end; it++) { //��������ʽ
        right_it = it->second.begin(); //����ʽ�Ҳ��ֶ���ʼ
        right_end = it->second.end();
        for (right_it; right_it != right_end; right_it++) { //��������ʽ�Ҳ��ֶ�
            if (is_last(*right_it, terminal_symbol)) { //�Ƿ�Ϊ����LAST����Ԫ�صĶ���
                symbols_stack.push(make_pair(it->first, terminal_symbol));//��������ջ
                last[it->first].insert(terminal_symbol); //��ӵ��󲿶�Ӧ��FIRST��
            }
        }
        while (!symbols_stack.empty()) { //��ջ�ڷ��Ŵ����൱�ڵݹ����LAST
            char first_value = symbols_stack.top().first; //��ȡջ���ս������Ϊ��Q��a��
            char left = find_last_equivalence(first_value); //���Ҷ�Ӧ�ȼ۲���ʽ�����ظò���ʽ���󲿣�������P=>...Q�Ĳ���ʽ
            if (first_value != left) { //�ҵ����������Ĳ���ʽ
                set<char> temp;
                auto iter = std::set_union(last[left].begin(), last[left].end(), last[first_value].begin(),
                                           last[first_value].end(), std::inserter(temp, temp.begin())); //�󲢼�������Q��LAST��ӵ�P��LAST
                last[left] = temp;
            }
            symbols_stack.pop();
        }
    }
}

///=================================================================================================
/// \fn void PriorityTable::print_first()
///
/// \brief ��ӡFIRST��LAST��
///
/// \date 2018/5/31
///=================================================================================================

void PriorityTable::print_first_last() {
    map<char, set<char>>::iterator it = first.begin();
    map<char, set<char>>::iterator end = first.end();
    if (!is_make_table) {
        cout << "�����������ȹ�ϵ��" << endl;
        return;
    }
    cout << setfill('*') << setw(50) << "FIRST��";
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
    cout << setfill('*') << setw(50) << "LAST��";
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
/// \brief ��ӡ���ȹ�ϵ��
///
/// \date 2018/6/1
///=================================================================================================

void PriorityTable::print_table() {
    cout << setfill('=') << setw(50) << "���ȹ�ϵ��";
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
/// \brief ��������ʽ���Ҳ���ȡ����ʽ����
///
/// \date 2018/6/1
///
/// \param right ����ʽ���Ҳ�
///
/// \return ����ʽ����
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
/// \brief ��ȡ���ȹ�ϵ��.
///
/// \date 2018/6/1
///
/// \return ���ȹ�ϵ��
///=================================================================================================

map<pair<char, char>, char> PriorityTable::get_prioity_table() {
    return prioity_table;
}

///=================================================================================================
/// \fn std::map<char, std::set<char>> PriorityTable::get_first()
///
/// \brief ��ȡfirst����
///
/// \date 2018/6/1
///
/// \return FIRST��
///=================================================================================================

std::map<char, std::set<char>> PriorityTable::get_first() {
    return first;
}

///=================================================================================================
/// \fn std::map<char, std::set<char>> PriorityTable::get_last()
///
/// \brief ��ȡLAST����
///
/// \date 2018/6/1
///
/// \return last��
///=================================================================================================

std::map<char, std::set<char>> PriorityTable::get_last() {
    return last;
}

PriorityTable::~PriorityTable() {
}

///=================================================================================================
/// \fn bool PriorityTable::is_first(string right_str, char &terminal_symbol)
///
/// \brief ����ʽ���Ҳ��Ƿ�������FIRST��Ԫ�ض�����ս��
///
/// \date 2018/5/31
///
/// \param 		    right_str	    ����ʽ�Ҳ�
/// \param [out] terminal_symbol �����������ս�������û����ֵ��Ϊ0
///
/// \return ������������TURE,��������FALSE
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
/// \brief �ж��Ƿ�����LAST��Ԫ�صĶ���
///
/// \date 2018/5/31
///
/// \param 		    right_str	    ����ʽ�Ҳ�
/// \param [out] terminal_symbol �����������ս�������û����ֵ��Ϊ0
///
/// \return ������������TURE,��������FALSE
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
/// \brief �����������Ƶ���right�Ĳ���ʽ����
/// 	   ���������ڲ���ʽ��A->B...,�����right����B���������������󲿾���A
///
/// \date 2018/5/31
///
/// \param right �ò���ʽ���Ҳ�
///
/// \return �����������󲿣���û���򷵻�right
///=================================================================================================

char PriorityTable::find_first_equivalence(char right) {
    map<char, vector<string>>::iterator it = grammars_map.begin();
    map<char, vector<string>>::iterator end = grammars_map.end();
    vector<string>::iterator start_it;
    vector<string>::iterator end_it;
    string temp = "";
    temp.append(1, right);
    for (it; it != end; it++) { //��������ʽ
        start_it = it->second.begin();
        end_it = it->second.end();
        for (start_it; start_it != end_it; start_it++) { //���ҵ���right���Ҳ��ĵ�һ�����ս��
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
/// \brief ����������Ӧ���������Ƶ���right�Ĳ���ʽ����
/// 	   ���������ڲ���ʽ��A->...B,�����right����B���������������󲿾���A
///
/// \date 2018/6/1
///
/// \param right ����ʽ���Ҳ�
///
/// \return ����ʽ����
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
        for (start_it; start_it != end_it; start_it++) { //��������ʽ
            if (start_it->at(start_it->size() - 1) == right) //����ʽ�Ҳ����һ�����ս��
                return it->first;
        }
    }
    return right;
}
