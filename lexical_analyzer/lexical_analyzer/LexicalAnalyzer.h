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
 * \class classname
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
    ~LexicalAnalyzer();
  protected:

  private:
    ///ÖÖ±ðÂë×Öµä
    map<string, string> seed_code_dict;
};
#endif

