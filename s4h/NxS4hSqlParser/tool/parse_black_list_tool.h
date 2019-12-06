//
// Created by jeff on 2019/12/4.
//

#ifndef S4H_TEST_PARSE_BLACK_LIST_TOOL_H
#define S4H_TEST_PARSE_BLACK_LIST_TOOL_H

#include "file_opr_tool.h"
#include <iostream>
#include <stdio.h>

void parse_black_tb(const std::string & ss, unsigned int & pos, std::set<std::string> & blacklist) {
    while(ss[pos] == ' ') {
        pos++;
    }
    if (ss[pos] == '\"') {
        pos++;
        while(ss[pos] == ' ') {
            pos++;
        }
        std::string sb;
        while(ss[pos] != '\"' && ss[pos] != ' ') {
            sb+=ss[pos];
            pos++;
        }
        blacklist.insert(sb);
    } else if(ss[pos] == '/' && ss[pos+1] == '*') {
        while( ss[pos-1] != '*' && ss[pos] != '/') {
            pos++;
        }
        pos++;
        parse_black_tb(ss, pos, blacklist);
    } else if(ss[pos] == '(') {

    } else {
        std::string sb;
        while(ss[pos] != ' ') {
            sb+=ss[pos];
            pos++;
        }
        blacklist.insert(sb);
    }
}

void parse_string2blacklist(std::string & ss, std::set<std::string> & blacklist) {
    unsigned int pos = 0;

    while(ss[pos] != '\0') {
        switch (ss[pos]) {

            case 'I': {
                std::string stmp;
                if(ss[pos-1] != '='){
                    break;
                }
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                if (ss[pos] == ' ' &&
                    stmp.compare("INSERT") == 0)
                {
                    while(ss[pos-1] != '\n'){
                        pos++;
                    }
                }
            } break;
            case 'U': {
                std::string stmp;
                if(ss[pos-1] != '='){
                    break;
                }
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                if (ss[pos] == ' ' &&
                        stmp.compare("UPDATE") == 0)
                {
                    while(ss[pos-1] != '\n'){
                        pos++;
                    }
                }
            } break;
            case 'D': {//DELETE
                std::string stmp;
                if(ss[pos-1] != '='){
                    break;
                }
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                stmp += ss[pos++];
                if (ss[pos] == ' ' &&
                    stmp.compare("DELETE") == 0)
                {
                    while(ss[pos-1] != '\n'){
                        pos++;
                    }
                }
            }
            case 'F':{
                std::string sfrom;
                if(ss[pos-1] != ' '){
                    break;
                }

                sfrom += ss[pos++];
                sfrom += ss[pos++];
                sfrom += ss[pos++];
                sfrom += ss[pos++];
                if (ss[pos] == ' ' &&
                    sfrom.compare("FROM") == 0)
                {
                    pos++;
                    parse_black_tb(ss, pos, blacklist);
                }
            } break;

            default:
                break;
        }
        pos++;
    }

}




void parse_string2blacklist_v2(std::string & ss, std::set<std::string> & blacklist) {
    unsigned  int pos = 0;
    while(ss[pos] != '\0') {
        if(     pos > 4 &&
                ss[pos-4] == 'F' &&
                ss[pos-3] == 'R' &&
                ss[pos-2] == 'O' &&
                ss[pos-1] == 'M' &&
                ss[pos] == ' ' ) {
            parse_black_tb(ss, pos, blacklist);
            while(ss[pos] != '\n') pos++;
        }
        pos++;
    }
}


//get select sql statement
void collect_sql_statement(const std::string & ss,unsigned int & pos, std::set<std::string> & sqlset) {
    std::string ssin;
    while(true) {
        if (ss[pos] == ',' &&
            ss[pos+1] == ' ' &&
            ss[pos+2] == 'e' &&
            ss[pos+3] == 'n' &&
            ss[pos+4] == 'c' &&
            ss[pos+5] == 'o' &&
            ss[pos+6] == 'd'  ) {

            break;
        }
        if (pos >= ss.length()) {
            break;
        }
        ssin+= ss[pos];
        pos++;
    }
    sqlset.insert(ssin);
}

void parse_statement_from_log(const std::string & ss, std::set<std::string> & sqlset) {
    unsigned  int  pos = 0;
    unsigned  int  count = ss.length();
    while (pos < count-5) {
        pos++;
        if(ss[pos-1] == '=' &&
           ss[pos] == 'S' &&
           ss[pos+1] == 'E' &&
           ss[pos+2] =='L' &&
           ss[pos+3] =='E' &&
           ss[pos+4] =='C' &&
           ss[pos+5] =='T'){
            collect_sql_statement( ss,  pos, sqlset);
        }
    }
}










#endif //S4H_TEST_PARSE_BLACK_LIST_TOOL_H
