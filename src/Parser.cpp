#include "Main.h"

namespace Interpreter {
    using namespace Lexer;

    Parser::Parser(std::string fileName) : lexer(fileName) { }

    void Parser::getLex() {
        lex = lexer.getLex();
        lexType = lex.getType();
        lexValue = lex.getValue();
        std::cout << "LEX: " << lexValue << std::endl;
    }

    void Parser::start() {
        startPoint();
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
                case LEX_EMPTY:
                    break;
                case LEX_NUMBER:
                    break;
                case LEX_STRING:
                    break;
                case LEX_ASSIGN:
                    break;
                case LEX_DOT:
                    break;
                case LEX_UNDEFINED:
                    break;
                case LEX_FINISH:
                    break;
                case LEX_PLUS:
                    break;
                case LEX_MINUS:
                    break;
                case LEX_MUL:
                    break;
                case LEX_DIV:
                    break;
                case LEX_MOD:
                    break;
                case LEX_TRUE:
                    break;
                case LEX_FALSE:
                    break;
                case LEX_OR:
                    break;
                case LEX_AND:
                    break;
                case LEX_NOT:
                    break;
                case LEX_RBRACKET:
                    break;
                case LEX_LBRACKET:
                    break;
                case LEX_RFBRACKET:
                    break;
                case LEX_LFBRACKET:
                    break;
                case LEX_DO:
                    break;
                case LEX_FOR:
                    break;
                case LEX_IN:
                    break;
                case LEX_BREAK:
                    break;
                case LEX_CONTINUE:
                    break;
                case LEX_ELSE:
                    break;
                case LEX_PLUSEQ:
                    break;
                case LEX_MINUSEQ:
                    break;
                case LEX_MULEQ:
                    break;
                case LEX_DIVEQ:
                    break;
                case LEX_MODEQ:
                    break;
                case LEX_MORE:
                    break;
                case LEX_LESS:
                    break;
                case LEX_MOREEQ:
                    break;
                case LEX_LESSEQ:
                    break;
                case LEX_EQ:
                    break;
                case LEX_NOTEQ:
                    break;
                case LEX_INC:
                    break;
                case LEX_DEC:
                    break;
                case LEX_TYPEOF:
                    break;
                case LEX_RETURN:
                    break;
                case LEX_COMMA:
                    break;
                case POLIZ_GO:
                    break;
                case POLIZ_FALSEGO:
                    break;
                case POLIZ_LABEL:
                    break;
                case POLIZ_ADDRESS:
                    break;
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

    void Parser::varPoint() {
        getLex();
        if (lexType != LEX_NAME)
            throw lex;
        poliz.push_back(lex);

        getLex();
        switch (lexType) {
            case LEX_ASSIGN:
            case LEX_PLUSEQ:
            case LEX_MINUSEQ:
            case LEX_MULEQ:
            case LEX_DIVEQ:
            case LEX_MODEQ:
                break;
            default:
                throw lex;
        }
        operators.push(lex);
        expressionPoint();

        poliz.push_back(operators.top());
        operators.pop();

        getLex();
        if (lexType == LEX_COMMA) {
            varPoint();
            return;
        }
        if (lexType != LEX_ENDOP)
            throw lex;
    }

    void Parser::expressionPoint() {
        enum {
            EL_NUMBER, EL_NAME, EL_OPERATION
        } lastElType = EL_OPERATION;
        bool isBreak = true;
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
                case LEX_MOD:
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
        operators.push(lex);
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
        operators.push(lex);
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
        poliz.push_back(Lex(LEX_READ));

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
        varPoint();
    }
}
