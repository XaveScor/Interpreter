#include "Main.h"

namespace Interpreter {
    std::string numToStr(size_t num) {
        std::ostringstream oss;
        oss << num;
        return oss.str();
    }
}