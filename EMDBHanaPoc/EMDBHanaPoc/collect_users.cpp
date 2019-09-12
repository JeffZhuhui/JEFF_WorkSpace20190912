#include "interface.h"
#include "nanodbc.h"
#include "tool.h"
#include "config.h"

bool collect_users(std::vector<IUser *>& rvec_user) {
	rvec_user.clear();
    try {
        nanodbc::connection cnn(NANODBC_TEXT((*g_pconfig)[CFG_USER_CONNECT]));
        nanodbc::statement stmt(cnn);
        nanodbc::string sql = NANODBC_TEXT("SELECT * FROM ");
		sql += NANODBC_TEXT((*g_pconfig)[CFG_USER_TABLE]);
        nanodbc::prepare(stmt, sql);
        nanodbc::result results = nanodbc::execute(stmt);
        while (results.next()) {
            auto u = make_users(&results);
            if (u != nullptr)
				rvec_user.push_back(u);
        }
        return rvec_user.size() > 0;
    }
    catch (nanodbc::database_error const& e) {
        /* todo log */
        return false;
    }
}


