#include "ViewMetaData.h"
#include "nanodbc.h"
#include "tool.h"
#include <algorithm>

CViewMetaData::CViewMetaData() {

}


CViewMetaData::~CViewMetaData() {

}

bool CViewMetaData::Parse(void *data_source /* from nanodbc */) {
	nanodbc::result *pdata = (nanodbc::result*)data_source;

	short columns = pdata->columns();

	for (short col = 0; col < columns; ++col) {

		int type = pdata->column_datatype(col);

		nanodbc::string colname = pdata->column_name(col);
		std::string sname;
		CommonFun::ToUTF8(colname, sname);

		_map_metadata.insert(make_pair(sname, type));
	}

	return true;
}

std::string CViewMetaData::GetViewId() const {
	return _view_id;
}

std::string CViewMetaData::GetSchemaName() const {
	return _schema;
}

std::string CViewMetaData::GetViewName() const {
	return _view_name;
}

bool CViewMetaData::IsValidAt(const std::string &column_name) const {
	std::string temp = column_name;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

	return _map_metadata.find(temp) != _map_metadata.end();
}

int CViewMetaData::TypeAt(const std::string &column_name) const {
	std::string temp = column_name;
	std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);

	Col2TypeMapCIter it = _map_metadata.find(temp);
	if (it == _map_metadata.end()) {
		return -3121592;
	}
	return it->second;
}

IViewMetaData *make_view_metadata(const std::string & str_view_id) {
	int iFind = str_view_id.find(".");//todo Ignore the name include char'.'
	std::string str_schema = str_view_id.substr(1, iFind-2 );
	std::string str_view_name = str_view_id.substr(iFind+2, str_view_id.length()-iFind-3);
	CViewMetaData * pview_metadata = new CViewMetaData(str_view_id, str_schema, str_view_name);

	return pview_metadata;
}