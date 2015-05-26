#pragma once

#include "Main.h"

namespace Interpreter {
    namespace Lexer {

class Ident {
		std::string name;
		bool declare;
		Lex_t type;
		bool assign;
		std::string value;
	public:
		Ident();

		std::string get_name();
		void put_name(const std::string n);

		bool get_declare();
		void put_declare();

		Lex_t get_type();
		void put_type(Lex_t newType);

		bool get_assign();
		void put_assign();

		std::string get_value();
		void put_value(std::string newValue);
};

    }
}
