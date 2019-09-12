#include "interface.h"
#include "CCLoginHelper.h"
#include "CCPolicyHelper.h"
#include "config.h"


bool collect_policys(std::vector<IPolicy *>& rvec_policy) {
    //login to web console, get session cooke.
    //e.g: JSESSIONID=74E928001F7804C90609B8B995C354E3; Path=/console; Secure; HttpOnly

	std::string str_ccservice = (*g_pconfig)[CFG_POLICY_CCS];
	std::string str_port = (*g_pconfig)[CFG_POLICY_PORT];
	std::string str_user_name = (*g_pconfig)[CFG_POLICY_UN];
	std::string str_pwd = (*g_pconfig)[CFG_POLICY_PWD];
	std::string str_policy_tag = (*g_pconfig)[CFG_POLICY_TAG];

//     std::string str_ccservice = "https://cc86-console-01.qapf1.qalab01.nextlabs.com";
//     std::string str_port = "443";
//     std::string str_user_name = "administrator";
//     std::string str_pwd = "123blue!";
//     std::string str_policy_tag = "hana_poc";

    std::string str_session_cookie = CCLoginHelper::Login(str_ccservice, str_port, str_user_name, str_pwd);
	if (str_session_cookie.empty()) {
		return false;
	}
	std::list<std::string> lst_policy;
	if (!CCPolicyHelper::SyncPolicy(str_ccservice, str_port, str_session_cookie, str_policy_tag, lst_policy)) {
		return false;
	}
        

    for (auto it : lst_policy) {
        std::stringstream ss(it);
        printf("POLICY:\n%s\n", it.c_str());
        IPolicy *ppolicy = make_policy(&ss);
        if (ppolicy != nullptr)
			rvec_policy.push_back(ppolicy);
    }
    return rvec_policy.size() > 0;
}