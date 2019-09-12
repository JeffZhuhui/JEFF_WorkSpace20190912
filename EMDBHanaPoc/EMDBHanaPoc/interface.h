#ifndef INTERFACE_H
#define INTERFACE_H

#include <vector>
#include <sstream>



/* mapped the table USERS */
class IUser 
{
public:
	virtual ~IUser() {}
    virtual bool Parse(void *pdata_source /* from nanodbc */) = 0;
    virtual bool IsValidAt(const std::string& column_name) const = 0;
    virtual int TypeAt(const std::string& column_name) const = 0;
    virtual bool IsNullAt(const std::string& column_name) const = 0;
    virtual std::string ValueAt(const std::string& column_name) const = 0;
};

/* mapped the table AUTHORIZATION_FILTERS */
class IFilter 
{
public:
    virtual ~IFilter() {}
    virtual std::string GetName() const = 0;
    virtual std::string GetViewId() const = 0;
    virtual std::string GetFilterCondition() const = 0;
};

class IViewMetaData
{
public:
	virtual ~IViewMetaData() {}
    virtual bool Parse(void *pdata_source /* from nanodbc */) = 0;
    virtual std::string GetViewId() const = 0;
    virtual std::string GetSchemaName() const = 0;
    virtual std::string GetViewName() const = 0;
    virtual bool IsValidAt(const std::string& column_name) const = 0;
    virtual int TypeAt(const std::string& column_name) const = 0;
};

class IPolicy 
{
public:
    virtual ~IPolicy() {}
    virtual bool Parse(std::stringstream *pdata_source /* json format */) = 0;
    virtual std::string GetViewId() const = 0;
    virtual std::string GetSchemaName() const = 0;
    virtual std::string GetViewName() const = 0;


    virtual bool IsMatched(const IUser *puser, const IViewMetaData *pview) const = 0;    /* ALWAYS SELECT, IGNORE ACTION */
    virtual std::string ConstructCondition(const IUser *puser, const IViewMetaData *pview) const = 0;

};

IFilter *make_filter(const IUser *puser, const IViewMetaData *pview, const std::vector<IPolicy*>& policys);
IUser *make_users(void *pdata_source);
IViewMetaData *make_view_metadata( const std::string & str_viewid);
IPolicy *make_policy(std::stringstream *pdata_source);

bool collect_policys(std::vector<IPolicy *>& rvec_policy);
bool collect_view_metadata(const std::vector<IPolicy *>& policys, std::vector<IViewMetaData *>& rvec_viewdata);
bool collect_users(std::vector<IUser *>& rvec_user);

bool update_table(const std::vector<IFilter*>& filters);

#endif