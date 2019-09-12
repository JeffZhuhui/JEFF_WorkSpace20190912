
#include "config.h"
#ifdef WIN32
#include <windows.h>
#endif 
#include <iostream> 
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

 CConfig* g_pconfig = NULL;

 CConfig::CConfig()
 {

 }

 bool CConfig::ReadConfig(const char* pconfig_path)
 { 
    try {
       using namespace boost::property_tree;
	   ptree lvpt_properties;
	   ini_parser::read_ini(pconfig_path, lvpt_properties);

       //walk through the config file
       ptree::iterator it_section = lvpt_properties.begin();
       while(it_section != lvpt_properties.end() ){
            std::string str_section = it_section->first;
            //read values from section
            ConfigMap cfg_values;   
            basic_ptree<std::string, std::string> lvbtItems = lvpt_properties.get_child(str_section);
            for (basic_ptree<std::string, std::string>::iterator lvitem=lvbtItems.begin();lvitem!=lvbtItems.end();lvitem++) {	
                std::string str_key = (*lvitem).first.data();
                std::string strValue = (*lvitem).second.data();

                cfg_values[str_key] = strValue;
            }
            _map_configs[str_section] = cfg_values;
            //next session
            it_section++;
       }
    }
    catch(...) {
        return false;
    }
    return true;
 }

 const std::string& CConfig::operator[](const char* pkey)
 {
     std::string str_cfg_path = pkey;
     size_t nPos = str_cfg_path.find_first_of('.');
     if(nPos==std::string::npos){
         return _str_empty_value;
     }

     std::string str_section = str_cfg_path.substr(0, nPos);
     std::string str_key = str_cfg_path.substr(nPos+1);

     //find section
     std::map<std::string,ConfigMap>::iterator it_section = _map_configs.find(str_section);
     if(it_section!=_map_configs.end()) {
         const ConfigMap& cfg_values = it_section->second;
         ConfigMap::const_iterator it_value = cfg_values.find(str_key);
         if(it_value !=cfg_values.end()) {
             return it_value->second;
         }
     }

     return _str_empty_value;
 }

void CConfig::PrintConfigData()
{
    std::map<std::string,ConfigMap>::iterator it_section = _map_configs.begin();
    while(it_section!=_map_configs.end()){
        printf("[%s]\n", it_section->first.c_str());
        ConfigMap::iterator it_cfg_value = it_section->second.begin();
        while(it_cfg_value!=it_section->second.end()){
            printf("%s=%s\n", it_cfg_value->first.c_str(), it_cfg_value->second.c_str() );
            it_cfg_value++;   
        }   
        it_section++;
    }
}
