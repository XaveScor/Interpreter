#pragma once

#include "Main.h"

namespace Interpreter {
    namespace Lexer {
        class Lex {
            Lex_t type;
            std::string value;
        public:
            Lex(Lex_t newType = LEX_EMPTY, const std::string newValue = "");

            Lex_t getType();

            std::string getValue();

            friend std::ostream &operator<<(std::ostream &out, Lex el);
        };

    }
}
