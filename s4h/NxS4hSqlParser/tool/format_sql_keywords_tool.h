//
// Created by jeff on 2019/12/6.
//

#ifndef S4H_TEST_FORMAT_SQL_KEYWORDS_TOOL_H
#define S4H_TEST_FORMAT_SQL_KEYWORDS_TOOL_H

#include "file_opr_tool.h"

void format_sql_keywords(const std::string & fpath, std::string & out) {
    std::string sin = read_from_file( fpath);
    if (sin.empty()) return;

    std::set<std::string> sets;
    unsigned int pos = 0;
    while(sin[pos] != '\0') {

        std::string stemp;
        while(sin[pos] > 64 && sin[pos]  < 90 || sin[pos] == '_') {
            stemp+=sin[pos];

            pos++;
        }
        if (!stemp.empty()) {
            std::string sss = "FUNC(";
            sss += stemp;
            sss +=", \"";
            sss +=stemp;
            sss += "\")\n";
            sets.insert(stemp);
        }
        pos++;
    }

    for(auto ss:sets) {
       // out += ss;
        printf("FUNC(%s, \"%s\" )\n", ss.c_str(), ss.c_str());
    }

}







#endif //S4H_TEST_FORMAT_SQL_KEYWORDS_TOOL_H
