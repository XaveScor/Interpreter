#include "Main.h"

namespace Interpreter {
    using namespace Lexer;

    void Executer::goTo(size_t position) {
        index = position;
    }
    void Executer::start() {
        Lex curLex;
        while (curLex.getType() != LEX_FINISH) {
            curLex = getLex();
            switch (curLex.getType()) {
                case LEX_NUMBER:
                case LEX_STRING:
                case LEX_TRUE:
                case LEX_FALSE:
                case POLIZ_ADDRESS:
                    push(curLex);
                    break;
                case LEX_NAME: {
                    std::string value = curLex.getValue();
                    push(data[value]);
                    break;
                }
                case LEX_NOT: {
                    Lex val = pop();
                    push(Lex(LEX_STRING, val.getValue().length() ? "" : "1"));
                    break;
                }
                case LEX_ASSIGN: {
                    Lex val = pop(), address = pop();

                    data[address.getValue()] = val;
                    break;
                }
                case LEX_PLUS: {
                    Lex aStr = pop(), bStr = pop();

                    if (aStr.getType() == LEX_NUMBER && bStr.getType() == LEX_NUMBER) {
                        double a = std::atof(aStr.getValue().c_str()),
                                b = std::atof(bStr.getValue().c_str());

                        push(Lex(LEX_NUMBER, numToStr(a + b)));
                    }
                    else {
                        push(Lex(LEX_STRING, bStr.getValue() + aStr.getValue()));
                    }
                    break;
                }
                case LEX_MINUS: {
                    double a = lexToNum(pop()),
                            b = lexToNum(pop());

                    push(Lex(LEX_NUMBER, numToStr(b - a)));
                    break;
                }
                case LEX_MUL: {
                    double a = lexToNum(pop()),
                            b = lexToNum(pop());

                    push(Lex(LEX_NUMBER, numToStr(a * b)));
                    break;
                }
                case LEX_DIV: {
                    double a = lexToNum(pop()),
                            b = lexToNum(pop());

                    push(Lex(LEX_NUMBER, numToStr(b / a)));
                    break;
                }
                case POLIZ_GO: {
                    int pos = std::atoi(curLex.getValue().c_str());
                    goTo((size_t) pos);
                    break;
                }
                case POLIZ_FALSEGO: {
                    Lex condition = pop();
                    if (condition.getType() == LEX_STRING && condition.getValue() == "") {
                        int pos = std::atoi(curLex.getValue().c_str());
                        goTo((size_t) pos);
                        break;
                    }
                    if (condition.getType() == LEX_NUMBER)
                        if (condition.getValue() == "0") {
                            int pos = std::atoi(curLex.getValue().c_str());
                            goTo((size_t) pos);
                            break;
                        }
                    if (condition.getType() == LEX_FALSE) {
                        int pos = std::atoi(curLex.getValue().c_str());
                        goTo((size_t) pos);
                        break;
                    }
                    break;
                }
                case LEX_WRITE: {
                    std::cout << pop().getValue() << std::endl;
                    break;
                }
                case LEX_MORE: {
                    Lex a = pop(), b = pop();
                    if (a.getType() == LEX_FALSE && b.getType() == LEX_TRUE ||
                            a.getType() == LEX_NUMBER && b.getType() == LEX_NUMBER && lexToNum(a) < lexToNum(b))
                        push(Lex(LEX_TRUE, "1"));
                    else
                        push(Lex(LEX_FALSE, "0"));
                    break;
                }
                case LEX_MOREEQ: {
                    Lex a = pop(), b = pop();
                    if (a.getType() == LEX_FALSE || b.getType() == LEX_TRUE ||
                        a.getType() == LEX_NUMBER && b.getType() == LEX_NUMBER && lexToNum(a) <= lexToNum(b))
                        push(Lex(LEX_TRUE, "1"));
                    else
                        push(Lex(LEX_FALSE, "0"));
                    break;
                }

                case LEX_LESS: {
                    Lex a = pop(), b = pop();
                    if (b.getType() == LEX_FALSE && a.getType() == LEX_TRUE ||
                        a.getType() == LEX_NUMBER && b.getType() == LEX_NUMBER && lexToNum(a) > lexToNum(b))
                        push(Lex(LEX_TRUE, "1"));
                    else
                        push(Lex(LEX_FALSE, "0"));
                    break;
                }
                case LEX_LESSEQ: {
                    Lex a = pop(), b = pop();
                    if (b.getType() == LEX_FALSE || a.getType() == LEX_TRUE ||
                        a.getType() == LEX_NUMBER && b.getType() == LEX_NUMBER && lexToNum(a) >= lexToNum(b))
                        push(Lex(LEX_TRUE, "1"));
                    else
                        push(Lex(LEX_FALSE, "0"));
                    break;
                }
                case LEX_EQ: {
                    Lex a = pop(), b = pop();
                    if ((b.getType() == LEX_FALSE || b.getType() == LEX_TRUE) && a.getType() == b.getType() ||
                        a.getValue() == b.getValue())
                        push(Lex(LEX_TRUE, "1"));
                    else
                        push(Lex(LEX_FALSE, "0"));
                    break;
                }
                case LEX_NOTEQ: {
                    Lex a = pop(), b = pop();
                    if ((b.getType() == LEX_FALSE || b.getType() == LEX_TRUE) && a.getType() != b.getType() ||
                        a.getValue() != b.getValue())
                        push(Lex(LEX_TRUE, "1"));
                    else
                        push(Lex(LEX_FALSE, "0"));
                    break;
                }
            }
        }
    }

    void Executer::push(Lex el) {
        calc.push(el);
    }

    Lex Executer::getLex() {
        return code[index++];
    }

    Executer::Executer(std::string fileName) : index(0), parser(fileName) {
        parser.start();
        code = parser.poliz;
//        std::cout << code[0].getValue() << std::endl;
    }

    Lex Executer::pop() {
        Lex ret = calc.top();
        calc.pop();
        return ret;
    }
}