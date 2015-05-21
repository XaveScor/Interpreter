#pragma once

#include "Main.h"

namespace Interpreter {
enum Lex_t {
	LEX_NULL,
	LEX_DO, LEX_ELSE, LEX_END, LEX_IF, LEX_FALSE, LEX_TRUE, LEX_INT, LEX_BOOL,
	LEX_THEN, LEX_WHILE, LEX_FOR, LEX_IN, LEX_PUTS, LEX_GETS, LEX_CHAR, LEX_DOUBLE,
	LEX_FIN,
	LEX_COMMA, LEX_DOT, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_EQ, LEX_LSS, LEX_GTR,
	LEX_PLUS, LEX_MINUS, LEX_MUL, LEX_DIV, LEX_MOD, LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_QUOT,
	LEX_PLUSEQ, LEX_MINUSEQ, LEX_MULEQ, LEX_DIVEQ, LEX_MODEQ, LEX_EOL, LEX_LSQBR, LEX_RSQBR, LEX_INC, LEX_DEC,
	LEX_AND, LEX_OR, LEX_NOT,
	LEX_NUM,
	LEX_ID,
	LEX_STR,
	POLIZ_LABEL,
	POLIZ_ADDRESS,
	POLIZ_GO,
	POLIZ_FGO,
	LEX_SEMICOLON,
	LEX_BL_START,
	LEX_BL_FINISH
};
}
