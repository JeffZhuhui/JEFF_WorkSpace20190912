

#include "interface.h"
#include "UserAttr.h"
#include "tool/tool.h"
#include "third_party/nanodbc.h"
#include <algorithm>
#include "config.h"


CUserAttr::CUserAttr() {

}


CUserAttr::~CUserAttr() {

}

void CUserAttr::AddValue(const String& str_col, int type, const String& str_value)
{
	SColData data(type, str_value);
	_map_user_data.insert(make_pair(str_col, data));
}

void CUserAttr::AddValue(const String& str_col, const SColData& data)
{
	_map_user_data.insert(make_pair(str_col, data));
}

bool CUserAttr::Parse(void *data_source /* from nanodbc */)
{
	nanodbc::result* pdata = (nanodbc::result*)data_source;

	short columns = pdata->columns();
	nanodbc::string const null_value = NANODBC_TEXT("");

	if (columns < 2) return false;

// 	std::vector<string> vecCol;
// 	for (short col = 0; col < columns; ++col) {
// 		nanodbc::string colname = pData->column_name(col);
// 		std::string sName;
// 		ToUTF8(colname, sName);
// 		vecCol.push_back(sName);
// 	}

	for (short col = 0; col < columns; ++col) {

		int type = pdata->column_datatype(col);

		nanodbc::string value = pdata->get< nanodbc::string>(col, null_value);
		std::string utf8_value;
		CommonFun::ToUTF8(value, utf8_value);
		nanodbc::string colname = pdata->column_name(col);
		std::string name;
		CommonFun::ToUTF8(colname, name);

		if (name.compare((*g_pconfig)[CFG_USER_FIELD]) == 0) {
			SetName(utf8_value);
		}
		
		ColData data(type, utf8_value, pdata->is_null(col));
		AddValue(name, data);
		
	}
}

bool CUserAttr::IsValidAt(const std::string& column_name) const {
	std::string temp = column_name;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

	return _map_user_data.find(temp) != _map_user_data.end();
}

int CUserAttr::TypeAt(const std::string& column_name) const
{
	std::string temp = column_name;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

	ColDataMapIter it = _map_user_data.find(temp);
	if (it == _map_user_data.end())
	{
		return -341592;
	}
	return (it->second)._type;
}

bool CUserAttr::IsNullAt(const std::string &column_name) const {
	std::string temp = column_name;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

	ColDataMapIter it = _map_user_data.find(temp);
	if (it == _map_user_data.end())
	{
		return true;
	}
	return (it->second)._is_null;
}

std::string CUserAttr::ValueAt(const std::string &column_name) const {
	std::string temp = column_name;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

	ColDataMapIter it = _map_user_data.find(temp);
	if (it == _map_user_data.end())
	{
		return "";
	}
	return (it->second)._data;
}

IUser *make_users(void *data_source) {
	
	CUserAttr *pUser = new CUserAttr;
	pUser->Parse(data_source);

	return pUser;
}
