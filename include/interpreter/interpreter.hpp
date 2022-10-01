#ifndef __REMMEL_INTERPRETER__
#define __REMMEL_INTERPRETER__

#include "lexer.hpp"
#include "ir.h"

namespace remmel
{
    class Interpreter
    {
    private:
        FStr in;

    public:
        Interpreter(FStr _in) : in(_in){};
        ~Interpreter();
        void process()
        {
            eval(parse((void *)&this->in));
        };
    };
}

#endif