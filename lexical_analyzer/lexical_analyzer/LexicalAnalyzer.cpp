#include "LexicalAnalyzer.h"
#include "LexicalAnalyzer.h"
#include <fstream>
#include <stdio.h>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace std;
using namespace boost;
LexicalAnalyzer::LexicalAnalyzer() {

}

int LexicalAnalyzer::read_seed_code(const string file_path) {
    ifstream open_file(file_path);
    string seed_code_str;
    vector<string>seed_code_vec;
    if (!open_file.is_open()) {
        printf( "The seed code file open fail\n");
        return -1;
    }
    while (getline(open_file, seed_code_str)) {
        split(seed_code_vec, seed_code_str, is_any_of("\t"), token_compress_on);
        seed_code_dict[seed_code_vec[0]] = seed_code_vec[1];
        seed_code_vec.clear();
    }
    open_file.close();
    return 0;
}

void LexicalAnalyzer::output_seed_code() {
    map<string, string>::iterator iter;
    for (iter = seed_code_dict.begin(); iter != seed_code_dict.end(); iter++) {
        printf("%s\t%s\n", iter->first.c_str(), iter->second.c_str());
    }
}

LexicalAnalyzer::~LexicalAnalyzer() {

}
