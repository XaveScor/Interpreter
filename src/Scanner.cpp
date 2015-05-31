#include "Main.h"

namespace Interpreter {
    namespace Lexer {

        void Scanner::getChar() {
            input.get(currentChar);
            if (input.eof())
                currentChar = EOF;

            buf += currentChar;
        }

        void Scanner::unGetChar() {
            input.unget();
            input.clear();
            buf = trim(buf, 1);
        }

        Scanner::Scanner(const std::string &filename) : input(filename.c_str()), buf(1, '\0'), currentState(START), curBufPosition(0) {
            Lex lex;
            do {
                lex = readLex();
                lexBuf.push_back(lex);
            }
            while (lex.getType() != Lexer::LEX_FINISH);
            lexBuf.push_back(lex);
        }

        Lex Scanner::readLex() {
            currentState = START;
            clearBuf();
            while (true) {
                getChar();
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
                            unGetChar();
                            Lex_t lex = checkLex(buf);
                            if (lex != LEX_EMPTY)
                                return Lex(lex, buf);
                            return Lex(LEX_NAME, buf);
                        }
                        if (isOperation(currentChar)) {
                            unGetChar();
                            Lex_t lex = checkLex(buf);
                            if (lex != LEX_EMPTY)
                                return Lex(lex, buf);
                            return Lex(LEX_NAME, buf);
                        }
                        if (currentChar == EOF)
                            return Lex(LEX_UNDEFINED);
                        break;
                    case STRING:
                        if (currentChar == '"')
                            return Lex(LEX_STRING, trim(buf, 1, 1)); // Delete first and last "
                        if (currentChar == EOF)
                            return Lex(LEX_UNDEFINED);
                        break;
                    case NUMBER:
                        if (isSpace(currentChar)) {
                            unGetChar();
                            return Lex(LEX_NUMBER, buf);
                        }
                        if (isOperation(currentChar)) {
                            unGetChar();
                            return Lex(LEX_NUMBER, buf);
                        }
                        if (!(std::isdigit(currentChar) || currentChar == '.'))
                            return Lex(LEX_UNDEFINED);
                        break;
                    case OPERATION:
                        if (!isOperation(currentChar)) {
                            while (buf.length()) {
                                unGetChar();
                                Lex_t lex = checkLex(buf);
                                if (lex != LEX_EMPTY)
                                    return Lex(lex, buf);
                            }
                            return Lex(LEX_UNDEFINED);
                        }
                        break;
                    case SPACE:
                        if (currentChar == EOF)
                            return Lex(LEX_FINISH, "FINISH");
                        currentState = START;
                        clearBuf();
                        break;
                }

            }

        }


        void Scanner::clearBuf() {
            buf.clear();
            currentChar = '\0';
        }

        Scanner::state_t Scanner::startState() {
            unGetChar();
            if (currentChar == '"') {
                getChar();
                return STRING;
            }
            if (std::isalpha(currentChar))
                return INDENT;
            if (std::isdigit(currentChar))
                return NUMBER;
            if (isOperation(currentChar))
                return OPERATION;
            if (isSpace(currentChar))
                return SPACE;

            throw new UndefinedType();
        }

        Lex_t Scanner::checkLex(std::string lexName) {
            std::string::iterator lexIt = lexName.begin();
            for (; lexIt != lexName.end(); ++lexIt)
                if (std::isupper(*lexIt))
                    *lexIt = (char) std::tolower(*lexIt);

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
                case '\0':
                    return true;
            }
            return false;
        }

        bool Scanner::isOperation(char aChar) {
            switch (aChar) {
                case '=':
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '&':
                case '|':
                case '!':
                case '(':
                case ')':
                case '{':
                case '}':
                case '>':
                case '<':
                case ';':
                case ',':
                    return true;
            }
            return false;
        }

        std::string Scanner::trim(const std::string &str, size_t end, size_t start/* = 0*/) {
            return str.substr(start, str.length() - end - start);
        }


        Lex Scanner::getLex() {
            if (curBufPosition == lexBuf.size() - 1)
                return lexBuf.back();
            return lexBuf[curBufPosition++];
        }

        void Scanner::unGetLex() {
            if (!curBufPosition)
                return;
            --curBufPosition;
        }
    }
}
