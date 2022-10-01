#ifndef __REMMEL_PARSER__
#define __REMMEL_PARSER__

#include "../../lib/libr.hpp"
#include "../lexer.hpp"

namespace remmel
{
    class Parser
    {
#define CurTokenIs(t) this->curTokenIs(t)
#define PeekTokenIs(t) this->peekTokenIs(t)
#define TokenNotEqual(t) !this->curTokenIs(t)
#define ExpectCurTokenNotEqual(t) !expectCurTokenIs(t)
#define ExpectPeekTokenNotEqual(t) !expectPeekTokenIs(t)
#define CurTokenType this->curToken.type
#define PeekTokenType this->peekToken.type
#define CurTokenLiteral this->curToken.Literal
#define PeekTokenLiteral this->peekToken.Literal
#define DRES std::tuple<uint32_t, Node *>
#define DRESOf(res, i) std::get<i>(res)
    private:
        Lexer *l;
        std::vector<std::string_view> errors;
        REM_TOKEN curToken;
        REM_TOKEN peekToken;
        // std::queue<Command *> *cmds;

        void nextToken();
        bool curTokenIs(TOKEN_TYPE);
        bool peekTokenIs(TOKEN_TYPE);
        bool expectCurTokenIs(TOKEN_TYPE);
        bool expectPeekTokenIs(TOKEN_TYPE);

        void parseDec();
        void parseNew();
        void parseDel();
        void parseSet();
        void parseGet();

        // DRES parseDecNode(bool);
        // Node *parseNewNode();

    public:
        Parser(std::string_view in) : l(new Lexer(in))
        {
            this->nextToken();
            this->nextToken();
        };
        ~Parser()
        {
            delete this->l;
        };
        void Parse();
        // std::queue<Command *> *GetCommands();
    };
}

#endif