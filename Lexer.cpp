#include "Lexer.h"

void Scanner::clear() {
	buf_top = 0;
	for ( int j = 0; j < 128; j++ )
		buf[j] = '\0';

}

void Scanner::gc () {
	lc = c;
	input >> c;
	if (input.eof())
		c = EOF;
	//c = fgetc (fp);
}
Scanner::Scanner (const std::string &filename):input(filename.c_str()) {
	//fp = fopen ( filename.c_str(), "r" );
	CS = H;
	clear();
	gc();
}
