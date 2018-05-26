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
/// \brief 读取种别码配置文件，生成种别码字典
///
/// \date 2018/5/25
///
/// \param file_path 种别码配置文件路径
///
/// \return 成功返回0失败返回-1
///=================================================================================================

int LexicalAnalyzer::read_seed_code(const string file_path) {
    ifstream open_file(file_path);
    string seed_code_str;
    vector<string>seed_code_vec;
    if (!open_file.is_open()) {
        printf( "The seed code file open fail\n");
        return -1;
    }
    while (getline(open_file, seed_code_str)) { //按行读取
        boost::split(seed_code_vec, seed_code_str, boost::is_any_of("\t"), boost::token_compress_on);
        seed_code_dict[seed_code_vec[0]] = std::stoi(seed_code_vec[1]);//生成字典映射
        seed_code_vec.clear();
    }
    open_file.close();
    return 0;
}

///=================================================================================================
/// \fn void LexicalAnalyzer::output_seed_code()
///
/// \brief 输出种别码字典
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
/// \brief 读取源代码存入内存.
///
/// \date 2018/5/25
///
/// \param file_path 源代码文件路径.
///
/// \return 成功返回0失败返回-1.
///=================================================================================================

int LexicalAnalyzer::read_source_code(const string file_path) {
    ifstream open_file(file_path);
    if (!open_file.is_open()) {
        printf("The seed code file open fail\n");
        return -1;
    }
    source_code = string((std::istreambuf_iterator<char>(open_file)),
                         std::istreambuf_iterator<char>()); //一次性读取源代码存入内存
    origin_source_code = source_code;
    open_file.close();
    return 0;

}

///=================================================================================================
/// \fn void LexicalAnalyzer::remove_space()
///
/// \brief 利用正则表达式除去多余的空格包括回车、换行、制表
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
/// \brief 获取字符类型，数字/字母/分隔符
///
/// \date 2018/5/26
///
/// \param ch 待判断的字符
///
/// \return 字符类型
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
/// \brief 扫描代码，进行分析获取种别码
///
/// \date 2018/5/26
///=================================================================================================

void LexicalAnalyzer::scan_code() {
    string::iterator it = source_code.begin();
    string::iterator end = source_code.end();
    string::iterator star = source_code.begin();
    string token = ""; //扫描出来的字符串
    while (it != end) { //遍历代码
        int char_type; //字符类型
        char_type = get_char_type(*it);
        switch (char_type) {
        case CHARACTER:
            token = joint_str(it, end); //拼接字符串
            lookup(token);
            break;
        case NUMBER:
            token = joint_num(it, end); //拼接无符号整数常量
            lookup(token);
            break;
        case OPERATE:
            if(isspace(*it)) //跳过空格
                break;
            token.clear();
            token.append(1, *it);
            if (seed_code_dict.find(token) != seed_code_dict.end()) { //分隔符或运算符
                if (seed_code_dict[token] == 5) {
                    lookup(token);
                } else { //拼接运算符
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
/// \brief 添加处理结果
///
/// \date 2018/5/26
///
/// \param token	 已经判别字符串
/// \param seed_code 种别码
///=================================================================================================

void LexicalAnalyzer::add_result(const std::string token, int seed_code) {
    boost::format result_format("(%d,%s)");
    result_format % seed_code % token;
    result.push_back(result_format.str());
}

///=================================================================================================
/// \fn void LexicalAnalyzer::format_print(const string token, int seed_code)
///
/// \brief 格式化输出结果
///
/// \date 2018/5/26
///
/// \param token	 经过判断得到的字符串
/// \param seed_code 种别码
///=================================================================================================

void LexicalAnalyzer::format_print(const string token, int seed_code) {
    boost::format output_format("(%d,%s)");
    output_format % seed_code % token;
    std::cout << output_format.str() << endl;
}

///=================================================================================================
/// \fn void LexicalAnalyzer::lookup(const string token)
///
/// \brief Looks up 获取最后结果
///
/// \date 2018/5/26
///
/// \param 已经判断过的字符串
///=================================================================================================

void LexicalAnalyzer::lookup(const string token) {
    cmatch what;
    regex num_reg("/^-?\d+(?:\.\d*)?(?:e[+\-]?\d+)?$/i"); //数字正则表达式
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
/// \brief 获取原始未经处理的代码.
///
/// \date 2018/5/25
///
/// \return 原始代码.
///=================================================================================================

inline string LexicalAnalyzer::get_origin_code() {
    return origin_source_code;
}

///=================================================================================================
/// \fn int LexicalAnalyzer::delete_comment()
///
/// \brief 利用正则表达式删除源代码中的注释部分
///
/// \date 2018/5/25
///
/// \return 0
///=================================================================================================

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
    //cout << source_code;
    return 0;
}

///=================================================================================================
/// \fn std::vector<std::string> LexicalAnalyzer::get_result()
///
/// \brief 获取最后结果
///
/// \date 2018/5/26
///
/// \return 最后的结果
///=================================================================================================

std::vector<std::string> LexicalAnalyzer::get_result() {
    return result;
}

// void LexicalAnalyzer::get_number() {
//     string reg_str = "^-?[1-9]\d*$";
//     string::const_iterator start = source_code.begin(), end = source_code.end();
//     size_t pos, num;
//     boost::regex reg(reg_str);
//     boost::smatch match; //保存第一个匹配结果
//     boost::match_flag_type flags = boost::match_default;
//     while (regex_search(start, end, match, reg, flags)) { //遍历搜索
//         pos = match[0].first - source_code.begin();
//         num = match[0].second - match[0].first;
//         std::cout << source_code.substr(pos, num) << endl;
//         source_code.erase(pos, num);
//         //start = source_code.begin() + pos;
//         start = match[0].second;//重新获取起始位置
//
//         end = source_code.end();//重要，此时字符串已经被改变，需要重新获得新的end()
//         // 匹配方式
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
/// \brief 拼接字符串
///
/// \date 2018/5/26
///
/// \param [in,out] it  字符串起始位置
/// \param 		    end 字符串末尾
///
/// \return 拼接出来的字符串
///=================================================================================================

std::string LexicalAnalyzer::joint_str(string::iterator &it, string::iterator end) {
    string token = "";
    while (get_char_type(*it) != OPERATE && it != end) { //拼接字母
        token.append(1, *it);
        it++;
    }
    it--;
    return token;
}

///=================================================================================================
/// \fn std::string LexicalAnalyzer::joint_num(string::iterator &it, string::iterator end)
///
/// \brief 拼接无符号整型数
///
/// \date 2018/5/26
///
/// \param [in,out] it  字符串起始位置
/// \param 		    end 字符串末尾
///
/// \return 无符号整形数
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
/// \brief 拼接多符号运算符
///
/// \date 2018/5/26
///
/// \param [in,out] it  字符串起始位置
/// \param 		    end 字符串终止位置
///
/// \return 运算符
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
