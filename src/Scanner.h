#pragma once

#include "Main.h"

namespace Interpreter {
    namespace Lexer {

        class UndefinedType : std::exception {
        };

        class Scanner {
            std::ifstream input;
            enum state_t {
                START, INDENT, STRING, NUMBER, OPERATION, SPACE
            };

            char currentChar;
            std::string buf;
            state_t currentState;

            void getChar();

            void clearBuf();

            state_t startState();

            Lex_t checkLex(std::string lexName);

            bool isSpace(char aChar);

            bool isOperation(char aChar);

            std::string trim(const std::string &str, size_t end, size_t start = 0);

            void unGetChar();

        public:
            Scanner(const std::string &filename);

            Lex getLex();

        };

    }
}
