#include "Main.h"

int main() {
    /*
    Interpreter::Parser parser("sample.js");
    parser.start();

    Interpreter::Parser::poliz_t::iterator it;
    for (it = parser.poliz.begin(); it != parser.poliz.end(); ++it) {
        std::cout << it->getType() << ": " << it->getValue() << std::endl;
    }
    /* */
/*
    Lexer::Scanner scanner("sample.js");
    Lexer::Lex lex = scanner.getLex();
    while(lex.getType() != Lexer::LEX_FINISH) {
        std::cout << lex.getValue() << std::endl;
        lex = scanner.getLex();
    }
    /* */

    Interpreter::Executer exec("sample.js");
    exec.start();
    return 0;
}

