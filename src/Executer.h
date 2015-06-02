#pragma once

#include "Main.h"

namespace Interpreter {
    using namespace Lexer;

    class Executer {
        Parser parser;
        Parser::poliz_t code;
        size_t index;

        std::stack<Lex> calc;

        Lex getLex();
        void goTo(size_t position);

        void push(Lex el);

        Lex pop();
    public:
        Executer(std::string fileName);

        void start();
    };
}