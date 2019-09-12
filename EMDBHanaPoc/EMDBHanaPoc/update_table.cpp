#include "interface.h"
#include "nanodbc.h"
#include "tool.h"
#include <set>
#include "config.h"

bool update(const nanodbc::string& sql);
bool is_end(const std::string& s, unsigned int iIndex) { return s.length() <= iIndex; }
bool translation_attribute_values(const std::string &s, std::string& ref) {
    int i = 0;
    std::stringstream b;
    while (!is_end(s, i)){
        if (s[i] == '\'')
        {
            /* code */
            b << s[i];
            b << s[i];
        }else{
            b << s[i];
        }
        i++;
    }
    ref = b.str();
    return true;
}

bool update_table(const std::vector<IFilter*>& filters) {
	std::string str_condition_tb = (*g_pconfig)[CFG_CONDITION_TABLE];

    std::set<std::string> t;
    for (auto it : filters) {
        t.insert(it->GetName() + it->GetViewId());
    }
    if (t.size() != filters.size())
        return false;

    nanodbc::string del = NANODBC_TEXT("DELETE FROM ");
    del += NANODBC_TEXT(str_condition_tb);
    del += NANODBC_TEXT(";");

    if (filters.size() > 0) {
        int i = 0;
        nanodbc::string insert = NANODBC_TEXT("INSERT INTO ");
        insert += NANODBC_TEXT(str_condition_tb);
        insert += NANODBC_TEXT(" VALUES ");
        for (auto it : filters) {
            if (i > 0) {
                insert += ", ";
            }
            insert += NANODBC_TEXT("(");
            nanodbc::string tmp;
            std::string cvt;
			translation_attribute_values(it->GetName(), cvt);
            CommonFun::FromUTF8("'"+cvt+"'", tmp);
            insert += tmp; insert += NANODBC_TEXT(", ");
			translation_attribute_values(it->GetViewId(), cvt);
            CommonFun::FromUTF8("'"+cvt+"'", tmp);
            insert += tmp; insert += NANODBC_TEXT(", ");
			translation_attribute_values(it->GetFilterCondition(), cvt);
            CommonFun::FromUTF8("'"+cvt+"'", tmp);
            insert += tmp;
            insert += NANODBC_TEXT(")");
            ++i;
        }
        del += insert;
    }

    return update(del);
}

bool update(const nanodbc::string& sql) {
    printf("update filter condition SQL :\n%s\n", sql.c_str());
    try {
        nanodbc::connection cnn( NANODBC_TEXT((*g_pconfig)[CFG_CONDITION_CONNECT]) );
        nanodbc::statement stmt(cnn);
        nanodbc::prepare(stmt, sql);
        nanodbc::result result = nanodbc::execute(stmt);
    }
    catch (nanodbc::database_error const& e) {
        /* todo log */
        return false;
    }
    return true;
}