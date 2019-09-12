#include "Policy.h"
#include "log.h"
#ifdef _WIN64
#ifdef _DEBUG
#pragma comment(lib,"lib\\json_vc71_libmtd.lib")
#else //
#pragma comment(lib,"lib\\json_vc71_libmt.lib")
#endif
#else
#ifdef _DEBUG
#pragma comment(lib,"lib\\x86\\json_vc71_libmtd.lib")
#else //
#pragma comment(lib,"lib\\x86\\json_vc71_libmt.lib")
#endif
#endif
#include "json/json.h"

#ifdef _WIN32
#include <windows.h>
#endif

#include <algorithm>
#include <sql.h>
#ifndef SQL_TINYINT
#define SQL_TINYINT -6
#endif // !SQL_TINYINT
#ifndef SQL_BIGINT
#define SQL_BIGINT -5
#endif // !SQL_BIGINT

//for IsMatched();
bool number_compare(const Condition & cond, const std::string & val_user);
bool verify_user_attribute(const IUser *puser, const Condition & cond);
bool verify_view_attribute(const std::string & str_schema, const std::string & str_viewid, const std::string & str_viewname, const IViewMetaData *pview);
//for ConstructCondition()
bool is_end(const std::string& s, int index) { return s.length() <= index; }
std::string construct_condition_from_components(const OpComp& opcomp, const IUser *puser, const IViewMetaData *pview);
std::string construct_condition_from_conditions(const Component& comp, const IUser *puser, const IViewMetaData *pview);
std::string construct_condition(const Condition &cond, const std::string & str_value, const IViewMetaData *pview);
bool translation_attribute_value(const std::string &s, std::string& rref);
bool translation_attribute_value(const std::string &s, std::string& rref, const IUser *puser);

CPolicy::CPolicy()
{
}


CPolicy::~CPolicy()
{
}

bool CPolicy::Parse(std::stringstream *pdata_source /* json format */)
{
	std::string str_policy = pdata_source->str();
	Json::Reader read;
	Json::Value root;
	if (read.parse(str_policy, root)) {
		_id = root["id"].asString();  // 
		_full_name = root["fullname"].asString();
		_effect_type = root["effectType"].asString();
		Json::Value subject_components = root["subjectComponents"];
		int subject_size = subject_components.size();
		for (int i = 0; i < subject_size; ++i) {
			Json::Value js_opcomp = subject_components[i];
			OpComp opcomp;
			std::string op = js_opcomp["operator"].asString();
			if (op.compare("IN") == 0) {
				opcomp._operator = OpComp::OP_IN;
			}
			else {
				opcomp._operator = OpComp::OP_NOT;
			}
			Json::Value js_components = js_opcomp["components"];
			int i_comp_size = js_components.size();
			for (int j = 0; j < i_comp_size; ++j) {

				Json::Value js_comp = js_components[j];
				Component comp;
				comp._id = js_comp["id"].asString();
				comp._name = js_comp["name"].asString();
				Json::Value js_conditons = js_comp["conditions"];
				int i_cond_size = js_conditons.size();
				for (int k = 0; k < i_cond_size; ++k) {
					Condition cond;
					Json::Value js_cond = js_conditons[k];
					cond._attribute = js_cond["attribute"].asString();
					cond._value = js_cond["value"].asString();
					std::string rhstype = js_cond["rhsType"].asString();
					if (rhstype.compare("CONSTANT") == 0) {
						cond._rhs_type = Condition::CONSTANT;
					}
					else if (rhstype.compare("SUBJECT") == 0) {
						cond._rhs_type = Condition::SUBJECT;
					}
					else {

					}

					std::string op_cond = js_cond["operator"].asString();
					if (op_cond.compare("=") == 0) {
						cond._operator = Condition::EQ;
					}
					else if (op_cond.compare("!=") == 0) {
						cond._operator = Condition::NEQ;
					}
					else if (op_cond.compare(">") == 0) {
						cond._operator = Condition::GT;
					}
					else if (op_cond.compare(">=") == 0) {
						cond._operator = Condition::GTE;
					}
					else if (op_cond.compare("<") == 0) {
						cond._operator = Condition::LT;
					}
					else if (op_cond.compare("<=") == 0) {
						cond._operator = Condition::LTE;
					}
					else {
						/*assert */
					}
					comp._conditions.push_back(cond);
				}
				opcomp._components.push_back(comp);
			}
			_subs.push_back(opcomp);

		}

		Json::Value resource_omponents = root["fromResourceComponents"];
		int res_size = resource_omponents.size();
		for (int i = 0; i < res_size; ++i) {
			Json::Value js_opcomp = resource_omponents[i];
			OpComp oprcomp;
			std::string op = js_opcomp["operator"].asString();
			if (op.compare("IN") == 0) {
				oprcomp._operator = OpComp::OP_IN;
			}
			else {
				oprcomp._operator = OpComp::OP_NOT;
			}

			Json::Value js_components = js_opcomp["components"];
			int comp_size = js_components.size();
			for (int j = 0; j < comp_size; ++j) {

				Json::Value js_comp = js_components[j];
				Component comp;
				comp._id = js_comp["id"].asString();
				comp._name = js_comp["name"].asString();
				Json::Value js_conditons = js_comp["conditions"];
				int cond_size = js_conditons.size();
				for (int k = 0; k < cond_size; ++k) {
					Condition cond;
					Json::Value js_cond = js_conditons[k];
					std::string attr = js_cond["attribute"].asString();

					if (attr.compare("schema") == 0) {
						_str_schema = js_cond["value"].asString();
					}
					else if (attr.compare("table") == 0) {
						_str_viewname = js_cond["value"].asString();
					}
					else {
						cond._attribute = attr;
						cond._value = js_cond["value"].asString();
						std::string rhstype = js_cond["rhsType"].asString();
						if (rhstype.compare("CONSTANT") == 0) {
							cond._rhs_type = Condition::CONSTANT;
						}
						else if (rhstype.compare("SUBJECT") == 0) {
							cond._rhs_type = Condition::SUBJECT;
						}
						else {

						}

						std::string op_cond = js_cond["operator"].asString();
						if (op_cond.compare("=") == 0) {
							cond._operator = Condition::EQ;
						}
						else if (op_cond.compare("!=") == 0) {
							cond._operator = Condition::NEQ;
						}
						else if (op_cond.compare(">") == 0) {
							cond._operator = Condition::GT;
						}
						else if (op_cond.compare(">=") == 0) {
							cond._operator = Condition::GTE;
						}
						else if (op_cond.compare("<") == 0) {
							cond._operator = Condition::LT;
						}
						else if (op_cond.compare("<=") == 0) {
							cond._operator = Condition::LTE;
						}
						else {
							/*assert */
						}
						comp._conditions.push_back(cond);
					}

				}
				oprcomp._components.push_back(comp);
			}
			_ress.push_back(oprcomp);
		}
	}
	if (!_str_schema.empty() && !_str_viewname.empty()) {
		_str_viewid = "\"" + _str_schema + "\".\"" + _str_viewname + "\"";
	}
	return true;
}
	


std::string CPolicy::GetViewId() const
{
	return _str_viewid;
}

std::string CPolicy::GetSchemaName() const
{
	return _str_schema;
}

std::string CPolicy::GetViewName() const
{
	return _str_viewname;
}

bool number_compare(const Condition & cond, const std::string & val_user) {
	bool ret = false;

	double d_left = atof(cond._value.c_str());
	double d_right = atof(val_user.c_str());
	switch (cond._operator)	{
		case Condition::EQ: {
			double d = d_left - d_right;
			if (d > -0.00001 && d < 0.00001) ret = true;

		} break;
		case Condition::NEQ: {
			double d = d_left - d_right;
			if (d <= -0.00001 || d >= 0.00001) ret = true;

		} break;
		case Condition::GT: { // >
			ret = d_left > d_right;
		} break;
		case Condition::GTE: { // >=
			ret = d_left >= d_right;
		} break;
		case Condition::LT: { // < 
			ret = d_left < d_right;
		} break;
		case Condition::LTE: { // <=
			ret = d_left <= d_right;
		} break;
	
	}
	return ret;
}


bool verify_user_attribute(const IUser *puser, const Condition & cond) {
	if (!puser->IsValidAt(cond._attribute)) {
		//Log::WriteLog()
		//std::cout << "user attribute:" << cond._attribute << " is invalid " << std::end_left;
		return false;
	}
		
	switch (puser->TypeAt(cond._attribute)) {
		case SQL_BIGINT: /* FALL THROUGH */
		case SQL_INTEGER:  /* FALL THROUGH */
		case SQL_SMALLINT:  /* FALL THROUGH */
		case SQL_TINYINT:  /* FALL THROUGH */
		case SQL_NUMERIC:  /* FALL THROUGH */
		case SQL_DECIMAL:  /* FALL THROUGH */
		case SQL_FLOAT:  /* FALL THROUGH */
		case SQL_REAL:  /* FALL THROUGH */
		case SQL_DOUBLE:{
			return number_compare(cond, puser->ValueAt(cond._attribute));
		
		} break;
	
		default: {
			if (cond._operator == Condition::EQ) {
				return cond._value.compare(puser->ValueAt(cond._attribute)) == 0;
			}		
			else if (cond._operator == Condition::NEQ) {
				return cond._value.compare(puser->ValueAt(cond._attribute)) != 0;
			}
			

		} break;
	
	}
	return false;
}

bool verify_view_attribute(const std::string &str_schema, const std::string &str_viewid, const std::string &str_viewname, const IViewMetaData *pview) {
	//schema
	if (str_schema.compare(pview->GetSchemaName()) != 0) return false;
	//viewid
	if (str_viewid.compare(pview->GetViewId()) != 0) return false;
	//viewname
	if (str_viewname.compare(pview->GetViewName()) != 0) return false;

	return true;
}

bool CPolicy::IsMatched(const IUser *puser, const IViewMetaData *pview) const
{
	//_subs
	bool ret = true;
	int sub_size = _subs.size();
	for (int i = 0 ; i < sub_size;++i){
		bool b_component = false;
		int iComSize = _subs[i]._components.size();
		for (int j = 0; j < iComSize; ++j){
			bool b_condition = true;
			Component com = _subs[i]._components[j];
			int cond_size = com._conditions.size();
			for (int k = 0 ; k < cond_size; ++k) {
				if ( !verify_user_attribute(puser, com._conditions[k]) ) {
					b_condition = false;
					break;
				}
			}
			if (b_condition == true)	{
				b_component = true;
				break;
			}
		}

		if (OpComp::OP_IN == _subs[i]._operator ) {
			if (b_component == false) {
				ret = false;
				break;
			}
		}
		else {
			if (b_component == true)	{
				ret = false;
				break;
			}
		}
	}
	if (ret == false) {
		return false;
	}
	//_ress
	return verify_view_attribute(_str_schema, _str_viewid, _str_viewname, pview);
}

std::string CPolicy::ConstructCondition(const IUser *puser, const IViewMetaData *pview) const
{
	int res_size = _ress.size();
	std::string str_condition;
	for (int i = 0 ; i < res_size; ++i)	{
		OpComp op = _ress[i];

		std::string str_sub = construct_condition_from_components(op, puser, pview);

		if (!str_sub.empty()) {
			if (!str_condition.empty())	{
				str_condition += " AND ";
			}
			if (res_size > 1) {
				str_condition += "(" + str_sub + ")";
			}
			else {
				str_condition += str_sub;
			}
		}
	}
	return str_condition;
}

std::string construct_condition_from_components(const OpComp& op, const IUser *puser, const IViewMetaData *pview)  {
	std::string str_con;
	int size = op._components.size();
	for (int i = 0; i < size; i++)	{
		Component comp = op._components[i];
		std::string str_conditions = construct_condition_from_conditions(comp, puser, pview);

		if (!str_conditions.empty())	{
			//the relationship between Comp is "OR"
			if (!str_con.empty()) {
				str_con += " OR ";
			}
			str_con += " " + str_conditions + " ";
		}
	}
	return str_con;
}

std::string construct_condition_from_conditions(const Component& comp, const IUser *puser, const IViewMetaData *pview) {
	std::string str_con;
	int size = comp._conditions.size();

	for (int i = 0 ; i < size; ++i) {
		Condition cond = comp._conditions[i];

		const std::string str_value = cond._value;
		std::string str_name = cond._attribute;

		if (!pview->IsValidAt(str_name))	{
			std::cout << "exist invalid field: " << str_name << std::endl;
			continue;
		}
		std::string str_value_new = str_value;

		if (!translation_attribute_value(str_value, str_value_new, puser)) {
			std::cout << "user attribute(" << str_name << ") format is illegal."<< std::endl;
			
			continue;
		}
		if (str_value_new.empty()) {
			std::cout << "user attribute(" << str_name << ") value is empty." << std::endl;
			continue;
		}

		std::string str_condition = construct_condition(cond, str_value_new, pview);

		if (!str_condition.empty()) {

			if (!str_con.empty()) {
				str_con += " AND ";
			}
			str_con += "(" + str_condition + ")";
		}
	}
	return str_con;
}

std::string construct_condition(const Condition& cond,const std::string & str_value, const IViewMetaData *pview) {
	std::string str_full_attr = cond._attribute;// = pview->GetViewName();
	//strFullAttr += "." + cond._attribute;
	std::string str_con;
	std::string sc = "";
	std::string str_temp = str_value;

	switch (pview->TypeAt(cond._attribute)) {
		case SQL_BIGINT:  /* FULL THROUGH */
		case SQL_INTEGER: /* FULL THROUGH */
		case SQL_SMALLINT: /* FULL THROUGH */
		case SQL_TINYINT: /* FULL THROUGH */
		case SQL_NUMERIC: /* FULL THROUGH */
		case SQL_DECIMAL: /* FULL THROUGH */
		case SQL_FLOAT: /* FULL THROUGH */
		case SQL_REAL: /* FULL THROUGH */
		case SQL_DOUBLE: 
			break;
		default: {
			str_temp = "'" + str_value + "'";
		}break;
	}
	std::string str_op;
	switch (cond._operator)	{
		case Condition::EQ: {
			str_op = "=";
		} break;
		case Condition::NEQ: {
			str_op = "<>";
		} break;
		case Condition::GT: {
			str_op = ">";
		} break;
		case Condition::GTE: {
			str_op = ">=";
		} break;
		case Condition::LT: {
			str_op = "<";
		} break;
		case Condition::LTE: {
			str_op = "<=";

		} break;

		default:
			break;
	}
	str_con = str_full_attr + str_op + str_temp;

	return str_con;
}

bool translation_attribute_value(const std::string &s, std::string& rref, const IUser *puser) {
	if (s.empty()) {  
		rref = s;
		return true;
	}

	if (s[0] != '$')
		return translation_attribute_value(s, rref);
	int i = 1;
	if (!(i < s.length() && s[i] == '{'))
		return false;

	++i;
	int start = i;
	while (i < s.length() && s[i] != '.')
		++i;
	if (!(i < s.length() && s[i] == '.'))
		return false;
	std::string user = s.substr(start, i - start);
	if (user != "user")
		return false;
	++i;
	start = i;
	i = s.length() - 1;
	if (s[i] != '}')
		return false;
	std::string attr = s.substr(start, i - start);
	
	std::string str_ret = puser->ValueAt(attr);
	rref = str_ret;

	translation_attribute_value(str_ret, rref);

	return true;
}
bool translation_attribute_value(const std::string &s, std::string& rref) {
	int i = 0;
	std::stringstream b;
	bool flag = false;
	int sLen = s.length();
	while (!is_end(s, i)) {
		if (s[i] == '\'') {
			/* code */
			b << s[i];
			b << s[i];
		}
		else {
			b << s[i];
		}
		i++;
	}
	rref = b.str();
	return true;
}

IPolicy *make_policy(std::stringstream *pdata_source) {
	CPolicy* ppolicy = new CPolicy();
	ppolicy->Parse(pdata_source);
	return ppolicy;
}