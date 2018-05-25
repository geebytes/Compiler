/*!
 * \file LexicalAnalyzer.h
 * \date 2018/05/24 16:11
 *
 * \author qinzhonghe
 *
 * \brief
 *
 * TODO: long description
 *
 * \note
*/

#ifndef LEXICALANALYER
#define LEXICALANALYER
#include <map>
#include <string>
using namespace std;
/*!
 * \class LexicalAnalyzer
 *
 *
 * \brief
 *
 * TODO: long description
 *
 * \note
 *
 * \author qinzhonghe
 *
 * \version 1.0
 *
 * \date 2018/05/24 16:20
 *
 *
 */
class LexicalAnalyzer {
  public:
    LexicalAnalyzer();
    int read_seed_code(const string file_path);
    void output_seed_code();
    int read_source_code(const string file_path);
    void remove_space();
    void scan_code();
    void lookup();
    string get_origin_code();
    int delete_comment();
    ~LexicalAnalyzer();
  protected:

  private:
    ///�ֱ����ֵ�
    map<string, string> seed_code_dict;

    ///�������Դ����
    string source_code;

    ///ԭʼ����
    string origin_source_code;
};
#endif

