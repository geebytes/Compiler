#include "LexicalAnalyzer.h"
#include "LexicalAnalyzer.h"
#include <fstream>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

LexicalAnalyzer::LexicalAnalyzer() {

}

/**--------------------------------------------------------------------------------------------------
 * \fn int LexicalAnalyzer::read_seed_code(const string file_path)
 *
 * \brief ��ȡ�ֱ��������ļ��������ֱ����ֵ�
 *
 * \date 2018/5/25
 *
 * \param file_path �ֱ��������ļ�·��
 *
 * \return �ɹ�����0ʧ�ܷ���-1
 *-----------------------------------------------------------------------------------------------**/

int LexicalAnalyzer::read_seed_code(const string file_path) {
    ifstream open_file(file_path);
    string seed_code_str;
    vector<string>seed_code_vec;
    if (!open_file.is_open()) {
        printf( "The seed code file open fail\n");
        return -1;
    }
    while (getline(open_file, seed_code_str)) { //���ж�ȡ
        split(seed_code_vec, seed_code_str, is_any_of("\t"), token_compress_on);
        seed_code_dict[seed_code_vec[0]] = seed_code_vec[1];//�����ֵ�ӳ��
        seed_code_vec.clear();
    }
    open_file.close();
    return 0;
}

/**--------------------------------------------------------------------------------------------------
 * \fn void LexicalAnalyzer::output_seed_code()
 *
 * \brief ����ֱ����ֵ�
 *
 * \date 2018/5/25
 *-----------------------------------------------------------------------------------------------**/

void LexicalAnalyzer::output_seed_code() {
    map<string, string>::iterator iter;
    for (iter = seed_code_dict.begin(); iter != seed_code_dict.end(); iter++) {
        printf("%s\t%s\n", iter->first.c_str(), iter->second.c_str());
    }
}

/**--------------------------------------------------------------------------------------------------
 * \fn int LexicalAnalyzer::read_source_code(const string file_path)
 *
 * \brief ��ȡԴ��������ڴ�
 *
 * \date 2018/5/25
 *
 * \param file_path Դ�����ļ�·��
 *
 * \return �ɹ�����0ʧ�ܷ���-1
 *-----------------------------------------------------------------------------------------------**/

int LexicalAnalyzer::read_source_code(const string file_path) {
    ifstream open_file(file_path);
    if (!open_file.is_open()) {
        printf("The seed code file open fail\n");
        return -1;
    }
    source_code = string((std::istreambuf_iterator<char>(open_file)),
                         std::istreambuf_iterator<char>()); //һ���Զ�ȡԴ��������ڴ�
    //cout << source_code << endl;
    origin_source_code = source_code;
    return 0;

}

/**
 * \fn string LexicalAnalyzer::get_origin_code()
 *
 * \brief ��ȡԭʼδ������Ĵ���.
 *
 * \date 2018/5/25
 *
 * \return ԭʼ����.
 */

string LexicalAnalyzer::get_origin_code() {
    return origin_source_code;
}

/**--------------------------------------------------------------------------------------------------
 * \fn int LexicalAnalyzer::delete_comment()
 *
 * \brief ɾ��Դ�����е�ע�Ͳ���
 *
 * \date 2018/5/25
 *
 * \return �ɹ�����0ʧ�ܷ���-1
 *-----------------------------------------------------------------------------------------------**/

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
    cout << source_code;
    return 0;
}

int LexicalAnalyzer::getnb() {
    return 0;

}

LexicalAnalyzer::~LexicalAnalyzer() {

}
