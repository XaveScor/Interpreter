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

    void Parser::startPoint() {
        while (lexType != LEX_FINISH) {
            getLex();
            switch (lexType) {
                case LEX_FUNCTION:
                    functionPoint();
                    break;
                case LEX_VAR:
                    varPoint();
                    break;
                case LEX_DO:
                case LEX_WHILE:
                case LEX_FOR:
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
            }
        }

        while(!operators.empty()) {
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
        getLex();

        while (lexType != LEX_ENDOP && lexType != LEX_COMMA && lexType != LEX_FINISH) {
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
                    while(operators.top().getType() != LEX_LBRACKET) {
                        poliz.push_back(operators.top());
                        operators.pop();
                    }
                    operators.pop(); //Delete bracket
                    break;
                case LEX_LBRACKET:
                    operators.push(lex);
                    break;
                case LEX_LFBRACKET:
                    //TODO create array;
                    break;
                case LEX_RFBRACKET:
                    //TODO create array;
                    break;
                default:
                    throw lex;
            }
            getLex();
        }
    }

    size_t Parser::getPriorityByOperation(Lex_t operation) const {
        return operationPriority.find(operation)->second;
    }

    void Parser::cyclePoint() {

    }

    void Parser::conditionPoint() {

    }

    void Parser::readPoint() {

    }

    void Parser::writePoint() {

    }
}
