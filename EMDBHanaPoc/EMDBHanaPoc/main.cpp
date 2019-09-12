#include <iostream>
#include "interface.h"
#include "config.h"

#include <map>

#ifdef WIN32
#include "windows.h"
#endif


bool init_config() {
	char cfiles[256] = { 0 };
#ifdef WIN32
	::GetModuleFileNameA(NULL, (CHAR*)cfiles, 256);
#else
	int rslt = readlink("/proc/self/exe", cfiles, 256);
	if (rslt < 0 || (rslt >= 256)) {
		return false;
	}
#endif
	std::string str_path(cfiles);
	int find = str_path.rfind("\\");

	int len = str_path.length();
	std::string str_config = str_path.substr(0, find + 1);
	str_config += "config.ini";

	if (NULL == g_pconfig) {
		g_pconfig = new CConfig();
		g_pconfig->ReadConfig(str_config.c_str());
	}
	return true;
}

int main() {

	init_config();

	printf("command: R/r is refresh.\n");
	printf("command: Q/q is quit.\n");
	char c = 0;
	while (1)
	{
		if (c != '\n')
		{
			printf("please input(r/q) command>\n");
		}
		c = getchar();

		if (c == 'Q' || c== 'q') {
			break;
		}
		else if (c == 'R' || c == 'r') {
			std::vector<IPolicy*> vec_policys;
			collect_policys(vec_policys);
			std::vector<IViewMetaData*> views_metadata;
			collect_view_metadata(vec_policys, views_metadata);
			std::vector<IUser*> users;
			collect_users(users);

			std::vector<IFilter*> vec_tbl;
			for (auto user : users) {
				for (auto view : views_metadata) {
					std::vector<IPolicy*> ps;
					for (auto policy : vec_policys) {
						if (policy->IsMatched(user, view)) {
							ps.push_back(policy);
						}
					}
					vec_tbl.push_back(make_filter(user, view, ps));
				}
			}

			update_table(vec_tbl);

			for (auto puser : users) {
				delete puser;
			}
			for (auto pview : views_metadata) {
				delete pview;
			}
			for (auto ppolicy : vec_policys) {
				delete ppolicy;
			}
			for (auto pfilter : vec_tbl) {
				delete pfilter;
			}
		} else {

		}


		
	}



    return 0;
}