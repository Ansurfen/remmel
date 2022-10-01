#ifndef __REMMEL_TOKEN__
#define __REMMEL_TOKEN__

#include "../lib/constant.hpp"

namespace remmel
{
    enum class REM_TOKEN_TYPE
    {
        TOKEN_ILLEGAL = -1,
        TOKEN_EOF,

        // identifiers
        TOKEN_IDENT,
        TOKEN_CHAR,
        TOKEN_INT,
        TOKEN_LONG,
        TOKEN_FLOAT,
        TOKEN_DOUBLE,
        TOKEN_STRING,
        TOKEN_BOOL,
        TOKEN_NULL,
        TOKEN_LIST,
        TOKEN_MAP,
        TOKEN_STRUCT,
        TOKEN_CONSTRUCT,
        TOKEN_ANY,

        // operator
        TOKEN_ASSIGN, // =

        TOKEN_LT, // <
        TOKEN_GT, // >

        // delimiters
        TOKEN_COMMA,     // ,
        TOKEN_SEMICOLON, // ;
        TOKEN_PERIOD,    // .
        TOKEN_COLON,     // :

        TOKEN_LPAREN,   // (
        TOKEN_RPAREN,   // )
        TOKEN_LBRACE,   // {
        TOKEN_RBRACE,   // }
        TOKEN_LBRACKET, // [
        TOKEN_RBRACKET, // ]

        // keyword
        TOKEN_DEC,
        TOKEN_NEW,
        TOKEN_GET,
        TOKEN_SET,
        TOKEN_DEL,
        TOKEN_AS,
    };

    struct REM_TOKEN
    {
        REM_TOKEN_TYPE type;
        FStr Literal;
        REM_TOKEN();
        REM_TOKEN(REM_TOKEN_TYPE, FStr);
    };

    static HashMap<FStr, REM_TOKEN_TYPE> keywords = {
        {"dec", REM_TOKEN_TYPE::TOKEN_DEC},
        {"set", REM_TOKEN_TYPE::TOKEN_SET},
        {"get", REM_TOKEN_TYPE::TOKEN_GET},
        {"new", REM_TOKEN_TYPE::TOKEN_NEW},
        {"del", REM_TOKEN_TYPE::TOKEN_DEL},
        {"null", REM_TOKEN_TYPE::TOKEN_NULL},
        {"map", REM_TOKEN_TYPE::TOKEN_MAP},
        {"bool", REM_TOKEN_TYPE::TOKEN_BOOL},
        {"string", REM_TOKEN_TYPE::TOKEN_STRING},
        {"float", REM_TOKEN_TYPE::TOKEN_FLOAT},
        {"double", REM_TOKEN_TYPE::TOKEN_DOUBLE},
        {"long", REM_TOKEN_TYPE::TOKEN_LONG},
        {"char", REM_TOKEN_TYPE::TOKEN_CHAR},
        {"as", REM_TOKEN_TYPE::TOKEN_AS},
    };

    REM_TOKEN_TYPE LookupIdent(FStr);
}

#endif