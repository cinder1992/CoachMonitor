#include <string.h>

size_t strcspn(const char* str, const char* delim) {
	const char* l_str = str;
	const char* l_delim = delim;

	while(*l_delim) {
		if(*l_delim++ != *l_str) {
			++l_str;
			l_delim = delim;
		}
	}
	return l_str - str;
}
