//
// Created by jeff on 2019/12/3.
//

#include "NXSFHLex.h"
#include <map>
#include <assert.h>
#include <strings.h>

#define EOI -1

NxToken::NxToken() : _token_type(TK_ERR) {}

NxToken::TOKEN_TYPE NxToken::GetType() const { return _token_type; }

const std::string& NxToken::GetWord() const { return _word; }

void NxToken::Set(TOKEN_TYPE token_type, const std::string& word) {
    if(_token_type != NxToken::TK_END)  _token_type = token_type;
    _word = word;
}
void NxToken::Set(TOKEN_TYPE token_type, const char word) {
    if(_token_type != NxToken::TK_END)  _token_type = token_type;
    _word = word;
}



int StrCaseCmp(const char *s1, const char *s2) {
#ifndef WIN32
    return strcasecmp(s1, s2);
#else
    return stricmp(s1, s2);
#endif
}
struct IgnoreCaseCmp : public std::binary_function<std::string, std::string, bool> {
    bool operator()(const std::string& left, const std::string& right) const {
        return StrCaseCmp(left.c_str(), right.c_str()) < 0;
    }
};
//-------------------------------------------------------------------
const std::map<std::string, NxToken::TOKEN_TYPE, IgnoreCaseCmp > KEYWORDS {
//        {"SELECT",  NxToken::SELECT},
//        {"FROM",    NxToken::FROM   },
//        {"WHERE",   NxToken::WHERE},
//        {"AS",      NxToken::AS},
//        {"AND",     NxToken::AND},
//        {"OR",      NxToken::OR},
//        {"CASE",    NxToken::CASE},
//        {"WHEN",    NxToken::WHEN},
//        {"ELSE",    NxToken::ELSE},
//        {"THEN",    NxToken::THEN},
//        {"END",     NxToken::END},
//        {"LIMIT",   NxToken::LIMIT},
//        {"TOP",     NxToken::TOP},
//        {"DISTINCT",NxToken::DISTINCT},
//        {"UNION",   NxToken::UNION},
//        {"GROUP",   NxToken::GROUP},
//        {"BY",      NxToken::BY},
//        {"ORDER",   NxToken::ORDER},
//        {"IN",      NxToken::IN},
//        {"ON",      NxToken::ON},
//        {"IS",      NxToken::IS},
//        {"NOT",      NxToken::NOT},
//        {"LIKE",    NxToken::LIKE},
//        {"DESC",    NxToken::DESC},
//        {"ASC",    NxToken::ASC},
//        {"COUNT",   NxToken::COUNT},
//        {"LEFT",    NxToken::LEFT},
//        {"RIGHT",   NxToken::RIGHT},
//        {"OUTER",   NxToken::OUTER},
//        {"INNER",   NxToken::INNER},
//        {"JOIN",    NxToken::JOIN},
//        {"FOR",     NxToken::FOR},
//        {"UPDATE",  NxToken::UPDATE},
//        {"WITH",    NxToken::WITH},
//        {"PARAMETERS",NxToken::PARAMETERS},
//        {"FUZZY",   NxToken::FUZZY},
//        {"CONTAINS",NxToken::CONTAINS},
//        {"MAX",     NxToken::MAX},
//        {"MIN",     NxToken::MIN},
//        {"INT",     NxToken::INT},
//        {"INTEGER", NxToken::INTEGER},
//        {"DOUBLE",   NxToken::DOUBLE},
//        {"DATE",    NxToken::DATE},
//        {"CHAR",    NxToken::CHAR},
//        {"VARCHAR", NxToken::VARCHAR},
//        {"NVARCHAR",NxToken::NVARCHAR},
//        {"NULL",NxToken::D_NULL },
//
//
//        {"AVG",     NxToken::AVG},
//        {"SUM",     NxToken::SUM},
//        {"BETWEEN", NxToken::BETWEEN},
//        {"NO",      NxToken::NO}

        {"NULL",      NxToken::D_NULL}
#define FORMAT(A,B)  ,{B,NxToken::A}
#include "keywords.h"
#undef  FORMAT


};

bool check_reserved_keyword(const std::string &word, NxToken& tk) {
    auto it = KEYWORDS.find(word);
    if (it != KEYWORDS.end()) {
        tk.Set(it->second, word);
        return true;
    }
    return false;
}
bool is_white(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == 'f';
}

bool is_identifier_begin(char c) {
    return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || '_' == c;
}

bool is_identifier_body(char c) {
    return is_identifier_begin(c) || ('0' <= c && c <= '9');
}

bool is_dec(char c) {
    return '0' <= c && c <= '9';
}
bool is_dot(char c) {
    return '.' == c;
}

bool is_escaped(char c, char& escaped) {
    //return c == '\\' || c == '"' || c == 'r' || c == 'n';
    switch (c) {
        case '\\' : {
            escaped = '\\';
            return true;
        } break;
        case '"' : {
            escaped = '"';
            return true;
        } break;
        case 'r' : {
            escaped = '\r';
            return true;
        } break;
        case 'n' : {
            escaped = '\n';
            return true;
        } break;
        default: {
            return false;
        }
    }
}

//---------------------------------------------------------------------

Lex::Lex(const std::string& condition) : _condition(condition), _pos(0) {}

const NxToken *Lex::GetCurrent() const { return &_cur_tk; }

char Lex::CharAt(unsigned pos) {
    if (pos < _condition.length()) return _condition[pos];
    else return EOI;
}

unsigned Lex::Pos() const {
    return _pos;
}

unsigned Lex::PosInc(unsigned inc) {

    for(int i = 0; i < inc; ++i) {
        _pos++;
        if(CharAt(_pos) == '\n') {
            _line++;
            _index = 0;
        } else {
            _index++;
        }
    }
    if (_pos > _condition.length()) _cur_tk.Set(NxToken::TK_END, "");
    return _pos;
}


void Lex::Next() {
    if (_cur_tk.GetType() == NxToken::TK_END) return;
    while (true) {
        switch (CharAt(Pos())) {
            case ' ':  /* go through */
            case '\t': /* go through */
            case '\n': /* go through */
            case '\r': /* go through */
            case '\f': {
                ScanfWhite();
            } break;
            case '-': {
                char c1 = CharAt(Pos() + 1);
                if (c1 == '-') {
                    ScanfComment();
                } else if(is_dec(c1)) {
                    return ScanfNumber();
                }else {
                    return ScanfOperator();
                }

            } break;
            case '/': {
                if (CharAt(Pos() + 1) == '*')
                    ScanfComment();
                else
                    return ScanfOperator();
            }  break;
            case '0' : /* go through */
            case '1' : /* go through */
            case '2' : /* go through */
            case '3' : /* go through */
            case '4' : /* go through */
            case '5' : /* go through */
            case '6' : /* go through */
            case '7' : /* go through */
            case '8' : /* go through */
            case '9' : {
                 ScanfNumber();
            } return;
            case '(' : /* go through */
            case ')' : /* go through */
            case '[' : /* go through */
            case ']' : /* go through */
            case '*' : /* go through */
            case ',' : /* go through */
            case '.' : /* go through */
            case '=' : /* go through */
            case '>' : /* go through */
            case '<' : {
                 ScanfOperator();
            } return;
            case '"' : {
                ScanfIdentifier();
            } return;
            case '\'' : {
                ScanfStrLiteral();
            } return;
            case '|': {
                PosInc(1);
                if(CharAt(Pos()) == '|') {
                    _cur_tk.Set(NxToken::LL_ADD, "||");
                    PosInc(1);
                }else {
                    _cur_tk.Set(NxToken::TK_ERR, "|");
                }
            } return;
            case '?':{
                _cur_tk.Set(NxToken::QUES_MARK, "?");
                PosInc(1);
            } return;
            case EOI : {
                _cur_tk.Set(NxToken::TK_END, "");

            } return;
            default: {
                if (is_identifier_begin(CharAt(Pos()))) {
                    return ScanfIdentifierNoQuatMarks();
                } else {
                    /* Skip The Unknown Char */
                    PosInc(1);
                }
            }
        }
    }
}

void Lex::ScanfWhite() {
    char c = CharAt(Pos());
    while (is_white(c)) c = CharAt(PosInc(1));
}

void Lex::ScanfOperator() {
    switch(CharAt(Pos())) {
        case '*' :{
            _cur_tk.Set(NxToken::STAR,'*');
            PosInc(1);
        } break;
        case ',' : {
            _cur_tk.Set(NxToken::COMMA,',');
            PosInc(1);
        } break;
        case '.' : {
            _cur_tk.Set(NxToken::DOT,'.');
            PosInc(1);
        }  break;
        case '(' :  {
            _cur_tk.Set(NxToken::LPAREN,'(');
            PosInc(1);
        } break;
        case ')' :  {
            _cur_tk.Set(NxToken::RPAREN,')');
            PosInc(1);
        } break;
        case '=':{
            _cur_tk.Set(NxToken::EQ, "=");
            PosInc(1);
        } break;
        case '>':{
            PosInc(1);
            if(CharAt(Pos()) == '=') {
                _cur_tk.Set(NxToken::EGT, ">=");
                PosInc(1);
            } else {
                _cur_tk.Set(NxToken::GT, ">");
            }
        } break;
        case '<':{
            PosInc(1);
            if(CharAt(Pos()) == '=') {
                _cur_tk.Set(NxToken::ELT, "<=");
                PosInc(1);
            } else if (CharAt(Pos()) == '>') {
                _cur_tk.Set(NxToken::NEQ, "<>");
                PosInc(1);
            }else{
                _cur_tk.Set(NxToken::LT, "<");
            }
        } break;
        case '[' : /* go through */
        case ']' : /* go through */ {
            /* todo err*/
            PosInc(1);
        } break;
        default:
        {
            PosInc(1);
            /*todo err*/
        }

    }
}
void Lex::ScanfNumber() {
    std::string buf;
    NxToken::TOKEN_TYPE tp = NxToken::D_UINTEGER;
    if (CharAt(Pos()) == '-'){
        tp = NxToken::D_INTEGER;
        buf+='-';
        PosInc(1);
    }
    while(is_dec( CharAt(Pos()) ) ) {
        buf+=CharAt(Pos());
        PosInc(1);
    }
//    if (buf.compare("-") == 0) {
//        _cur_tk.Set(NxToken::TK_ERR, buf);
//        return;
//    }

    if(is_dot(CharAt(Pos()))) {
        buf+=CharAt(Pos());
        PosInc(1);
        while( is_dec(CharAt(Pos())) ) {
            buf+=CharAt(Pos());
            PosInc(1);
        }
        char c = CharAt(Pos());
        if(is_identifier_begin(c)) {
            _cur_tk.Set(NxToken::TK_ERR, buf);
        }else {
            _cur_tk.Set(NxToken::D_DOUBLE, buf);
        }

    } else {
        char c = CharAt(Pos());
        if(is_identifier_begin(c)) {
            _cur_tk.Set(NxToken::TK_ERR, buf);
        }else {
            _cur_tk.Set(tp, buf);
        }
    }
}

void Lex::ScanfIdentifier() {
    assert(CharAt(Pos()) == '"');
    PosInc(1);
    std::string buf;
    char c = CharAt(Pos());
    while (c != '"' && c != EOI) {
        if (c == '\\') {
            char next = CharAt(Pos()+1);
            char escaped = 0;
            if (is_escaped(next, escaped)) {
                buf += escaped;
                PosInc(1);
            } else {
                _cur_tk.Set(NxToken::TK_ERR, "Unexpected Escape Char");
                return;
            }
        } else {
            buf += c;
        }
        c = CharAt(PosInc(1));
    }
    if (c == '"') {
        PosInc(1);
        _cur_tk.Set(NxToken::IDENTIFIER, buf);
    } else {
        _cur_tk.Set(NxToken::TK_ERR, "Unterminated String IDENTIFIER");
    }
}

void Lex::ScanfStrLiteral() {
    assert(CharAt(Pos()) == '\'');
    PosInc(1);
    std::string buf;
    char c = CharAt(Pos());
    while (c != '\'' && c != EOI) {
        if (c == '\\') {
            char next = CharAt(Pos()+1);
            char escaped = 0;
            if (is_escaped(next, escaped)) {
                buf += escaped;
                PosInc(1);
            } else {
                _cur_tk.Set(NxToken::TK_ERR, "Unexpected Escape Char");
                return;
            }
        } else {
            buf += c;
        }
        c = CharAt(PosInc(1));
    }
    if (c == '\'') {
        PosInc(1);
        _cur_tk.Set(NxToken::D_LITERAL, buf);
    } else {
        _cur_tk.Set(NxToken::TK_ERR, "Unterminated String Literal");
    }
}

void Lex::ScanfIdentifierNoQuatMarks() {
    int pos = Pos();
    std::string buf;
    while( is_identifier_body(CharAt(Pos()) )) {
        buf += CharAt(Pos());
        PosInc(1);
    }
    NxToken tk;
    if (check_reserved_keyword(buf, tk)) {
        _cur_tk = tk;
    }else {
        _cur_tk.Set(NxToken::IDENTIFIER, buf);
    }
    if(buf=="N" && CharAt(Pos())=='\'') {
        _cur_tk.Set(NxToken::N_CHAR, 'N');
    }
}

void Lex::ScanfComment() {
    if (CharAt(Pos()) == '-' && CharAt(Pos() + 1) == '-') {
        SingleLineComment();
    } else if (CharAt(Pos()) == '/' && CharAt(Pos() + 1) == '*') {
        MultiLineComment();
    }
}


void Lex::SingleLineComment() {
    PosInc(2);    /* skip -- */
    while (CharAt(Pos()) != EOI && CharAt(Pos()) != '\n')
        PosInc(1);
    if (CharAt(Pos()) == '\n') {
        PosInc(1);
    }

}

void Lex::MultiLineComment() {
    PosInc(2);  /* skip */
    char c1 = CharAt(Pos()), c2 = CharAt(Pos() + 1);
    while (c1 != EOI && c2 != EOI) {
        if (c1 == '*' && c2 == '/')
            break;
        PosInc(1);
        c1 = CharAt(Pos()), c2 = CharAt(Pos() + 1);
    }
    if (c1 == '*' && c2 == '/')
        PosInc(2);  /* skip  */
    else {
        /* unterminated multiline comment */
        _cur_tk.Set(NxToken::TK_ERR, "unterminated multiline comment");
    }
}
