#pragma once

#include "Main.h"

namespace Interpreter {
    extern std::map<std::string, Lex> data;
    std::string numToStr(double num);

    double lexToNum(Lex lex);
}