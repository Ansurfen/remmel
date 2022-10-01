#include "../include/interpreter/lexer.hpp"

using namespace remmel;

Lexer::Lexer(FStr _in) : in(_in), len(_in.length()), pos(0), readPos(0) { this->readChar(); }

REM_TOKEN Lexer::NextToken()
{
    REM_TOKEN ret = REM_TOKEN(REM_TOKEN_TYPE::TOKEN_ILLEGAL, " ");
    this->skipWhitespace();
    switch (this->ch)
    {
    case '\"':
        ret.type = REM_TOKEN_TYPE::TOKEN_STRING;
        ret.Literal = this->readString();
        break;
    case '=':
        ret.type = REM_TOKEN_TYPE::TOKEN_ASSIGN;
        ret.Literal = "=";
        break;
    case '(':
        ret.Literal = "(";
        ret.type = REM_TOKEN_TYPE::TOKEN_LPAREN;
        break;
    case ')':
        ret.Literal = ")";
        ret.type = REM_TOKEN_TYPE::TOKEN_RPAREN;
        break;
    case '{':
        ret.Literal = "{";
        ret.type = REM_TOKEN_TYPE::TOKEN_LBRACE;
        break;
    case '}':
        ret.Literal = "}";
        ret.type = REM_TOKEN_TYPE::TOKEN_RBRACE;
        break;
    case ',':
        ret.Literal = ",";
        ret.type = REM_TOKEN_TYPE::TOKEN_COMMA;
        break;
    case ';':
        ret.Literal = ";";
        ret.type = REM_TOKEN_TYPE::TOKEN_SEMICOLON;
        break;
    case '.':
        ret.Literal = ".";
        ret.type = REM_TOKEN_TYPE::TOKEN_PERIOD;
        break;
    case '<':
        ret.Literal = "<";
        ret.type = REM_TOKEN_TYPE::TOKEN_LT;
        break;
    case '>':
        ret.Literal = ">";
        ret.type = REM_TOKEN_TYPE::TOKEN_GT;
        break;
    case '[':
        ret.Literal = "[";
        ret.type = REM_TOKEN_TYPE::TOKEN_LBRACKET;
        break;
    case ']':
        ret.Literal = "]";
        ret.type = REM_TOKEN_TYPE::TOKEN_RBRACKET;
        break;
    case (int)REM_TOKEN_TYPE::TOKEN_EOF:
        ret.type = REM_TOKEN_TYPE::TOKEN_EOF;
        ret.Literal = "EOF";
        return ret;
    default:
        if (isLetter(this->ch))
        {
            ret.Literal = this->readIdentifier();
            ret.type = LookupIdent(ret.Literal);
            return ret;
        }
        else if (isDigit(this->ch))
        {
            std::string_view temp = this->readNumber();
            return REM_TOKEN(REM_TOKEN_TYPE::TOKEN_INT, temp);
        }
        break;
    }
    this->readChar();
    return ret;
}

void Lexer::skipWhitespace()
{
    while (this->ch == '\t' || this->ch == '\n' || this->ch == '\r' || this->ch == ' ')
        this->readChar();
}

void Lexer::readChar()
{
    if (this->readPos >= this->len)
        this->ch = 0;
    else
        this->ch = this->in[this->readPos];
    this->pos = this->readPos;
    this->readPos += 1;
}

char Lexer::peekChar()
{
    if (this->readPos >= this->len)
        return 0;
    else
        return this->in[this->readPos];
}

FStr Lexer::readString()
{
    uint64_t pos = this->pos + 1;
    while (true)
    {
        this->readChar();
        if (this->ch = 0 || this->ch == '"')
            break;
    }
    return this->in.substr(pos, this->pos - pos);
}

FStr Lexer::readNumber()
{
    uint64_t pos = this->pos;
    while (isDigit(this->ch))
        this->readChar();
    return this->in.substr(pos, this->pos - pos);
}

FStr Lexer::readIdentifier()
{
    uint64_t pos = this->pos;
    while (isLetter(this->ch))
        this->readChar();
    return this->in.substr(pos, this->pos - pos);
}

bool isLetter(char ch)
{
    return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}

bool isDigit(char ch)
{
    return '0' <= ch && ch <= '9';
}