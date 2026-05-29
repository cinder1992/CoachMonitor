#include <stdio.h>

int fgetc(FILE* file) {
	unsigned char rval;
	int stat;
	//exit early if file has been closed
	if(!file->_fvalid) {
		return EOF;
	}
	//handle unget buffer
	if(file->_buf_unget != '\0') {
		rval = file->_buf_unget;
		file->_buf_unget = '\0';
		return rval;
	}
	//handle "phantom" files used for sscanf and snprintf
	if(file->_fd == -1) { //file is string
		if(file->_buf_cur >= file->_buf_size - 1) {
			file->_ferror = EOF;
			return EOF;
		}
		rval = ((unsigned char*)file->_buf)[file->_buf_cur++];
		if(rval == '\0') {
			file->_buf_size = file->_buf_cur-1;
			return EOF;
		}
		return rval;
	}
	//handle normal files
	switch(file->_bufmode) {
		case _IOFBF: //TODO: Fix
		case _IOLBF: //TODO: Fix
		case _IONBF: //TODO: Fix
			stat = file->_read(file->_fd, &rval, 1);
			if(stat <=0) return EOF;
			return rval;
		default:
			return EOF;
	}
}
