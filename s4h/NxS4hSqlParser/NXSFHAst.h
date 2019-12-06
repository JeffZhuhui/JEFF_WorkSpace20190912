//
// Created by jeff on 2019/12/5.
//

#ifndef S4H_TEST_NXSFHAST_H
#define S4H_TEST_NXSFHAST_H

#include "Interface.h"
#include <string>

namespace NXSFH {

    enum AST_TYPE {
        AST_TOP,
        AST_DISTINCT,
        AST_SELECT_EXPR,
        AST_SELECT_EXPRS,
        AST_FROM_EXPR,
        AST_FROM_EXPRS,
        AST_WHERE,
        AST_GROUP,
        AST_GROUPING,
        AST_HAVING,
        AST_ORDER,
        AST_LIMIT
    };

    class AstTop :public IAstStmt {/// TOP uint
    public:
        AstTop();
        virtual ~AstTop();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;

    private:
        AST_TYPE _type;
        NxToken _top;
        NxToken _uint;
    };

    class AstDistinct :public IAstStmt {/// [ALL | DISTINCT]
    public:
        AstDistinct();
        virtual ~AstDistinct();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;
    private:
        AST_TYPE _type;
        NxToken _tk;
    };

    class AstSelectExpr :public IAstStmt {///
    public:
        AstSelectExpr();
        virtual ~AstSelectExpr();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;
    private:
        AST_TYPE _type;
        /*todo*/
    };

    class AstSelectExprList :public IAstStmt {/// AstSelectExpr { [, AstSelectExpr] ...}
    public:
        AstSelectExprList();
        virtual ~AstSelectExprList();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;

    private:
        AST_TYPE _type;
        std::vector<AstSelectExpr*> _vec_exprs;
    };

    class AstFromExpr :public IAstStmt {
    public:
        AstFromExpr();
        virtual ~AstFromExpr();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;

    private:
        AST_TYPE _type;
        /*todo*/
    };

    class AstFromExprList :public IAstStmt {/// AstFromExpr { [, AstFromExpr] ...}
    public:
        AstFromExprList();
        virtual ~AstFromExprList();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;
    private:
        AST_TYPE _type;
        std::vector<AstFromExpr*> _vec_exprs;
    };

    class AstWhereClause :public IAstStmt {
    public:
        AstWhereClause();
        virtual ~AstWhereClause();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;

    private:
        AST_TYPE _type;
        std::vector<NxToken> _vec_tk;
    };
    class AstGroupClause :public IAstStmt {
    public:
        AstGroupClause();
        virtual ~AstGroupClause();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;
    private:
        AST_TYPE _type;
        std::vector<NxToken> _vec_tk;

    };
    class AstHavingClause :public IAstStmt {
    public:
        AstHavingClause();
        virtual ~AstHavingClause();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;
    private:
        AST_TYPE _type;
        std::vector<NxToken> _vec_tk;
    };

    class AstOrderClause :public IAstStmt { ///Order By column-ref
    public:
        AstOrderClause();
        virtual ~AstOrderClause();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;
    private:
        AST_TYPE _type;
        std::vector<NxToken> _vec_tk;
    };

    class AstLimit :public IAstStmt { /// Limit uint [offset uint]
    public:
        AstLimit();
        virtual ~AstLimit();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;
    private:
        AST_TYPE _type;
        std::vector<NxToken> _vec_tk;
//      NxToken _limit;
//      NxToken _offset;
    };


    class AstSelectStmt :public IAstStmt {
    public:
        AstSelectStmt();
        virtual ~AstSelectStmt();
        virtual bool CheckSupport() ;
        virtual bool RewriteWithMaskStrategy(void* connection, const std::vector<IMaskStrategy*>& mask_strategys) ;
        virtual std::u16string Output() ;

    private:
        AST_TYPE _type;
        AstTop * _ast_top;
        AstDistinct * _ast_dist;
        AstSelectExprList * _ast_sexprs;
        AstFromExprList * _ast_fexprs;
        AstWhereClause * _ast_where;
        AstGroupClause * _ast_group;
        AstHavingClause * _ast_hav;
        AstOrderClause * _ast_order;
        AstLimit * _ast_limit;

    };

}


#endif //S4H_TEST_NXSFHAST_H
