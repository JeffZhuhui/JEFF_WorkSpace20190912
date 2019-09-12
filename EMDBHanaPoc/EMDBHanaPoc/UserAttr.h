#pragma once

#include <map>

typedef std::string String;
typedef struct ColData
{
	ColData(int type, const std::string& data, bool is_null = false)
		:_type(type), _data(data),_is_null(is_null) {}
	int _type;
	std::string _data;
	bool _is_null;

} SColData;

typedef std::map<String, SColData> ColDataMap;
typedef ColDataMap::const_iterator ColDataMapIter;

class CUserAttr : public IUser
{
public:
	CUserAttr();
	virtual ~CUserAttr();


	void SetName(const String& str_name) { _str_name = str_name; }
	void AddValue(const String& str_col, int type, const String& str_value) ;
	void AddValue(const String& str_col, const SColData& data);
	String GetUserName() { return _str_name; }

	virtual bool Parse(void *data_source /* from nanodbc */) override;
	virtual bool IsValidAt(const std::string& column_name) const override;
	virtual int TypeAt(const std::string& column_name) const override;
	virtual bool IsNullAt(const std::string& column_name) const override;
	virtual std::string ValueAt(const std::string& column_name) const override;

private:
	String _str_name;
	ColDataMap _map_user_data;
};

