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
 * \brief 读取种别码配置文件，生成种别码字典
 *
 * \date 2018/5/25
 *
 * \param file_path 种别码配置文件路径
 *
 * \return 成功返回0失败返回-1
 *-----------------------------------------------------------------------------------------------**/

int LexicalAnalyzer::read_seed_code(const string file_path) {
    ifstream open_file(file_path);
    string seed_code_str;
    vector<string>seed_code_vec;
    if (!open_file.is_open()) {
        printf( "The seed code file open fail\n");
        return -1;
    }
    while (getline(open_file, seed_code_str)) { //按行读取
        split(seed_code_vec, seed_code_str, is_any_of("\t"), token_compress_on);
        seed_code_dict[seed_code_vec[0]] = seed_code_vec[1];//生成字典映射
        seed_code_vec.clear();
    }
    open_file.close();
    return 0;
}

/**--------------------------------------------------------------------------------------------------
 * \fn void LexicalAnalyzer::output_seed_code()
 *
 * \brief 输出种别码字典
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
 * \brief 读取源代码存入内存
 *
 * \date 2018/5/25
 *
 * \param file_path 源代码文件路径
 *
 * \return 成功返回0失败返回-1
 *-----------------------------------------------------------------------------------------------**/

int LexicalAnalyzer::read_source_code(const string file_path) {
    ifstream open_file(file_path);
    if (!open_file.is_open()) {
        printf("The seed code file open fail\n");
        return -1;
    }
    source_code = string((std::istreambuf_iterator<char>(open_file)),
                         std::istreambuf_iterator<char>()); //一次性读取源代码存入内存
    //cout << source_code << endl;
    origin_source_code = source_code;
    return 0;

}

/**
 * \fn string LexicalAnalyzer::get_origin_code()
 *
 * \brief 获取原始未经处理的代码.
 *
 * \date 2018/5/25
 *
 * \return 原始代码.
 */

string LexicalAnalyzer::get_origin_code() {
    return origin_source_code;
}

/**--------------------------------------------------------------------------------------------------
 * \fn int LexicalAnalyzer::delete_comment()
 *
 * \brief 删除源代码中的注释部分
 *
 * \date 2018/5/25
 *
 * \return 成功返回0失败返回-1
 *-----------------------------------------------------------------------------------------------**/

int LexicalAnalyzer::delete_comment() {
    string reg_str = "('(?:[^\\\\']|\\\\.)*'|\"(?:[^\\\\\"]|\\\\.)*\")|" //跳过" "/' '部分
                     "(?<comment>//[^\\n]*|/\\*.*?\\*/)"; //单行注释，多行注释
    string::const_iterator start = source_code.begin(), end = source_code.end();
    size_t pos, num;
    boost::regex reg(reg_str);
    boost::smatch match; //保存第一个匹配结果
    boost::match_flag_type flags = boost::match_default;
    while (regex_search(start, end, match, reg, flags)) { //遍历搜索
        pos = match[0].first - source_code.begin();
        num = match[0].second - match[0].first;

        if (match["comment"].matched) {
            source_code.erase(pos, num);
            start = source_code.begin() + pos;
        } else {
            start = match[0].second;//重新获取起始位置
        }

        end = source_code.end();//重要，此时字符串已经被改变，需要重新获得新的end()
        // 匹配方式
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
