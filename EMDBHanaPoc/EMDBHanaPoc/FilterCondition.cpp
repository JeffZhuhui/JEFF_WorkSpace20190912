#include "FilterCondition.h"
#include "UserAttr.h"


CFilterCondition::CFilterCondition()
{
}


CFilterCondition::~CFilterCondition()
{
}

std::string CFilterCondition::GetName() const
{
	return _username;
}

std::string CFilterCondition::GetViewId() const
{
	return _viewid;
}

std::string CFilterCondition::GetFilterCondition() const
{
	return _condition;
}

IFilter *make_filter(const IUser *puser, const IViewMetaData *pview, const std::vector<IPolicy*>& policys) 
{
	
	std::string str_condition;
	for (size_t nPolicy = 0; nPolicy < policys.size(); nPolicy++) {
		IPolicy *pPolicy = policys[nPolicy];
		if (pPolicy && pPolicy->IsMatched(puser, pview)) {
			std::string str_con = pPolicy->ConstructCondition(puser, pview);
			if (!str_con.empty()) {
				if (!str_condition.empty()) {
					str_condition += " OR ";
				}
				str_condition += " " + str_con + " ";
			}
		}
	}
	if (str_condition.empty()) {
		return NULL;
	}
	IFilter * pFilter = new CFilterCondition(((CUserAttr*)puser)->GetUserName(),pview->GetViewId(), str_condition);

	return pFilter;
}
