#include <stdio.h>

int ungetc(int c, FILE* file) {
	if(file->_fl_r != 1) return EOF; //non-read files have no unget buffer!
	if(file->_buf_unget != '\0') return EOF;
	return file->_buf_unget = c;
}
