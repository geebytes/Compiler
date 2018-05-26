#include "LexicalAnalyzer.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
int main() {
    LexicalAnalyzer lex_analysis;
    lex_analysis.read_seed_code("seed_code.txt");
    //lex_analysis.output_seed_code();
    lex_analysis.read_source_code("test.c");
    //std::cout << lex_analysis.get_origin_code();
    lex_analysis.delete_comment();
    lex_analysis.remove_space();
    //lex_analysis.get_number();
    lex_analysis.scan_code();
    std::vector<std::string>output_result = lex_analysis.get_result();
    std::vector<std::string>::iterator it;
    for (it = output_result.begin(); it != output_result.end(); it++) {
        std::cout << *it << endl;
    }
    system("pause");
}