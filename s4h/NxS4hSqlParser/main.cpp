#include <iostream>
#include "microtest.h"
#include "NXSFHLex.h"
#include "tool/format_sql_keywords_tool.h"
#include "tool/parse_black_list_tool.h"
#include "NXSFHAst.h"


#define FOLDER_WHITE_LOG "/home/jeff/CLionProjects/NxS4hSqlParser/resourece/log_white/"
#define FOLDER_BLACK_LOG "/home/jeff/CLionProjects/NxS4hSqlParser/resourece/log_black/"
#define FOLDER_TABLE_OUT "/home/jeff/CLionProjects/NxS4hSqlParser/resourece/s4h_tables/"
std::set<std::string>  set_white;
std::set<std::string>  set_black;
/*
TEST(GET_SQL_ST_white) { //get all sql statement write to file
   std::string  folder = FOLDER_WHITE_LOG;
   std::map<std::string , std::string> mapfile;
   get_file_paths_v2(folder, mapfile);
   for (auto it: mapfile) {
       std::string ss =  read_from_file(it.second);

       std::set<std::string> sqls;
       parse_statement_from_log(ss,sqls );

       std::string sfile;
       sfile = folder + "select_sql/" + it.first;
       output_file(sqls, sfile);
   }
}

TEST(GET_FROM_TB_white){ //get all sql table(from "tbname") write to file

   std::string  folder = FOLDER_WHITE_LOG;
   folder += "select_sql/";
   std::map<std::string , std::string> mapfile;
   get_file_paths_v2(folder, mapfile);
   //std::set<std::string> blacklist;
   for (auto it: mapfile) {
       std::string ss =  read_from_file(it.second);
       // printf("path : %s-----\n", path.c_str());
       parse_string2blacklist_v2(ss, set_white);
   }
   printf("whitelist size : %ld-----\n", set_white.size());
}

TEST(GET_SQL_ST) { //get all sql statement write to file
   std::string  folder = FOLDER_BLACK_LOG;
   std::map<std::string , std::string> mapfile;
   get_file_paths_v2(folder, mapfile);
   for (auto it: mapfile) {
       std::string ss =  read_from_file(it.second);

       std::set<std::string> sqls;
       parse_statement_from_log(ss,sqls );

       std::string sfile;
       sfile = folder + "select_sql/" + it.first;
       output_file(sqls, sfile);
   }
}

TEST(GET_FROM_TB){//get all sql table(from "tbname") write to file

   std::string  folder = FOLDER_BLACK_LOG ;
   folder += "select_sql/";
   std::map<std::string , std::string> mapfile;
   get_file_paths_v2(folder, mapfile);
   std::set<std::string> blacklist;
   for (auto it: mapfile) {
       std::string ss =  read_from_file(it.second);
       // printf("path : %s-----\n", path.c_str());
       parse_string2blacklist_v2(ss, set_black);
   }
   printf("blacklist size : %ld-----\n", set_black.size());
}

TEST(BLACK_WHITE) {
   std::set<std::string> setall;
   setall=set_black;
   for(auto tb: set_white) {
       setall.insert(tb);
   }
   printf("all_tb_list size : %ld-----\n", setall.size());

   std::set<std::string> setwhite;
   std::set<std::string> setblack;
   for (auto tb:set_white) {
       if(set_black.find(tb) == set_black.end()) {
           setwhite.insert(tb);
       }else {
           setblack.insert(tb);
       }
   }

   printf("white_tb_list size : %ld-----\n", setwhite.size());
   printf("black_tb_list size : %ld-----\n", setblack.size());

   {
       std::string sout = FOLDER_TABLE_OUT;
       output_tb2file(setblack, sout += "common_table");
   }
   {
       std::string sout = FOLDER_TABLE_OUT;
       output_tb2file(setwhite, sout += "white_special_table");
   }
   {
       std::string sout = FOLDER_TABLE_OUT;
       output_tb2file(setall, sout += "all_table");
   }
}
*/

/*
TEST(GET_SQL_KEYWORDS) {
    const std::string  fpath = "/home/jeff/CLionProjects/NxS4hSqlParser/resourece/s4h/HANA_SQL_KEYWORDS";
    std::string out;
    format_sql_keywords(fpath, out);
}
*/


/////parse old sql to new sql string
bool parse_sql(const std::string &in, std::string &out) {
    Lex lex(in);
    while (true) {
        lex.Next();
        const NxToken *tk = lex.GetCurrent();
        //ASSERT_TRUE(tk->GetType() != NxToken::TK_ERR);
        if (tk->GetType() == NxToken::TK_ERR) {
            //out("\n%s", tk->GetWord().c_str());
            out+="--generate error";
            return false;
        }
        if (tk->GetType() == NxToken::TK_END) {
            break;
        }
        std::string word;
        if(tk->GetType() == NxToken::D_LITERAL) {
            word+='\'';
            word+=tk->GetWord();
            word+='\'';
        } else if (tk->GetType() == NxToken::IDENTIFIER) {
            word+='\"';
            word+=tk->GetWord();
            word+='\"';
        } else {
            word = tk->GetWord();
        }
        out += word;
        if(tk->GetType() != NxToken::N_CHAR &&
           tk->GetType() != NxToken::COUNT&&
           tk->GetType() != NxToken::FUZZY&&
           tk->GetType() != NxToken::IN&&
           tk->GetType() != NxToken::CONTAINS&&
           tk->GetType() != NxToken::PARAMETERS
                ) {
            out+=" ";

        }

    }
    return true;
}

//lex
TEST(LEX_1) {
    std::string spath = FOLDER_WHITE_LOG;
    spath+= "HANADB1444_.log";
    std::string ss =  read_from_file(spath);

    std::set<std::string> sqls;
    parse_statement_from_log(ss,sqls );

    for (auto sql: sqls) {
        //std::string sql = "SELECT \"ID\" FROM \"UCONHTTPCUSTHEAD\" WHERE \"ID\" = ? AND \"MANDT\" = ? LIMIT 1";
        std::string out;
        ASSERT_TRUE(parse_sql(sql, out));
        printf("%s\n", out.c_str());
    }


}
TEST(LEX_2) {
    {
        std::string sql = "select * from 3abc where abc = ?";
        std::string out;
        ASSERT_FALSE(parse_sql(sql, out));
    }

    {
        std::string sql = "select \"sss as aaa from bbb where abc = ?";
        std::string out;
        ASSERT_FALSE(parse_sql(sql, out));
    }

    {
        std::string sql = "select | from 1abc where abc = ?";
        std::string out;
        ASSERT_FALSE(parse_sql(sql, out));
    }

    {
        std::string sql = "select * from 1abc where N 'xxx' = ?";
        std::string out;
        ASSERT_FALSE(parse_sql(sql, out));
    }

}


TEST_MAIN()