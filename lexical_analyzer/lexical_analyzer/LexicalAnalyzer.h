///=================================================================================================
/// \file LexicalAnalyzer.h
///
/// \brief 定义词法分析器的类
///=================================================================================================

#ifndef LEXICALANALYER
#define LEXICALANALYER
#include <map>
#include<set>
#include <string>
#include <vector>
using namespace std;

///=================================================================================================
/// \enum CharType
///
/// \brief 字符类型对应的值
///=================================================================================================

enum CharType {CHARACTER, NUMBER, SPACE, OPERATE};


///=================================================================================================
/// \class LexicalAnalyzer
///
/// \brief 词法分析器
///
/// \date 2018/5/26
///=================================================================================================

class LexicalAnalyzer {
  public:
    LexicalAnalyzer();
    int read_seed_code(const string file_path);
    void output_seed_code();
    int read_source_code(const string file_path);
    void remove_space();
    int get_char_type(char ch);
    void scan_code();
    void lookup(const string token);
    string get_origin_code();
    int delete_comment();
    std::vector<string> get_result();
    //void get_number();
    ~LexicalAnalyzer();
  protected:

  private:
    ///种别码字典
    map<string, int> seed_code_dict;

    ///待处理的源代码
    string source_code;

    ///原始代码
    string origin_source_code;

    ///源代码中出现的关键字
    map<int, vector<string> > keyword_dict;

    ///源代码中出现的标识符
    map<int, vector<string> > tag_dict;

    ///源代码中的常数
    map<int, vector<string> > const_dict;

    ///源代码中的分隔符
    map<int, vector<string> > split_dict;

    ///运算符
    map<int, vector<string> > opreate_set;

    /// 结果
    vector<string> result;
    std::string joint_str(std::string::iterator &it, std::string::iterator end);
    std::string joint_num(std::string::iterator &it, std::string::iterator end);
    std::string joint_operator(std::string::iterator &it, std::string::iterator end);
    void add_result(const std::string token, int seed_code);
    void format_print(const string token, int seed_code);

};
#endif

