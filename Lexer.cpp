#pragma once

#include "Main.h"

namespace Interpreter {
void Scanner::clear() {
	buf_top = 0;
	for ( int j = 0; j < 128; j++ )
		buf[j] = '\0';
}

void Scanner::gc () {
	lc = c;
	input.get(c);
	if (input.eof())
		c = EOF;
}
Scanner::Scanner (const std::string &filename):input(filename.c_str()) {
	CS = H;
	clear();
	gc();
}

std::map<std::string, Ident> TID;

std::map<std::string, Lex_t> Scanner::TW = { {"", LEX_NULL}, {}, {"do", LEX_DO}, {"else", LEX_ELSE},
	{"end", LEX_END}, {"if", LEX_IF}, {"false", LEX_FALSE}, {"true", LEX_TRUE}
};

std::map<std::string, Lex_t> Scanner::TD = { {"", LEX_NULL}, {"@", LEX_FIN}, {"\n", LEX_EOL}, {",", LEX_COMMA}, {".", LEX_DOT}, {"=", LEX_ASSIGN},
	{"(", LEX_LPAREN}, {")",LEX_RPAREN}, {"==", LEX_EQ}, {"<", LEX_LSS}, {">", LEX_GTR},
	{"+", LEX_PLUS}, {"-", LEX_MINUS}, {"*", LEX_MUL}, {"/", LEX_DIV}, {"%", LEX_MOD},
	{"+=", LEX_PLUSEQ}, {"-=", LEX_MINUSEQ}, {"*=", LEX_MULEQ}, {"/=", LEX_DIVEQ}, {"%=", LEX_MODEQ}, {"++", LEX_INC}, {"--", LEX_DEC}
};

Lex Scanner::get_lex () {
	int d, j;
	std::map<std::string, Ident>::iterator itd;
	CS = H;
	do {
		switch(CS) {
			case H:
				if (c ==' ' || c == '\n')
					gc();
				else if (isalpha(c) || c == '_') {
					clear();
					add();
					gc();
					CS = IDENT;
				} else if (isdigit(c)) {
					clear();
					add();
					gc();
					CS = NUMB;
				} else if ( c == '"') {
					clear();
					gc();
					CS = STR;
				} else if (c == EOF)
					return Lex(LEX_FIN);
				else if (c == ';') {
					gc();
					return Lex(LEX_SEMICOLON, ";");
				} else if (c == '{') {
					gc();
					return Lex(LEX_BL_START, "{");
				} else if (c == '}') {
					gc();
					return Lex(LEX_BL_FINISH, "}");
				} else
					CS = DELIM;
				break;
			case IDENT:
				if (isalpha(c) || isdigit(c) || c == '_') {
					add();
					gc();
				} else if(TW[buf])
					return Lex(TW[buf], buf);
				else {
					itd = TID.find(buf);
					if(itd != TID.end() ) {
						TID[buf];
						(itd -> second).put_name(buf);
					}
					return Lex(LEX_ID, buf);
				}
				break;
			case STR:
				if ( c != '"') {
					add();
					gc();
				} else {
					gc();
					CS = H;
					return Lex(LEX_STR, buf);
				}
				break;
			case NUMB : {
					if( isdigit(c) ) {
						add();
						gc();
					} else return Lex( LEX_NUM, buf );
					break;
				}
			case DELIM:
				if((c == '+' || c == '-' || c == '*' || c == '/' || c == '%') && !((c == '+' && lc == '+') || (c == '-' && lc == '-') )) {
					clear();
					add();
					gc();
				} else if((c == '=' && (lc == '+' || lc == '-' || lc == '*' || lc == '/' || lc == '%')) || (c == '+' && lc == '+') || (c == '-' && lc == '-')) {
					add();
					if(TD[buf]) {
						gc();
						return Lex(TD[buf], buf);
					}
					break;
				} else if(lc == '+' || lc == '-' || lc == '*' || lc == '/' || lc == '%') {
					if(TD[buf]) {
						return Lex(TD[buf], buf);
					}
					break;
				} else {
					clear();
					add();
					if(TD[buf]) {
						gc();
						return Lex(TD[buf], buf);
					}
					break;
				}
		}
	} while(true);
}
}
