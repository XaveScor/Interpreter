#pragma once

#include "Main.h"

namespace Interpreter {
    namespace Lexer {
        enum Lex_t {
            LEX_EMPTY,
            LEX_VAR,
            LEX_NAME,
            LEX_NUMBER, LEX_STRING,
            LEX_ASSIGN,
            LEX_ENDOP, LEX_DOT,
            LEX_UNDEFINED,
            LEX_FINISH,
            LEX_PLUS, LEX_MINUS, LEX_MUL, LEX_DIV,
            LEX_TRUE, LEX_FALSE,
            LEX_OR, LEX_AND, LEX_NOT,
            LEX_RBRACKET, LEX_LBRACKET,
            LEX_RFBRACKET, LEX_LFBRACKET,
            LEX_DO, LEX_WHILE, LEX_FOR, LEX_IN, LEX_BREAK, LEX_CONTINUE,
            LEX_IF, LEX_ELSE,
            LEX_PLUSEQ, LEX_MINUSEQ, LEX_MULEQ, LEX_DIVEQ, LEX_MODEQ,
            LEX_MORE, LEX_LESS, LEX_MOREEQ, LEX_LESSEQ, LEX_EQ, LEX_NOTEQ,
            LEX_READ, LEX_WRITE,
            LEX_INC, LEX_DEC,
            LEX_FUNCTION, LEX_TYPEOF, LEX_RETURN,
            LEX_COMMA,
            POLIZ_GO, POLIZ_FALSEGO, POLIZ_ADDRESS
        };

        typedef std::map<std::string, Lex_t> keyTable_t;
        const keyTable_t keyTable = {
                {"var",      LEX_VAR},
                {"=",        LEX_ASSIGN},
                {";",        LEX_ENDOP},
                {"+",        LEX_PLUS},
                {"-",        LEX_MINUS},
                {"*",        LEX_MUL},
                {"/",        LEX_DIV},
                {".",        LEX_DOT},
                {"true",     LEX_TRUE},
                {"false",    LEX_FALSE},
                {"&&",       LEX_AND},
                {"||",       LEX_OR},
                {"!",        LEX_NOT},
                {"(",        LEX_LBRACKET},
                {")",        LEX_RBRACKET},
                {"{",        LEX_LFBRACKET},
                {"}",        LEX_RFBRACKET},
                {"do",       LEX_DO},
                {"while",    LEX_WHILE},
                {"if",       LEX_IF},
                {"else",     LEX_ELSE},
                {"+=",       LEX_PLUSEQ},
                {"-=",       LEX_MINUSEQ},
                {"*=",       LEX_MULEQ},
                {"/=",       LEX_DIVEQ},
                {"%=",       LEX_MODEQ},
                {"==",       LEX_EQ},
                {"!=",       LEX_NOTEQ},
                {"for",      LEX_FOR},
                {"in",       LEX_IN},
                {">",        LEX_MORE},
                {"<",        LEX_LESS},
                {">=",       LEX_MOREEQ},
                {"<=",       LEX_LESSEQ},
                {"read",     LEX_READ},
                {"write",    LEX_WRITE},
                {"++",       LEX_INC},
                {"--",       LEX_DEC},
                {"continue", LEX_CONTINUE},
                {"break",    LEX_BREAK},
                {"function", LEX_FUNCTION},
                {",",        LEX_COMMA},
                {"typeof",   LEX_TYPEOF},
                {"return",   LEX_RETURN}
        };
    }
}
