#pragma once



#include "interface.h"



struct Condition {
	std::string _attribute;
	enum { EQ, NEQ, GT, GTE, LT, LTE } _operator;
	std::string _value;
	enum { CONSTANT, SUBJECT } _rhs_type;
};

struct Component {
	std::string _id;
	std::string _name;
	std::vector<Condition> _conditions;
};

struct OpComp {
	enum { OP_IN, OP_NOT } _operator;
	std::vector<Component> _components;
};

class CPolicy :
	public IPolicy
{
public:
	CPolicy();
	~CPolicy();

	virtual bool Parse(std::stringstream *pdata_source /* json format */) override;
	virtual std::string GetViewId() const override;
	virtual std::string GetSchemaName() const override;
	virtual std::string GetViewName() const override;


	virtual bool IsMatched(const IUser *puser, const IViewMetaData *pview) const override;    /* ALWAYS SELECT, IGNORE ACTION */
	virtual std::string ConstructCondition(const IUser *puser, const IViewMetaData *pview) const override;


private:
	std::string _str_schema;
	std::string _str_viewid;
	std::string _str_viewname;

// 	Condition m_schema;
// 	Condition m_viewid;
// 	Condition m_viewname;

	std::string _id;
	std::string _full_name;
	std::string _effect_type;
	std::vector<OpComp> _subs;
	std::vector<OpComp> _ress;
};

