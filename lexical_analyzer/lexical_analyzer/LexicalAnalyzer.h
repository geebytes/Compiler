///=================================================================================================
/// \file LexicalAnalyzer.h
///
/// \brief ����ʷ�����������
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
/// \brief �ַ����Ͷ�Ӧ��ֵ
///=================================================================================================

enum CharType {CHARACTER, NUMBER, SPACE, OPERATE};


///=================================================================================================
/// \class LexicalAnalyzer
///
/// \brief �ʷ�������
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
    ///�ֱ����ֵ�
    map<string, int> seed_code_dict;

    ///�������Դ����
    string source_code;

    ///ԭʼ����
    string origin_source_code;

    ///Դ�����г��ֵĹؼ���
    map<int, vector<string> > keyword_dict;

    ///Դ�����г��ֵı�ʶ��
    map<int, vector<string> > tag_dict;

    ///Դ�����еĳ���
    map<int, vector<string> > const_dict;

    ///Դ�����еķָ���
    map<int, vector<string> > split_dict;

    ///�����
    map<int, vector<string> > opreate_set;

    /// ���
    vector<string> result;
    std::string joint_str(std::string::iterator &it, std::string::iterator end);
    std::string joint_num(std::string::iterator &it, std::string::iterator end);
    std::string joint_operator(std::string::iterator &it, std::string::iterator end);
    void add_result(const std::string token, int seed_code);
    void format_print(const string token, int seed_code);

};
#endif

