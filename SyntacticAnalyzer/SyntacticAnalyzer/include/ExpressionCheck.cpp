#include "ExpressionCheck.h"
#include <regex>
#include <iterator>
#include"boost/format.hpp"
#include <iomanip>
ExpressionCheck::ExpressionCheck() {
    left_prime_phrase = "";
    is_move = true;
    error_info.push_back("ȱ�ٱ��ʽ"); //eg.
    error_info.push_back("���ʽ��ȱ�������"); //eg .ii
    error_info.push_back("���ż��ޱ��ʽ"); //eg.()
    error_info.push_back("�Ƿ�������");
    error_info.push_back("���ʽ��ȱ�������"); //eg. )(
    error_info.push_back("��ȷ");
    error_info.push_back("�Ƿ�������");
    expression_index = 0;
    setp = 1;
}

///=================================================================================================
/// \fn void ExpressionCheck::get_grammar(std::vector<std::string> grammars)
///
/// \brief ��ȡ�ķ�
///
/// \date 2018/6/3
///
/// \param grammars �洢����ʽ������
///=================================================================================================

void ExpressionCheck::get_grammar(std::vector<std::string> grammars) {
    priority_table.get_grammar(grammars);
    this->grammars = grammars;
}

///=================================================================================================
/// \fn void ExpressionCheck::get_terminal_symbol(set<char> terminal_symbols)
///
/// \brief ��ȡ�ս����
/// \date 2018/6/3
///
/// \param terminal_symbols �ս������
///=================================================================================================

void ExpressionCheck::get_terminal_symbol(set<char> terminal_symbols) {
    priority_table.get_terminal_symbol(terminal_symbols);
    this->terminal_symbols = terminal_symbols;
}

///=================================================================================================
/// \fn void ExpressionCheck::make_priority_table()
///
/// \brief �������ȹ�ϵ��.
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
/// \brief ������
///
/// \date 2018/6/3
///
/// \param left_prime_phrase �����ض���
/// \param normalize_char    ��Լ�ķ���
///
/// \return �������
///=================================================================================================

int ExpressionCheck::check_error(string left_prime_phrase, char normalize_char) {

    if (normalize_char == 'i') { //���ʽ�����Ƿ���������
        int index = left_prime_phrase.find(normalize_char);
        if (index != left_prime_phrase.size() - 1 != 0 && left_prime_phrase[index + 1] == 'i') { //���ʽ�����ȱ�������,eg. ii
            return DEFECT_OPERATOR;
        }
        if ((index != 0 && (terminal_symbols.find(index - 1) == terminal_symbols.end()))) //���ʽ�Ҳ���ȱ�������
            return EXP_NO_OPERATOR;
        if ((index != left_prime_phrase.size() - 1 && (terminal_symbols.find(index + 1) == terminal_symbols.end()))) //���ʽ�����ȱ�������
            return EXP_NO_OPERATOR;
    }
    if (normalize_char == '(' || normalize_char == ')') { //���źϷ��Լ��
        int left_index = left_prime_phrase.find('(');
        int right_index = left_prime_phrase.find(')');
        if (left_index != -1 && right_index != -1) { //���ż��Ƿ���ڱ��ʽ,eg. (i)
            for (int i = left_index; i != right_index; i++) {
                if (terminal_symbols.find(left_prime_phrase[i]) == terminal_symbols.end())
                    return OK;
            }
            return BRACKETS_NO_EXP;
        }
        if (left_index == left_prime_phrase.size() - 1) { //�Ƿ�������
            return INVALID_LEFT_BRACKET;
        }
        if (left_index + 1 == right_index) { //ȱ���������eg. )(
            return DEFECT_OPERATOR;
        }
        if (left_index != -1 && right_index == -1) { //�Ƿ�������
            return INVALID_LEFT_BRACKET;
        }
        if (left_index == -1 && right_index != -1) { //�Ƿ�������
            return INVALID_RIGHT_BRACKET;
        }
    }
    if (terminal_symbols.find(normalize_char) != terminal_symbols.end()) { //��������Ƿ���ڷ��ս��
        int index = left_prime_phrase.find(normalize_char);
        if ((index != 0 && (terminal_symbols.find(index - 1) != terminal_symbols.end()))) //��������ȱ�ٱ��ʽ
            return EXPRESSION_ERROR;
        if ((index != left_prime_phrase.size() - 1 && (terminal_symbols.find(index + 1) != terminal_symbols.end()))) //������Ҳ�ȱ�ٱ��ʽ
            return EXPRESSION_ERROR;
    }
    return OK;
}

///=================================================================================================
/// \fn char ExpressionCheck::skip_no_terminal(char top_value)
///
/// \brief �������ս��
///
/// \date 2018/6/3
///
/// \param top_value ����ջջ��Ԫ��
///
/// \return �ս��ջ��
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
/// \brief ��Լ����
///
/// \date 2018/6/3
///
/// \param top_value ջ��Ԫ��
/// \param exp_value ���ʽ����ǰ�����ַ�
///
/// \return ��Լ���ջ��Ԫ��
///=================================================================================================

char ExpressionCheck::reduction(char top_value, char exp_value) {
    char q = top_value; //ջ��Ԫ�أ������ض���ĵ�һ�����ս��
    char a = exp_value; //���봮��
    char p = top_value;

    while ((table[make_pair(p, a)] == '>' || a == '#') && !symbols_stack.empty()) { //ջ�����ȼ��������봮��
        left_prime_phrase.append(1, top_value); //����ض�����ַ�
        symbols_stack.pop();
        top_value = symbols_stack.top();
        top_value = skip_no_terminal(top_value); //�������ս��
        if (table[make_pair(top_value, q)] == '=' || table[make_pair(top_value, q)] == '<' || top_value == '#') { //���������ض�������һ���ս��
            if (table[make_pair(top_value, q)] == '=') {
                left_prime_phrase.append(1, top_value);
                symbols_stack.pop();
            }
            reverse(left_prime_phrase.begin(), left_prime_phrase.end()); //�����ض���ķ�ת

            top_value = symbols_stack.top(); //����ջ��Ԫ��
            if (match_production_left(left_prime_phrase)) { //�Ƿ������Լ������
                symbols_stack.push('V'); //�滻�����ض���
                is_move = false; //���ƽ�
                left_phrase = left_prime_phrase; //���������������ض���
            } else {
                int error_type = check_error(left_prime_phrase, q);
                if (error_type != OK) {
                    error_record[expression_index] = error_info[error_type];
                }
                is_move = true;
                left_phrase.clear();
            }
            left_prime_phrase.clear(); //��ոò���������ض���
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
/// \brief ����ʽ��׼����������ʽ�Ҳ����еķ��ս���滻ΪV
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
/// \brief �Ƿ�����ܹ��Ƶ�����������ʽ���Ҳ��Ĳ���ʽ��.
///
/// \date 2018/6/3
///
/// \param right_str ����ʽ�Ҳ�
///
/// \return True �������, false ���������
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
/// \brief ���������¼
///
/// \date 2018/6/4
///
/// \param index   ��ǰ���ʽ��λ��
/// \param prioity ջ���뵱ǰ���ʽ�ַ��Ĺ�ϵ
/// \param left    �����ض���
/// \param act     ����
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
/// \brief �����ʽ
///
/// \date 2018/6/3
///
/// \param expression �����ı��ʽ
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

    while (expression[index] != '#') { //�������ʽ��
        expression_index = index;
        is_move = true;
        char a = expression[index];
        top_value = symbols_stack.top();
        top_value = skip_no_terminal(top_value);
        if (top_value == 0) { //����ջΪ��
            break;
        }
        char q = top_value;
        if (table.count(make_pair(top_value, a)) == 0 && top_value != '#') { //ջ���ս�������봮��ǰ���ս���޹�ϵ
            error_record[expression_index] = error_info[EXP_NO_OPERATOR];
        }
        save_analysis_step(index, table[make_pair(top_value, a)], left_phrase, "�ƽ�");
        top_value = reduction(q, a); //��Լ����
        if (!left_phrase.empty()) { //��Լ
            save_analysis_step(index, table[make_pair(top_value, a)], left_phrase, "��Լ");
            left_phrase.clear();
        }
        if (is_move || top_value == '#' || table[make_pair(top_value, a)] == '<' || table[make_pair(top_value, a)] == '=') { //�ƽ�
            symbols_stack.push(a);
        } else { //���봮���ƶ�
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
            save_analysis_step(index, '>', left_phrase, "��Լ");

    }
    left_phrase.clear();
    if (terminal_symbols.find(symbols_stack.top()) != terminal_symbols.end() || symbols_stack.top() == '#') {
        if(error_record.find(expression_index) == error_record.end())
            error_record[expression_index] = error_info[EXPRESSION_ERROR]; //�������ȱ�ٱ��ʽ
        save_analysis_step(index, ' ', left_phrase, "����");

    } else
        save_analysis_step(index, ' ', left_phrase, "����");
    setp = 0;
    return 0;
}

///=================================================================================================
/// \fn void ExpressionCheck::print_info()
///
/// \brief ��ӡ������Ϣ
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
/// \brief ��ӡ����ջ��״̬
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
/// \brief ��ӡÿһ����״̬.
///
/// \date 2018/6/3
///=================================================================================================

void ExpressionCheck::print_step() {
    boost::format fmt("%-20s|%-20s|%-20s|%-20s|%-20s|%-20s");
    fmt % "����" % "����ջ" % "��ϵ" % "���봮" % "�����ض���" % "����"; //���ÿһ����״̬
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
/// \brief ���������Ϣ
/// \date 2018/6/3
///=================================================================================================

void ExpressionCheck::print_error() {
    boost::format fmt("%-20s|%-20s");
    fmt % "����λ��" % "��������"; //��������
    string output_str = fmt.str();
    cout << output_str << endl;
    cout << setfill('-') << setw(100) << "" << endl;
    map<int, string>::iterator it = error_record.begin();
    map<int, string>::iterator end = error_record.end();
    for (it; it != end; it++) {
        boost::format fmt("%-20s|%-20s");
        fmt % it->first % it->second; //��������
        string output_str = fmt.str();
        cout << output_str << endl;
        cout << setfill('-') << setw(100) << "" << endl;
    }
}

///=================================================================================================
/// \fn void ExpressionCheck::reset()
///
/// \brief ����һЩ��¼��Ϣ
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
/// \brief ��ȡ��������
///
/// \date 2018/6/3
///
/// \return ����������Ϣ
///=================================================================================================

std::map<int, std::vector<std::string>> ExpressionCheck::get_setp() {
    return analysis_info;
}

///=================================================================================================
/// \fn std::map<int, std::string> ExpressionCheck::get_error()
///
/// \brief ��ȡ������Ϣ
///
/// \date 2018/6/3
///
/// \return ������Ϣ
///=================================================================================================

std::map<int, std::string> ExpressionCheck::get_error() {
    return error_record;
}

///=================================================================================================
/// \fn std::map<std::pair<char, char>, char> ExpressionCheck::get_priority_table()
///
/// \brief ��ȡ���ȹ�ϵ��
///
/// \date 2018/6/3
///
/// \return ���ȹ�ϵ��
///=================================================================================================

std::map<std::pair<char, char>, char> ExpressionCheck::get_priority_table() {
    return table;
}

///=================================================================================================
/// \fn std::map<char, std::set<char>> ExpressionCheck::get_last()
///
/// \brief ��ȡLAST��
///
/// \date 2018/6/3
///
/// \return LAST��.
///=================================================================================================

std::map<char, std::set<char>> ExpressionCheck::get_last() {
    return priority_table.get_last();
}

///=================================================================================================
/// \fn std::map<char, std::set<char>> ExpressionCheck::get_first()
///
/// \brief ��ȡFIRST��
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
/// \brief ��ȡ����ջ������
///
/// \date 2018/6/3
///
/// \return ����ջ�����ݣ����ҵ���
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
