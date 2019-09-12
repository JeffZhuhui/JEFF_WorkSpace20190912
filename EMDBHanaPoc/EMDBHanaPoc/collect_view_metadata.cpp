#include "interface.h"
#include "tool.h"
#include "nanodbc.h"
#include <map>
#include "config.h"

//"Driver=SAP HANA ODBC DRIVER;SERVERNODE = 10.23.60.152:39015;Uid=SYSTEM;PWD=123Blue!"


bool fetch_meta_data(IViewMetaData *pview) 
{
    try {
        nanodbc::connection cnn(NANODBC_TEXT((*g_pconfig)[CFG_VIEW_CONNECT]));
        nanodbc::statement stmt(cnn);
        nanodbc::string sql = NANODBC_TEXT("SELECT * FROM ");
        nanodbc::string cvt;
        CommonFun::FromUTF8(pview->GetViewId(), cvt);
        sql += cvt;
        sql += NANODBC_TEXT(" WHERE 1=0");
        nanodbc::prepare(stmt, sql);
        nanodbc::result results = nanodbc::execute(stmt);
		pview->Parse(&results);
    }
    catch (nanodbc::database_error const& e) {
        /* todo log */
        return false;
    }
    return true;
}


bool collect_view_metadata(const std::vector<IPolicy *>& policys, std::vector<IViewMetaData *>& rvec_viewdata)
{
	if (policys.size() <= 0) {
		return false;
	}  
    std::map<std::string, IViewMetaData*> view_ids;
    for (auto it : policys) {
        if (view_ids.find(it->GetViewId()) == view_ids.end()) {
            IViewMetaData *pview = make_view_metadata(it->GetViewId());
            if (pview != nullptr && fetch_meta_data(pview)) {
				rvec_viewdata.push_back(pview);
                view_ids.insert(std::make_pair(it->GetViewId(), pview));
            }
            else {
                assert(false);
                /* todo */
            }
        }
    }
    return rvec_viewdata.size() > 0;
}