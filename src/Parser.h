#pragma once

#include "Main.h"

namespace Interpreter {
    using namespace Lexer;

    class Parser {
    public:
        typedef std::vector<Lex> poliz_t;
        typedef std::stack<Lex> operators_t;
    private:
        Scanner lexer;
        Lex lex;
        std::string lexValue;
        Lex_t lexType;
        typedef Lex_t operationName;
        const std::map<operationName, size_t> operationPriority = {
                {LEX_INC,      0},
                {LEX_DEC,      0},
                {LEX_NOT,      0},
                {LEX_MUL,      1},
                {LEX_DIV,      1},
                {LEX_PLUS,     2},
                {LEX_MINUS,    2},
                {LEX_MORE,     3},
                {LEX_MOREEQ,   3},
                {LEX_LESS,     3},
                {LEX_LESSEQ,   3},
                {LEX_EQ,       4},
                {LEX_NOTEQ,    5},
                {LEX_AND,      6},
                {LEX_OR,       7},
                {LEX_LBRACKET, 8},
                {LEX_ASSIGN,   10},
                {LEX_PLUSEQ,   10},
                {LEX_MINUSEQ,  10},
                {LEX_MULEQ,    10},
                {LEX_DIVEQ,    10},
                {LEX_MODEQ,    10},
                {LEX_EMPTY,    100}

        };

        void getLex();

        void startPoint(Lex_t second = LEX_FINISH);

        void functionPoint();

        void varPoint(bool create = true);

        void cyclePoint();

        void conditionPoint();

        void readPoint();

        void writePoint();

        operators_t operators;

        void expressionPoint();

        void unGetLex();

        size_t getPriorityByOperation(Lex_t operation) const;

        void blockPoint();

        void namePoint();

    public:
        poliz_t poliz;

        Parser(std::string fileName);

        void start();

    };
}