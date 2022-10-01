#ifndef __REMMEL_LEXER__
#define __REMMEL_LEXER__

#include "token.hpp"

namespace remmel
{
    class Lexer
    {
    private:
        FStr in;
        uint64_t pos;
        uint64_t readPos;
        uint64_t len;
        char ch;

        void readChar();
        char peekChar();
        void skipWhitespace();
        FStr readString();
        FStr readNumber();
        FStr readIdentifier();

    public:
        Lexer(FStr);
        ~Lexer();
        REM_TOKEN NextToken();
    };

    bool isLetter(char);
    bool isDigit(char);
}

#endif