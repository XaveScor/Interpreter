#include "Main.h"

namespace Interpreter {
    namespace Lexer {

Ident::Ident() {
	declare = false;
	assign = false;
}

std::string Ident::get_name() {
	return name;
}
void Ident::put_name(const std::string n) {
	name = n;
}

bool Ident::get_declare() {
	return declare;
}
void Ident::put_declare() {
	declare = true;
}

Lex_t Ident::get_type() {
	return type;
}
void Ident::put_type(Lex_t newType) {
	type = newType;
}

bool Ident::get_assign() {
	return assign;
}
void Ident::put_assign() {
	assign = true;
}

std::string Ident::get_value() {
	return value;
}
void Ident::put_value(std::string newValue) {
	value = newValue;
}

    }
}
