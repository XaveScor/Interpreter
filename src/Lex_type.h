#pragma once

#include "Main.h"

namespace Interpreter {
    namespace Lexer {
        enum Lex_t {
            LEX_EMPTY,
            LEX_VAR,
            LEX_NAME,
            LEX_NUMBER,
            LEX_ASSIGN,
            LEX_ENDOP,
            LEX_UNDEFINED,
            LEX_FINISH
        };

        typedef std::map<std::string, Lex_t> keyTable_t;
        const keyTable_t keyTable = {
                {"var", LEX_VAR},
                {"=",   LEX_ASSIGN},
                {";",   LEX_ENDOP},
        };
    }
}
