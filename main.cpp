#include "Main.h"

int main() {
	Lexer::Scanner scanner("sample.js");
	Lexer::Lex lex;
	while(lex.get_type() != Lexer::LEX_FIN) {
		lex = scanner.getLex();
		std::cout << lex << std::endl;
	}
	return 0;
}

