//
// Created by jeff on 2019/12/5.
//

#ifndef S4H_TEST_INTERFACE_H
#define S4H_TEST_INTERFACE_H

#include <string>

/*
 * this module need to run queryPC cpp sdk on linux
 * so need 2 days
 * */
class IMaskStrategy {
public:
    virtual ~IMaskStrategy() {}
    virtual std::u16string GetMaskedColumn() = 0;
    // include the condition's column ref and the masked column
    virtual std::vector<std::u16string> GetReferencedColumn() = 0;
    virtual std::string MakeExpression(const std::u16string& scope) = 0;
    /* todo */
};

std::vector<IMaskStrategy*> query_pc(/* todo */);

/*
 * this module is the rewrite sql module
 * contains a simple hana sql lexer conponent, parser component, and apply mask strategy component
 * need 8 days
 * */
class IAstStmt {
public:
    virtual ~IAstStmt() { }
    /*
     *
     * */
    virtual bool CheckSupport() = 0;
    /*
     * return : is the ast really modified
     * */
    virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) = 0;
    virtual std::u16string Output() = 0;
};

IAstStmt *parse_sql(const std::u16string& sql);

/*
 * todo
 * We need a sql prefilter
 * use hana sql lexer analyze and blacklist, white list inplement it
 * need 0.5~1 days
 * */
bool is_sql_need_mask(const std::u16string& sql);


#endif //S4H_TEST_INTERFACE_H
