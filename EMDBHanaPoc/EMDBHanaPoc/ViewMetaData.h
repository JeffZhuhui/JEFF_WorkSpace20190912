#pragma once
#include "interface.h"
#include <map>

typedef std::map<std::string, int> Col2TypeMap;
typedef Col2TypeMap::const_iterator Col2TypeMapCIter;

class CViewMetaData :
	public IViewMetaData
{
public:
	CViewMetaData();
	CViewMetaData(const std::string& str_view_id, const std::string& str_schema, const std::string& str_view_name)
		:_view_id(str_view_id), _schema(str_schema), _view_name(str_view_name) {}
	~CViewMetaData();

	virtual bool Parse(void *data_source /* from nanodbc */) override;
	virtual std::string GetViewId() const override;
	virtual std::string GetSchemaName() const override;
	virtual std::string GetViewName() const override;
	virtual bool IsValidAt(const std::string& column_name) const override;
	virtual int TypeAt(const std::string& column_name) const override;
private:
	std::string _view_id;
	std::string _view_name;
	std::string _schema;
	Col2TypeMap _map_metadata;

};

