#pragma once

#include "Main.h"

namespace Interpreter {
class Ident {
		std::string name;
		bool declare;
		Lex_t type;
		bool assign;
		std::string value;
	public:
		Ident() {
			declare = false;
			assign = false;
		}
		std::string get_name (){
			return name;
		}
		void put_name(const std::string n) {
			name = n;
		}
		bool get_declare() {
			return declare;
		}
		void put_declare() {
			declare = true;
		}
		Lex_t get_type() {
			return type;
		}
		void put_type(Lex_t t) {
			type = t;
		}
		bool get_assign() {
			return assign;
		}
		void put_assign() {
			assign = true;
		}
		std::string get_value() {
			return value;
		}
		void put_value(std::string v) {
			value = v;
		}
};

class Lex {
		Lex_t t_lex;
		std::string v_lex;
	public:
		Lex ( Lex_t  t = LEX_NULL, const std::string  v = "") {
			t_lex = t;
			v_lex = v;
		}
		Lex_t      get_type ( ) {
			return  t_lex;
		}
		std::string           get_value ( ) {
			return v_lex;
		}
		friend std::ostream&  operator << (std::ostream & s, Lex l ) {
			s  << l.v_lex;
			return s;
		}
};

class Scanner {
		std::ifstream input;
		enum state {H, IDENT, STR, NUMB, DELIM};
		static std::map <std::string, Lex_t> TW;
		static std::map <std::string, Lex_t> TD;
		state CS;
		char c, lc;
		char buf [128];
		int buf_top;
	public:
		void clear();
		void add() {
			buf [ buf_top++ ] = c;
		}
		void gc();
		Scanner(const std::string &filename);
		Lex get_lex ();
};
}
