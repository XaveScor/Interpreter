#pragma once

#include "Main.h"

namespace Interpreter {
    namespace Lexer {

class Scanner {
		std::ifstream input;
		enum state_t {H, IDENT, STR, NUMB, DELIM};
		static std::map <std::string, Lex_t> TW;
		static std::map <std::string, Lex_t> TD;
		state_t currentState;
		char c, lc;
		char buf[128];
		int buf_top;

		void getChar();
        void cleanBuf();
		void add();
	public:
		Scanner(const std::string &filename);
		Lex getLex();
};

    }
}
