#include "Main.h"

namespace Interpreter {
    using namespace Lexer;

    Parser::Parser(std::string fileName) : lexer(fileName) { }

    void Parser::getLex() {
        lex = lexer.getLex();
        lexType = lex.getType();
        lexValue = lex.getValue();
//        std::cout << "LEX: " << lexValue << std::endl;
    }

    void Parser::start() {
        startPoint();
        poliz.push_back(Lex(LEX_FINISH, ""));
    }

    void Parser::startPoint(Lex_t second /* = LEX_FINISH*/) {
        getLex();
        while (lexType != LEX_FINISH && lexType != second) {
            switch (lexType) {
                case LEX_FUNCTION:
                    functionPoint();
                    break;
                case LEX_VAR:
                    varPoint();
                    break;
                case LEX_WHILE:
                    cyclePoint();
                    break;
                case LEX_IF:
                    conditionPoint();
                    break;
                case LEX_READ:
                    readPoint();
                    break;
                case LEX_WRITE:
                    writePoint();
                    break;
                case LEX_ENDOP:
                    break;
                case LEX_NAME:
                    unGetLex();
                    namePoint();
                    break;
                default:
                    if (second != LEX_FINISH && lexType == second)
                        break;
                    throw lex;
            }
            getLex();
        }

        while (!operators.empty()) {
            poliz.push_back(operators.top());
            operators.pop();
        }
    }

    void Parser::functionPoint() {

    }

    void Parser::varPoint(bool create) {
        getLex();
        if (lexType != LEX_NAME)
            throw lex;
        if (create) {
            if (data.count(lexValue))
                throw "";
            data.insert(std::make_pair(lexValue, Lex(LEX_STRING, "")));
        }
        else {
            if (!data.count(lexValue))
                throw "";
        }
        poliz.push_back(Lex(POLIZ_ADDRESS, lex.getValue()));

        getLex();
        switch (lexType) {
            case LEX_ASSIGN:
            case LEX_PLUSEQ:
            case LEX_MINUSEQ:
            case LEX_MULEQ:
            case LEX_DIVEQ:
            case LEX_MODEQ:
                break;
            case LEX_ENDOP:
                goto endop;
            case LEX_COMMA:
                goto comma;
            default:
                throw lex;
        }
        operators.push(lex);
        expressionPoint();

        poliz.push_back(operators.top());
        operators.pop();

        getLex();
        comma:
        if (lexType == LEX_COMMA) {
            varPoint(true);
            return;
        }
        endop:
        if (lexType != LEX_ENDOP)
            throw lex;
    }

    void Parser::expressionPoint() {
        enum {
            EL_NUMBER, EL_NAME, EL_OPERATION
        } lastElType = EL_OPERATION;
        bool isBreak = true;
        operators.push(LEX_EMPTY);
        while (isBreak) {
            getLex();
            switch (lexType) {
                case LEX_NUMBER:
                case LEX_TRUE:
                case LEX_FALSE:
                case LEX_STRING:
                case LEX_NAME:
                    if (lastElType != EL_OPERATION)
                        throw lex;
                    poliz.push_back(lex);
                    lastElType = EL_NUMBER;
                    break;
                case LEX_PLUS:
                case LEX_MINUS:
                case LEX_DIV:
                case LEX_MUL:
                case LEX_AND:
                case LEX_OR:
                case LEX_NOT:
                case LEX_INC:
                case LEX_DEC:
                case LEX_MORE:
                case LEX_MOREEQ:
                case LEX_LESS:
                case LEX_LESSEQ:
                case LEX_EQ:
                case LEX_NOTEQ: {
                    if (lastElType == EL_OPERATION)
                        throw lex;
                    if (!operators.empty()) {
                        size_t priority = getPriorityByOperation(lexType);
                        while (priority > getPriorityByOperation(operators.top().getType())) {
                            poliz.push_back(operators.top());
                            operators.pop();
                        }
                    }
                    operators.push(lex);
                    lastElType = EL_OPERATION;
                    break;
                }
                case LEX_RBRACKET:
                    while (operators.top().getType() != LEX_LBRACKET) {
                        if (operators.top().getType() == LEX_EMPTY) {
                            operators.pop();
                            continue;
                        }
                        poliz.push_back(operators.top());
                        operators.pop();
                    }
                    operators.pop(); //Delete bracket
                    break;
                case LEX_LBRACKET:
                    operators.push(lex);
                    break;
                default:
                    unGetLex();
                    while (operators.top().getType() != LEX_EMPTY) {
                        poliz.push_back(operators.top());
                        operators.pop();
                    }
                    operators.pop();
                    isBreak = false;
            }
        }
    }

    size_t Parser::getPriorityByOperation(Lex_t operation) const {
        return operationPriority.find(operation)->second;
    }

    void Parser::cyclePoint() {
        getLex();
        size_t startCycle = poliz.size();
        if (lexType != LEX_LBRACKET)
            throw lex;
        unGetLex();
        expressionPoint();
        poliz.push_back(Lex(POLIZ_FALSEGO));
        size_t firstGoTo = poliz.size() - 1;

        getLex();
        if (lexType != LEX_LFBRACKET)
            throw lex;
        blockPoint();
        getLex();
        if (lexType != LEX_RFBRACKET)
            throw lex;
        poliz.push_back(Lex(POLIZ_GO, numToStr(startCycle)));
        poliz[firstGoTo] = Lex(POLIZ_FALSEGO, numToStr(poliz.size()));
    }

    void Parser::conditionPoint() {
        getLex();
        if (lexType != LEX_LBRACKET)
            throw lex;
        unGetLex();
        expressionPoint();

        poliz.push_back(Lex(POLIZ_FALSEGO));
        size_t firstGoTo = poliz.size() - 1;

        getLex();
        if (lexType != LEX_LFBRACKET)
            throw lex;
        blockPoint();
        getLex();
        if (lexType != LEX_RFBRACKET)
            throw lex;
        poliz[firstGoTo] = Lex(POLIZ_FALSEGO, numToStr(poliz.size()));

        getLex();
        if (lexType != LEX_ELSE) {
            unGetLex();
            return;
        }
        poliz.push_back(Lex(POLIZ_GO));
        size_t secondGoTo = poliz.size() - 1;
        getLex();
        if (lexType != LEX_LFBRACKET)
            throw lex;
        blockPoint();
        getLex();
        if (lexType != LEX_RFBRACKET)
            throw lex;
        poliz[secondGoTo] = Lex(POLIZ_GO, numToStr(secondGoTo));
    }

    void Parser::readPoint() {
        getLex();
        if (lexType != LEX_LBRACKET)
            throw lex;
        getLex();
        if (lexType != LEX_NAME)
            throw lex;
        poliz.push_back(lex);
        poliz.push_back(Lex(LEX_READ));

        getLex();
        if (lexType != LEX_RBRACKET)
            throw lex;

        getLex();
        if (lexType != LEX_ENDOP)
            throw lex;
    }

    void Parser::writePoint() {
        getLex();
        if (lexType != LEX_LBRACKET)
            throw lex;
        unGetLex();
        expressionPoint();
        poliz.push_back(Lex(LEX_WRITE));

        getLex();
        if (lexType != LEX_ENDOP)
            throw lex;
    }

    void Parser::blockPoint() {
        startPoint(LEX_RFBRACKET);
        unGetLex();
    }

    void Parser::unGetLex() {
        lexer.unGetLex();
    }

    void Parser::namePoint() {
        varPoint(false);
    }
}
