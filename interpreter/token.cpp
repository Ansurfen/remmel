#include "../include/interpreter/token.hpp"

using namespace remmel;

REM_TOKEN_TYPE LookupIdent(FStr ident)
{
    return keywords.find(ident) != keywords.end() ? keywords[ident] : REM_TOKEN_TYPE::TOKEN_IDENT;
}