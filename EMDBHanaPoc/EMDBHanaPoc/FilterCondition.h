#pragma once
#include "interface.h"
class CFilterCondition :
	public IFilter
{
public:
	CFilterCondition();
	CFilterCondition(const std::string & username, const std::string & viewid,const std::string & condition)
		:_username(username), _viewid(viewid), _condition(condition){}
	~CFilterCondition();

	virtual std::string GetName() const override;
	virtual std::string GetViewId() const override;
	virtual std::string GetFilterCondition() const override;

private:
	std::string _username;
	std::string _viewid;
	std::string _condition;
};

