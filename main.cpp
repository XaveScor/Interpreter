#include <iostream>

#include "Lexer.h"

int main() {
	Interpreter::Scanner a("sample.js");
	Interpreter::Lex l;
	while(l.get_type() != Interpreter::LEX_FIN) {
		l = a.get_lex();
		std::cout << l << std::endl;
	}
	return 0;
}

