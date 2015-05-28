#include "Main.h"

int main() {
    Lexer::Scanner scanner("sample.js");
    Lexer::Lex lex;
    while (lex.get_type() != Lexer::LEX_FINISH) {
        try {
            lex = scanner.getLex();
        } catch (Lexer::UndefinedType) {
            return 0;
        }
        std::cout << lex << std::endl;
    }
    return 0;
}

