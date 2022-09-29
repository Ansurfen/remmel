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
        Lexer(FStr _in) : in(_in), len(_in.length()), pos(0), readPos(0) { this->readChar(); }
        ~Lexer();
        REM_TOKEN NextToken();
    };

    bool isLetter(char);
    bool isDigit(char);
}

#endif