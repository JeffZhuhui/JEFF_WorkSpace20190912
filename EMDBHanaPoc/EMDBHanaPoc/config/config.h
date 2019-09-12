#ifndef CONFIG_H_2019_01_31
#define CONFIG_H_2019_01_31
#include <stdio.h>
#include <string>
#include <map>

typedef std::map<std::string,std::string> ConfigMap;



#define CFG_USER_TABLE "USER.table" 
#define CFG_USER_FIELD "USER.user_field" 
#define CFG_USER_CONNECT "USER.connect"
#define CFG_VIEW_CONNECT "VIEW.connect"
#define CFG_POLICY_CCS "POLICY.ccservice" 
#define CFG_POLICY_PORT "POLICY.port"
#define CFG_POLICY_UN "POLICY.user_name"
#define CFG_POLICY_PWD "POLICY.pwd"
#define CFG_POLICY_TAG "POLICY.policy_tag"

#define CFG_CONDITION_TABLE "CONDITION.table"
#define CFG_CONDITION_CONNECT "CONDITION.connect"

class CConfig
{
    public:
    CConfig();
    CConfig(const CConfig&){};    

    public:
    bool ReadConfig(const char *pconfig_path);
    void PrintConfigData();
    const std::string& operator[](const char *pkey);
    private:
    std::map<std::string, ConfigMap>  _map_configs;
    std::string _str_empty_value;
};

extern CConfig* g_pconfig;




#endif 