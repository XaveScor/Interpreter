#pragma once

#include <fstream>
#include <string>
#include <map>
#include <iostream>

enum type_of_lex {
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

class Lex {
		type_of_lex      t_lex;
		std::string           v_lex;
	public:
		Lex ( type_of_lex  t = LEX_NULL, const std::string  v = "") {
			t_lex = t;
			v_lex = v;
		}
		type_of_lex      get_type ( ) {
			return  t_lex;
		}
		std::string           get_value ( ) {
			return v_lex;
		}
		friend std::ostream&  operator << (std::ostream & s, Lex l ) {
			s  << /*lex_names[l.t_lex] <<*/ "   " << l.v_lex;
			return s;
		}
};

class Scanner {
		std::ifstream input;
	public:
		enum state {H, IDENT, STR, NUMB, DELIM};
		static std::map <std::string, type_of_lex> TW;
		static std::map <std::string, type_of_lex> TD;
		state CS;
		FILE *fp;
		char c, lc;
		char buf [128];
		int buf_top;
		void clear ();
		void add () {
			buf [ buf_top++ ] = c;
		}
		void gc();
		Scanner(const std::string &filename);
		Lex get_lex ();
};
