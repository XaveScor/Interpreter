#pragma once

#include "Main.h"

namespace Interpreter {
    namespace Lexer {

        class Scanner {
            std::ifstream input;
            enum state_t {
                START, INDENT, STRING, NUMBER, OPERATION
            };

            char currentChar;
            std::string buf;
            state_t currentState;

            void getChar();

            void clearBuf();

            state_t startState();

            Lex_t checkLex(const std::string lexName);

            bool isSpace(char aChar);

            class UndefinedType : std::exception {
            };

            bool notGetCharInNext;

            bool isOperation(char aChar);

        public:
            Scanner(const std::string &filename);

            Lex getLex();


        };

    }
}
