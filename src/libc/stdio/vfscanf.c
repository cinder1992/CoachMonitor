#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

static void fgethex(FILE* __restrict file, int* var) {
	*var = 0;
	int val;
	do {
		val = toupper(fgetc(file));
		switch(val) {
			case '0' ... '9':
				*var = (*var << 4) | (val - '0');
				break;
			case 'A' ... 'F':
				*var = (*var << 4) | ((val - 'A')+'\x0A');
			default:
				break;
		}
	} while(isxdigit(val));
}

static void fgetdec(FILE* __restrict file, int* var){
	*var = 0;
	int val;
	// Skip leading whitespace
	while(isspace(val = fgetc(file)));

	//parse digits
	do {
		//We can assume that val is not whitespace at this stage
		*var = (*var * '\x0A') + (val - '0');
		val = fgetc(file);
	} while(isdigit(val));
	ungetc(val, file); //unget last non-space character
}

static inline void getlenvar(const char* format, int* idx, int* val) {
	*val = 0;
	while(isdigit(format[*idx])) {
		*val = (*val * '\x0A') + (format[*idx++] - '0');
	}
}

int vfscanf(FILE* file, const char* format, va_list args) {
	int retv = 0;
	int idx = 0;
	int tmp;
	while(isspace(format[idx]) && format[idx] != '\0') idx++; //Skip leading whitespace chars in format
	while(format[idx] != '\0') {
		if(format[idx] == '%') {
			switch(format[++idx]) {
				case 'x':
				case 'X':
					fgethex(file, va_arg(args, int*));
					retv++;
					break;
				case 'd':
					fgetdec(file, va_arg(args, int*));
					retv++;
					break;
				case 's':
					tmp = !0;
					if(isdigit(format[idx + 1])) {
						idx++;
						getlenvar(format, &idx, &tmp); //length
					}
					fgets(va_arg(args, char*), tmp, file);
					retv++;
					break;
				default: //Error condition: Unsupported Format
					return retv;
					break;
			} idx++;
		} else if(format[idx] == ' ') {
			idx++;
			while(isspace(tmp = fgetc(file))); //skip whitespace in file
			ungetc(tmp, file); // unget the last non-space character
		} else if(fgetc(file) != format[idx++]) break;
	}
	return retv;
}
