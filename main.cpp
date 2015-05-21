#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <map>

#include "Lexer.h"

using namespace std;

/*char lex_names[100000][30] = {
	"LEX_NULL     ",
	"LEX_DO       ", "LEX_ELSE     ", "LEX_END      ", "LEX_IF       ", "LEX_FALSE    ", "LEX_TRUE     ", "LEX_INT      ", "LEX_BOOL     ",
	"LEX_THEN     ", "LEX_WHILE    ", "LEX_FOR      ", "LEX_IN       ", "LEX_PUTS     ", "LEX_GETS     ", "LEX_CHAR     ", "LEX_DOUBLE   ",
	"LEX_FIN      ",
	"LEX_COMMA    ", "LEX_DOT      ", "LEX_ASSIGN   ", "LEX_LPAREN   ", "LEX_RPAREN   ", "LEX_EQ       ", "LEX_LSS      ", "LEX_GTR      ",
	"LEX_PLUS     ", "LEX_MINUS    ", "LEX_MUL      ", "LEX_DIV      ", "LEX_MOD      ", "LEX_LEQ      ", "LEX_NEQ      ", "LEX_GEQ      ", "LEX_QUOT     ",
	"LEX_PLUSEQ   ", "LEX_MINUSEQ  ", "LEX_MULEQ    ", "LEX_DIVEQ    ", "LEX_MODEQ    ", "LEX_EOL      ", "LEX_LSQBR    ", "LEX_RSQBR    ", "LEX_INC      ", "LEX_DEC      ",
	"LEX_AND      ", "LEX_OR       ", "LEX_NOT      ",
	"LEX_NUM      ",
	"LEX_ID       ",
	"LEX_STR      ",
	"POLIZ_LABEL  ",
	"POLIZ_ADDRESS",
	"POLIZ_GO     ",
	"POLIZ_FGO    ",
	"LEX_SEMICOLON",
	"LEX_BL_START ",
	"LEX_BL_FINISH"
};*/

class Ident
{
        string           name;
        bool             declare;
        type_of_lex      type;
        bool             assign;
        string           value;
public:
                         Ident()                       { declare = false; assign = false; }
        string           get_name ()                   { return name; }
        void             put_name (const string n)     { name = n; }
        bool             get_declare ()                { return declare; }
        void             put_declare ()                { declare = true; }
        type_of_lex      get_type    ()                { return type; }
        void             put_type    ( type_of_lex t ) { type = t; }
        bool             get_assign  ()                { return assign; }
        void             put_assign  ()                { assign = true; }
        string           get_value   ()                { return value; }
        void             put_value   (string v)        { value = v; }
};

map < string, Ident > TID;

map < string, type_of_lex > Scanner::TW = { {"", LEX_NULL}, {}, {"do", LEX_DO}, {"else", LEX_ELSE},
					  				     {"end", LEX_END}, {"if", LEX_IF}, {"false", LEX_FALSE}, {"true", LEX_TRUE} };

map < string, type_of_lex > Scanner::TD = { {"", LEX_NULL}, {"@", LEX_FIN}, {"\n", LEX_EOL}, {",", LEX_COMMA}, {".", LEX_DOT}, {"=", LEX_ASSIGN},
										 {"(", LEX_LPAREN}, {")",LEX_RPAREN}, {"==", LEX_EQ}, {"<", LEX_LSS}, {">", LEX_GTR},
										 {"+", LEX_PLUS}, {"-", LEX_MINUS}, {"*", LEX_MUL}, {"/", LEX_DIV}, {"%", LEX_MOD},
										 {"+=", LEX_PLUSEQ}, {"-=", LEX_MINUSEQ}, {"*=", LEX_MULEQ}, {"/=", LEX_DIVEQ}, {"%=", LEX_MODEQ}, {"++", LEX_INC}, {"--", LEX_DEC}
										};

Lex Scanner::get_lex () {
	int d, j;
	map < string, Ident > ::iterator itd;
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
				}
				else if (isdigit(c)) {
					clear();
					add();
					gc();
					CS = NUMB;
				}
				else if ( c == '"') {
					clear();
					gc();
					CS = STR;
				}
				else if (c == EOF)
					return Lex(LEX_FIN);
				else if (c == ';') {
                    gc();
                    return Lex(LEX_SEMICOLON, ";");
				}
				else if (c == '{') {
                    gc();
                    return Lex(LEX_BL_START, "{");
				}
				else if (c == '}') {
                    gc();
                    return Lex(LEX_BL_FINISH, "}");
				}
                else
					CS = DELIM;
				break;
			case IDENT:
                if (isalpha(c) || isdigit(c) || c == '_') {
					add();
					gc();
				}
				else if(TW[buf])
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
				}
				else {
					gc();
					CS = H;
					return Lex(LEX_STR, buf);
				}
				break;
			case NUMB : {
				if( isdigit(c) ) {
					add();
					gc();
				}
				else return Lex( LEX_NUM, buf );
				break;
			}
			case DELIM:
			    if((c == '+' || c == '-' || c == '*' || c == '/' || c == '%') && !((c == '+' && lc == '+') || (c == '-' && lc == '-') )) {clear(); add(); gc();}
			    else if((c == '=' && (lc == '+' || lc == '-' || lc == '*' || lc == '/' || lc == '%')) || (c == '+' && lc == '+') || (c == '-' && lc == '-')) {
                    add();
                    if(TD[buf]) {
                        gc();
                        return Lex(TD[buf], buf);
                    }
                    break;
			    }
			    else if(lc == '+' || lc == '-' || lc == '*' || lc == '/' || lc == '%') {
                    if(TD[buf]) {
                        return Lex(TD[buf], buf);
                    }
                    break;
			    }
			    else {
                    clear();
                    add();
                    if(TD[buf]) {
                        gc();
                        return Lex(TD[buf], buf);
                    }
                    break;
			    }
		}
	}while(true);
}

int main() {
	Scanner a("sample.js");
	Lex l;
	while(l.get_type() != LEX_FIN) {
		l = a.get_lex();
		cout << l << endl;
	}
	return 0;
}

