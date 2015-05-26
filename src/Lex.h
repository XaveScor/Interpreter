#pragma once

#include "Main.h"

namespace Interpreter {
    namespace Lexer {
class Lex {
		Lex_t type;
		std::string value;
	public:
	Lex(Lex_t newType = LEX_UNDEFINED, const std::string newValue = "");
		Lex_t get_type();
		std::string get_value();
		friend std::ostream& operator <<(std::ostream &out, Lex el);
};

    }
}
