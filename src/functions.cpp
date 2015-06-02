#include "Main.h"

namespace Interpreter {
    std::map<std::string, Lex> data;

    std::string numToStr(double num) {
        std::ostringstream oss;
        oss << num;
        return oss.str();
    }

    double lexToNum(Lex lex) {
        return std::atof(lex.getValue().c_str());
    }
}