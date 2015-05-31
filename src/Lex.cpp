#include "Main.h"

namespace Interpreter {
    namespace Lexer {
        Lex::Lex(Lex_t newType/* = LEX_EMPTY*/, const std::string newValue/* = ""*/)
                : type(newType), value(newValue) {
            if (newType == LEX_UNDEFINED) {
                std::cerr << "Undefined Lex is found";
                throw new UndefinedType;
            }
        }

        Lex_t Lex::getType() {
            return type;
        }

        std::string Lex::getValue() {
            return value;
        }

        std::ostream &operator<<(std::ostream &out, Lex el) {
            out << el.getValue();
            return out;
        }
    }

}
