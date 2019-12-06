//
// Created by jeff on 2019/12/3.
//

#ifndef SQLPARSERTEST_NXSFHLEX_H
#define SQLPARSERTEST_NXSFHLEX_H


#include <string>


class NxToken {
public:
    enum TOKEN_TYPE {
        LPAREN, // (
        RPAREN, // )
        EQ,     // =
        NEQ,    // <>
        GT,     // >
        EGT,    // >=
        LT,     // <
        ELT,    // <=
        COMMA,  // ,
        DOT,    // .
        LL_ADD, // ||
        QUES_MARK,// ?
        STAR,   // *
        N_CHAR, // N'XX'
//        SELECT,
//        FROM,
//        WHERE,
//        AS,
//        AND,
//        OR,
//        CASE,
//        WHEN,
//        ELSE,
//        THEN,
//        END,
//        LIMIT,
//        TOP,
//        NO, NOT,
//        DISTINCT,
//        UNION,
//        GROUP,
//        BY,
//        ORDER,
//        IS,
//        IN,
//        ON,
//        LIKE,
//        BETWEEN,
//        DESC, ASC,
//        LEFT,
//        OUTER,
//        JOIN,
//        RIGHT,
//        INNER,
//        FOR,
//        UPDATE,
//        WITH,
//        //EXISTS,
//        //
//
//        /*DATA TYPE*/
//        INT,
//        INTEGER,
//        DOUBLE,
//        DATE,
//        CHAR,
//        VARCHAR,
//        NVARCHAR,
//        /*FUNC*/
//        COUNT,
//        CONTAINS,
//        FUZZY,
//        PARAMETERS,
//        MAX,
//        MIN,
//        AVG,
//        SUM,
#define FORMAT(A,B) A,
#include "keywords.h"
#undef  FORMAT
        IDENTIFIER,
        D_NULL,//NULL
        D_LITERAL,
        D_UINTEGER,
        D_INTEGER,
        D_DOUBLE,
        TK_ERR,
        TK_END
    };
    NxToken();
    NxToken(TOKEN_TYPE token_type, const std::string& word);
    TOKEN_TYPE GetType() const;
    const std::string& GetWord() const;
    void Set(TOKEN_TYPE token_type, const std::string& word);
    void Set(TOKEN_TYPE token_type, const char word);
private:
    TOKEN_TYPE      _token_type;
    std::string     _word;
};



class Lex {
public:
    explicit Lex(const std::string& condition);
    const NxToken *GetCurrent() const;
    virtual void Next();
protected:
    char CharAt(unsigned pos);
    std::string Sub(unsigned start, unsigned end);
    unsigned PosInc(unsigned inc);
    unsigned Pos() const;
    void ScanfNumber();
    void ScanfIdentifier();
    void ScanfStrLiteral();
    void ScanfOperator();
    void ScanfWhite();
    void ScanfIdentifierNoQuatMarks();

    void ScanfComment();
    void SingleLineComment();
    void MultiLineComment();

protected:
    NxToken _cur_tk;
    std::string _condition;
    unsigned _pos;

    int _line;
    int _index;
};














#endif //SQLPARSERTEST_NXSFHLEX_H
