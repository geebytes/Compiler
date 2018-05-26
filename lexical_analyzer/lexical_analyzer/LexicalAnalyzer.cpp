#include "LexicalAnalyzer.h"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/regex.hpp>
#include <boost/format.hpp>
#include <regex>
#include <iterator>
#include <cctype>


LexicalAnalyzer::LexicalAnalyzer() {

}


///=================================================================================================
/// \fn int LexicalAnalyzer::read_seed_code(const string file_path)
///
/// \brief ��ȡ�ֱ��������ļ��������ֱ����ֵ�
///
/// \date 2018/5/25
///
/// \param file_path �ֱ��������ļ�·��
///
/// \return �ɹ�����0ʧ�ܷ���-1
///=================================================================================================

int LexicalAnalyzer::read_seed_code(const string file_path) {
    ifstream open_file(file_path);
    string seed_code_str;
    vector<string>seed_code_vec;
    if (!open_file.is_open()) {
        printf( "The seed code file open fail\n");
        return -1;
    }
    while (getline(open_file, seed_code_str)) { //���ж�ȡ
        boost::split(seed_code_vec, seed_code_str, boost::is_any_of("\t"), boost::token_compress_on);
        seed_code_dict[seed_code_vec[0]] = std::stoi(seed_code_vec[1]);//�����ֵ�ӳ��
        seed_code_vec.clear();
    }
    open_file.close();
    return 0;
}

///=================================================================================================
/// \fn void LexicalAnalyzer::output_seed_code()
///
/// \brief ����ֱ����ֵ�
///
/// \date 2018/5/25
///=================================================================================================

void LexicalAnalyzer::output_seed_code() {
    map<string, int>::iterator iter;
    for (iter = seed_code_dict.begin(); iter != seed_code_dict.end(); iter++) {
        printf("%s\t%d\n", iter->first.c_str(), *iter);
    }
}

///=================================================================================================
/// \fn int LexicalAnalyzer::read_source_code(const string file_path)
///
/// \brief ��ȡԴ��������ڴ�.
///
/// \date 2018/5/25
///
/// \param file_path Դ�����ļ�·��.
///
/// \return �ɹ�����0ʧ�ܷ���-1.
///=================================================================================================

int LexicalAnalyzer::read_source_code(const string file_path) {
    ifstream open_file(file_path);
    if (!open_file.is_open()) {
        printf("The seed code file open fail\n");
        return -1;
    }
    source_code = string((std::istreambuf_iterator<char>(open_file)),
                         std::istreambuf_iterator<char>()); //һ���Զ�ȡԴ��������ڴ�
    origin_source_code = source_code;
    open_file.close();
    return 0;

}

///=================================================================================================
/// \fn void LexicalAnalyzer::remove_space()
///
/// \brief ����������ʽ��ȥ����Ŀո�����س������С��Ʊ�
///
/// \date 2018/5/25
///=================================================================================================

void LexicalAnalyzer::remove_space() {
    string reg_str = "\t|\r|\n";
    std::regex reg(reg_str);
    string::const_iterator start = source_code.begin(), end = source_code.end();
    source_code = std::regex_replace(source_code, reg, "");
    //std::cout << source_code;
}

///=================================================================================================
/// \fn int LexicalAnalyzer::get_char_type(char ch)
///
/// \brief ��ȡ�ַ����ͣ�����/��ĸ/�ָ���
///
/// \date 2018/5/26
///
/// \param ch ���жϵ��ַ�
///
/// \return �ַ�����
///=================================================================================================

int LexicalAnalyzer::get_char_type(char ch) {
    if (isalpha(ch))
        return CharType::CHARACTER;
    else if (isdigit(ch))
        return CharType::NUMBER;
    else
        return CharType::OPERATE;
}

///=================================================================================================
/// \fn void LexicalAnalyzer::scan_code()
///
/// \brief ɨ����룬���з�����ȡ�ֱ���
///
/// \date 2018/5/26
///=================================================================================================

void LexicalAnalyzer::scan_code() {
    string::iterator it = source_code.begin();
    string::iterator end = source_code.end();
    string::iterator star = source_code.begin();
    string token = ""; //ɨ��������ַ���
    while (it != end) { //��������
        int char_type; //�ַ�����
        char_type = get_char_type(*it);
        switch (char_type) {
        case CHARACTER:
            token = joint_str(it, end); //ƴ���ַ���
            lookup(token);
            break;
        case NUMBER:
            token = joint_num(it, end); //ƴ���޷�����������
            lookup(token);
            break;
        case OPERATE:
            if(isspace(*it)) //�����ո�
                break;
            token.clear();
            token.append(1, *it);
            if (seed_code_dict.find(token) != seed_code_dict.end()) { //�ָ����������
                if (seed_code_dict[token] == 5) {
                    lookup(token);
                } else { //ƴ�������
                    token = joint_operator(it, end);
                    lookup(token);
                }
            }
            break;
        default:
            break;
        }
        it++;
    }
}

///=================================================================================================
/// \fn void LexicalAnalyzer::add_result(const std::string token, int seed_code)
///
/// \brief ��Ӵ�����
///
/// \date 2018/5/26
///
/// \param token	 �Ѿ��б��ַ���
/// \param seed_code �ֱ���
///=================================================================================================

void LexicalAnalyzer::add_result(const std::string token, int seed_code) {
    boost::format result_format("(%d,%s)");
    result_format % seed_code % token;
    result.push_back(result_format.str());
}

///=================================================================================================
/// \fn void LexicalAnalyzer::format_print(const string token, int seed_code)
///
/// \brief ��ʽ��������
///
/// \date 2018/5/26
///
/// \param token	 �����жϵõ����ַ���
/// \param seed_code �ֱ���
///=================================================================================================

void LexicalAnalyzer::format_print(const string token, int seed_code) {
    boost::format output_format("(%d,%s)");
    output_format % seed_code % token;
    std::cout << output_format.str() << endl;
}

///=================================================================================================
/// \fn void LexicalAnalyzer::lookup(const string token)
///
/// \brief Looks up ��ȡ�����
///
/// \date 2018/5/26
///
/// \param �Ѿ��жϹ����ַ���
///=================================================================================================

void LexicalAnalyzer::lookup(const string token) {
    cmatch what;
    regex num_reg("/^-?\d+(?:\.\d*)?(?:e[+\-]?\d+)?$/i"); //����������ʽ
    if (seed_code_dict.find(token) != seed_code_dict.end()) {
        //format_print(token, seed_code_dict[token]);
        add_result(token, seed_code_dict[token]);
    } else if (regex_match(token.c_str(), what, num_reg)) {
        //format_print(token, 3);
        add_result(token, 3);
    } else {
        //format_print(token, 2);
        add_result(token, 2);
    }
}

///=================================================================================================
/// \fn string LexicalAnalyzer::get_origin_code()
///
/// \brief ��ȡԭʼδ������Ĵ���.
///
/// \date 2018/5/25
///
/// \return ԭʼ����.
///=================================================================================================

inline string LexicalAnalyzer::get_origin_code() {
    return origin_source_code;
}

///=================================================================================================
/// \fn int LexicalAnalyzer::delete_comment()
///
/// \brief ����������ʽɾ��Դ�����е�ע�Ͳ���
///
/// \date 2018/5/25
///
/// \return 0
///=================================================================================================

int LexicalAnalyzer::delete_comment() {
    string reg_str = "('(?:[^\\\\']|\\\\.)*'|\"(?:[^\\\\\"]|\\\\.)*\")|" //����" "/' '����
                     "(?<comment>//[^\\n]*|/\\*.*?\\*/)"; //����ע�ͣ�����ע��
    string::const_iterator start = source_code.begin(), end = source_code.end();
    size_t pos, num;
    boost::regex reg(reg_str);
    boost::smatch match; //�����һ��ƥ����
    boost::match_flag_type flags = boost::match_default;
    while (regex_search(start, end, match, reg, flags)) { //��������
        pos = match[0].first - source_code.begin();
        num = match[0].second - match[0].first;

        if (match["comment"].matched) {
            source_code.erase(pos, num);
            start = source_code.begin() + pos;
        } else {
            start = match[0].second;//���»�ȡ��ʼλ��
        }

        end = source_code.end();//��Ҫ����ʱ�ַ����Ѿ����ı䣬��Ҫ���»���µ�end()
        // ƥ�䷽ʽ
        if (start != source_code.begin()) {
            flags |= boost::match_prev_avail;
            flags |= boost::match_not_bob;
        }
    }
    //cout << source_code;
    return 0;
}

///=================================================================================================
/// \fn std::vector<std::string> LexicalAnalyzer::get_result()
///
/// \brief ��ȡ�����
///
/// \date 2018/5/26
///
/// \return ���Ľ��
///=================================================================================================

std::vector<std::string> LexicalAnalyzer::get_result() {
    return result;
}

// void LexicalAnalyzer::get_number() {
//     string reg_str = "^-?[1-9]\d*$";
//     string::const_iterator start = source_code.begin(), end = source_code.end();
//     size_t pos, num;
//     boost::regex reg(reg_str);
//     boost::smatch match; //�����һ��ƥ����
//     boost::match_flag_type flags = boost::match_default;
//     while (regex_search(start, end, match, reg, flags)) { //��������
//         pos = match[0].first - source_code.begin();
//         num = match[0].second - match[0].first;
//         std::cout << source_code.substr(pos, num) << endl;
//         source_code.erase(pos, num);
//         //start = source_code.begin() + pos;
//         start = match[0].second;//���»�ȡ��ʼλ��
//
//         end = source_code.end();//��Ҫ����ʱ�ַ����Ѿ����ı䣬��Ҫ���»���µ�end()
//         // ƥ�䷽ʽ
// //         if (start != source_code.begin()) {
// //             flags |= boost::match_prev_avail;
// //             flags |= boost::match_not_bob;
// //         }
//     }
//     cout << source_code;
// }

LexicalAnalyzer::~LexicalAnalyzer() {

}

///=================================================================================================
/// \fn std::string LexicalAnalyzer::joint_str(string::iterator &it, string::iterator end)
///
/// \brief ƴ���ַ���
///
/// \date 2018/5/26
///
/// \param [in,out] it  �ַ�����ʼλ��
/// \param 		    end �ַ���ĩβ
///
/// \return ƴ�ӳ������ַ���
///=================================================================================================

std::string LexicalAnalyzer::joint_str(string::iterator &it, string::iterator end) {
    string token = "";
    while (get_char_type(*it) != OPERATE && it != end) { //ƴ����ĸ
        token.append(1, *it);
        it++;
    }
    it--;
    return token;
}

///=================================================================================================
/// \fn std::string LexicalAnalyzer::joint_num(string::iterator &it, string::iterator end)
///
/// \brief ƴ���޷���������
///
/// \date 2018/5/26
///
/// \param [in,out] it  �ַ�����ʼλ��
/// \param 		    end �ַ���ĩβ
///
/// \return �޷���������
///=================================================================================================

std::string LexicalAnalyzer::joint_num(string::iterator &it, string::iterator end) {
    string token = "";
    while (get_char_type(*it) == NUMBER && it != end) {
        token.append(1, *it);
        it++;
    }
    it--;
    return token;
}

///=================================================================================================
/// \fn std::string LexicalAnalyzer::joint_operator(string::iterator &it, string::iterator end)
///
/// \brief ƴ�Ӷ���������
///
/// \date 2018/5/26
///
/// \param [in,out] it  �ַ�����ʼλ��
/// \param 		    end �ַ�����ֹλ��
///
/// \return �����
///=================================================================================================

std::string LexicalAnalyzer::joint_operator(string::iterator &it, string::iterator end) {
    string token = "";
    string last_str = "";
    while (get_char_type(*it) == OPERATE && it != end) {
        last_str = token;
        token.append(1, *it);
        if (seed_code_dict.find(token) != seed_code_dict.end())
            it++;
        else
            return last_str;
    }
    it--;
    return token;
}
