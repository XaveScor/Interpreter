#include "Main.h"

namespace Interpreter {
    namespace Lexer {

        void Scanner::getChar() {
            if (notGetCharInNext) {
                notGetCharInNext = false;
                return;
            }
            input.get(currentChar);
            if (input.eof())
                currentChar = EOF;
            if (!isSpace(currentChar))
                buf += currentChar;
        }

        Scanner::Scanner(const std::string &filename) : input(filename.c_str()), buf(1, '\0'), currentState(START),
                                                        notGetCharInNext(false) { }

        Lex Scanner::getLex() {
            currentState = START;
            clearBuf();
            while (true) {
                getChar();
                notGetCharInNext = false;
                switch (currentState) {
                    case START:
                        try {
                            currentState = startState();
                        } catch (const UndefinedType &) {
                            return Lex(LEX_UNDEFINED);
                        }
                        break;
                    case INDENT:
                        if (isSpace(currentChar)) {
                            Lex_t lex = checkLex(buf);
                            if (lex != LEX_EMPTY)
                                return Lex(lex, buf);
                            return Lex(LEX_NAME, buf);
                        }
                        if (isOperation(currentChar)) {
                            input.unget();
                            return Lex(LEX_NAME, buf.substr(0, buf.length() - 1));
                        }
                        break;
                    case STRING:
                        break;
                    case NUMBER:
                        if (isSpace(currentChar))
                            return Lex(LEX_NUMBER, buf);
                        if (isOperation(currentChar)) {
                            input.unget();
                            return Lex(LEX_NUMBER, buf.substr(0, buf.length() - 1));
                        }
                        if (!std::isdigit(currentChar))
                            return Lex(LEX_UNDEFINED);
                        break;
                    case OPERATION:
                        if (isSpace(currentChar)) {
                            Lex_t lex = checkLex(buf);
                            if (lex != LEX_EMPTY)
                                return Lex(lex, buf);
                            return Lex(LEX_UNDEFINED);
                        }
                        if (!isOperation(currentChar))
                            return Lex(LEX_UNDEFINED);
                        break;
                }

            }

        }


        void Scanner::clearBuf() {
            buf.clear();
            currentChar = '\0';
        }

        Scanner::state_t Scanner::startState() {
            notGetCharInNext = true;
            if (currentChar == '"')
                return STRING;
            if (std::isalpha(currentChar))
                return INDENT;
            if (std::isdigit(currentChar))
                return NUMBER;
            if (isOperation(currentChar))
                return OPERATION;

            throw new UndefinedType();
        }

        Lex_t Scanner::checkLex(const std::string lexName) {
            typename keyTable_t::const_iterator it = keyTable.begin();
            Lex_t ret = LEX_EMPTY;

            for (; it != keyTable.end(); ++it)
                if (lexName == it->first) {
                    ret = it->second;
                    break;
                }

            return ret;
        }

        bool Scanner::isSpace(char aChar) {
            switch (aChar) {
                case ' ':
                case '\t':
                case '\n':
                case EOF:
                    return true;
            }
            return false;
        }

        bool Scanner::isOperation(char aChar) {
            switch (aChar) {
                case '=':
                case ';':
                    return true;
            }
            return false;
        }
    }
}
