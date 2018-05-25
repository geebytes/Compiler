#include "LexicalAnalyzer.h"
#include <stdlib.h>
#include <iostream>
int main() {
    LexicalAnalyzer lex_analysis;
    //lex_analysis.read_seed_code("seed_code.txt");
    //lex_analysis.output_seed_code();
    lex_analysis.read_source_code("LexicalAnalyzer.cpp");
    //std::cout << lex_analysis.get_origin_code();
    lex_analysis.delete_comment();
    lex_analysis.remove_space();
    system("pause");
}