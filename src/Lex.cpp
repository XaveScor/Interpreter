#include "Main.h"

namespace Interpreter {
    namespace Lexer {
        Lex::Lex(Lex_t newType/* = LEX_UNDEFINED*/, const std::string newValue/* = ""*/)
                : type(newType), value(newValue) { }

        Lex_t Lex::get_type() {
            return type;
        }

        std::string Lex::get_value() {
            return value;
        }

        std::ostream &operator<<(std::ostream &out, Lex el) {
            out << el.get_value();
            return out;
        }
    }

}
